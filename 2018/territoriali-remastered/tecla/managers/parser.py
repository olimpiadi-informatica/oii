#!/usr/bin/env python3

from collections import deque
import json
import unittest
import io
from functools import reduce
from random import shuffle, choices, randrange
import string


BUFFER_SIZE = 1024
FUZZER_LENGTH = 8192
FUZZER_RUNS = 1024
DEFAULT_INT_MAX_LEN = 32
DEFAULT_FLOAT_MAX_LEN = 32
DEFAULT_STRING_MAX_LEN = 4096


class TokenStream:
    def __init__(self, file, strict_spaces=False, int_max_len=DEFAULT_INT_MAX_LEN, float_max_len=DEFAULT_FLOAT_MAX_LEN, str_max_len=DEFAULT_STRING_MAX_LEN, spaces=" \t\n"):
        """
        :param file: file object of the output
        :param strict_spaces: whether to consider spaces as tokens, manual skipping of them is required
        :param int_max_len: maximum number of chars for a int
        :param float_max_len: maximum number of chars for a float
        :param str_max_len: maximum number of chars for a str
        :param spaces: list of characters to consider spaces
        """
        self.file = file
        self.strict_spaces = strict_spaces

        if str_max_len < int_max_len:
            raise ValueError("str_max_len lower than int_max_len")
        if str_max_len < float_max_len:
            raise ValueError("str_max_len lower than float_max_len")

        self.int_max_len = int_max_len
        self.float_max_len = float_max_len
        self.str_max_len = str_max_len

        self.spaces = spaces

        self.char_buffer = deque()
        self.current_line_no = 1
        self.eof = False

    # =======================
    #      read a token
    # =======================

    def int(self, validate=lambda x: True):
        """Read an integer"""
        return self._parse_number(self.int_max_len, int, "+-0123456789", validate, advance_buffer=True)

    def float(self, validate=lambda x: True):
        """Read a float"""
        return self._parse_number(self.float_max_len, float, "+-e0123456789.", validate, advance_buffer=True)

    def str(self, validate=lambda x: True):
        """Read a string"""
        self._skip_spaces()
        buffer = list()
        # read all chars that are not spaces
        while not self._is_eof() and self._probe_char() not in self.spaces:
            buffer += self._next_char()
            if len(buffer) > self.str_max_len:
                raise ValueError("string too long")
        buffer = "".join(buffer)
        if not validate(buffer):
            raise ValueError("invalid string")
        return buffer

    def char(self, validate=lambda x: True):
        """Read a single char, skipping spaces"""
        self._skip_spaces()
        char = self._next_char()
        if not validate(char):
            raise ValueError("invalid char")
        return char

    def space(self, validate=lambda x: True):
        """Read a single space"""
        if self._is_eof() or self._probe_char() not in self.spaces:
            raise ValueError("expecting a space")
        space = self._next_char()
        if not validate(space):
            raise ValueError("invalid space")
        return space

    def end(self):
        """Check that there are no more tokens before the next testcase without consuming anything"""
        # the end of the file is a valid end
        if not self.strict_spaces:
            self._skip_spaces()

        if self._is_eof():
            return
        try:
            # read at least the characters for the prefix and a digit
            while len(self.char_buffer) < len("Case #")+1:
                self._read_char()
            # check the buffer starts with the prefix
            if self._is_prefix() >= 0:
                raise ValueError("the testcase has not ended")
        # if the EOF is found but not at the beginning there's a problem
        except EOFError:
            raise ValueError("expecting new testcase, not EOF")

    def seek_next_testcase(self):
        """
        skip everything until the next testcase
        @:returns a pair: (testcase number, skipped bytes, line_no)
        @:raises EOFError: when the file ends this error is raised with the skipped bytes as args[1]
        """
        old_spaces = self.spaces
        MAX_LEN = 100

        class safe_str:
            def __init__(self):
                self.str = list()
                self.trimmed = False

            def __add__(self, other):
                if len(self.str) > MAX_LEN or self.trimmed:
                    return self
                if len(self.str) + len(other) > MAX_LEN:
                    self.str += list(other[:MAX_LEN-len(self)]) + list("...")
                    self.trimmed = True
                    return self
                self.str += list(other)
                return self

            def __len__(self):
                return len(self.str)

            def __str__(self):
                return "".join(self.str)

        data_read = safe_str()
        skipped_from = self.current_line_no

        while True:
            try:
                skipped = str(data_read)
                skipped_from = self.current_line_no

                # skip all the spaces
                while self._probe_char() in self.spaces:
                    data_read += self._next_char()

                # try to read the "Case"
                case = self.str()
                line = self.current_line_no
                data_read += case
                # if the string is not Case, read also the space and try again
                if case.lower() != "case" and case.lower() != "caso":
                    data_read += self._probe_char()
                    continue

                # skip one space between "Case" and "#"
                data_read += self.space()

                # check if the next char is #
                if self._probe_char() != "#": continue
                # if so read it
                data_read += self.char()

                # to read the testcase number use the ":" as a delimiter, after the int is read revert this change
                self.spaces += ":"
                num = self.int()
                data_read += str(num)
                # revert self.spaces
                self.spaces = old_spaces
                # if the testcase number is not valid
                if num <= 0: continue

                # check if the char after the number is a ":"
                if self._probe_char() != ":": continue
                data_read += self.char()

                return num, line, str(skipped), skipped_from
            except ValueError as ex:
                pass
            except EOFError as ex:
                raise EOFError(ex.args[0], str(data_read), skipped_from)
            finally:
                # if the call to self.int() fails we have to be sure to have reverted self.spaces
                self.spaces = old_spaces

    def has_int(self):
        """check is the next bytes in the buffer are a valid int"""
        if not self.strict_spaces:
            self._skip_spaces()
        try:
            self._parse_number(self.int_max_len, int, "+-0123456789", lambda x: True, advance_buffer=False)
        except:
            return False
        else:
            return True

    def has_float(self):
        """check is the next bytes in the buffer are a valid float"""
        if not self.strict_spaces:
            self._skip_spaces()
        try:
            self._parse_number(self.float_max_len, float, "+-e0123456789.", lambda x: True, advance_buffer=False)
        except:
            return False
        else:
            return True

    def has_space(self, accepted=None):
        """check is the next byte in the buffer is a space (only in strict_spaces mode)"""
        if not self.strict_spaces:
            raise RuntimeError("has_space is available only in strict_spaces mode")
        if accepted is None:
            accepted = self.spaces
        return not self._is_eof() and self._probe_char() in accepted

    # ================
    #    utilities
    # ================

    def _skip_spaces(self):
        """Try to skip the spaces, if int strict_spaces mode and there are spaces to skip raise an error"""
        if self.strict_spaces and not self._is_eof() and self._probe_char() in self.spaces:
            raise ValueError("expecting something not a space")
        spaces = ""
        while not self._is_eof() and self._probe_char() in self.spaces:
            spaces += self._next_char()
        return spaces

    def _next_char(self):
        """Read and consume a char"""
        if self._probe_char() == "\n":
            self.current_line_no += 1
        return self.char_buffer.popleft()

    def _probe_char(self, index=0):
        """Fetch the next index-th character without consuming it"""
        if len(self.char_buffer) <= index:
            self._read_char()
        return self.char_buffer[index]

    def _read_char(self):
        """Read but not consume a character"""
        char = self.file.read(BUFFER_SIZE)
        if char == "":
            raise EOFError("End of file")
        self.char_buffer.extend(char)
        return char

    def _parse_number(self, max_len, type, allowed_chars, validate, advance_buffer=True):
        """
        Read and parse a number
        :param max_len: maximum number of characters to read
        :param type: int/float
        :param allowed_chars: set of allowed characters in the number
        :param validate: function to call to check if the number is valid
        :param advance_buffer: whether to consume the number
        """
        self._skip_spaces()
        # index in the char_buffer
        index = 0
        buffer = ""
        # continue to read until the end of the file or an invalid char
        while not self._is_eof(index+1) and self._probe_char(index) in allowed_chars:
            buffer += self.char_buffer[index]
            index += 1
            if len(buffer) > max_len:
                raise ValueError("number too long")

        # if the while exited because an invalid char
        if not self._is_eof(index+1) and self._probe_char(index) not in self.spaces:
            raise ValueError("invalid character `%s' in number" % self._probe_char(index))

        # consume the number if requested
        if advance_buffer:
            for _ in range(index):
                self._next_char()

        res = type(buffer)
        if not validate(res):
            raise ValueError("validation failed")
        return res

    def _is_prefix(self):
        """tries to match the "Case #" prefix in the buffer, returns the index of mismatch, -1 if match"""
        for i in range(len("Case #")):
            if self.char_buffer[i].lower() != "case #"[i]:
                return i
        return -1

    def _is_eof(self, at_least=1):
        """returns True if there are no more bytes to consume"""
        if len(self.char_buffer) >= at_least:
            return False
        if self.eof:
            return True
        try:
            self._read_char()
        except EOFError:
            self.eof = True
            return True
        else:
            return False


class Parser:
    def __init__(self, parse_testcase, num_inputs, file, **kwargs):
        """
        :param parse_testcase: function to call to parse a testcase, will be passed 2 parameters: (testcase number,
        stream). The second parameter is an instance of TokenStream. The function may return the score [0,1] or a tuple
        (score, message).
        :param num_inputs: number of testcases
        :param file: file with the output to parse
        :param kwargs: arguments to pass to the TokenStream constructor
        """
        self.stream = TokenStream(file, **kwargs)
        self.parse_testcase = parse_testcase
        self.num_inputs = num_inputs

    def run(self):
        total_score = 0.0
        testcases_seen = set()
        output = {
            "score": 0.0,
            "validation": {
                "cases": [{"status": "missing"} for _ in range(self.num_inputs)],
                "alerts": []
            },
            "feedback": {
                "cases": [{"correct": False} for _ in range(self.num_inputs)],
                "alerts": []
            }
        }

        def add_warning(message):
            output["validation"]["alerts"].append({"severity": "warning", "message": message})

        while True:
            try:
                num, line_no, skipped, skipped_from = self.stream.seek_next_testcase()
                if len(skipped) > 0:
                    add_warning("Skipped data from line %d: %s" % (skipped_from, skipped))
                if num in testcases_seen:
                    add_warning("Skipped duplicate testcase %d at line %d" % (num, line_no))
                    continue
                if num > self.num_inputs:
                    add_warning("Skipped testcase %d > %d at line %d" % (num, self.num_inputs, line_no))
                    continue
                testcases_seen.add(num)
                output["validation"]["cases"][num-1]["status"] = "parsed"
                output["validation"]["cases"][num-1]["message"] = "Found from line %d" % line_no
            except EOFError as ex:
                if len(ex.args) >= 3 and len(ex.args[1]) > 0:
                    add_warning("Skipped data from line %d: %s" % (ex.args[2], ex.args[1]))
                break

            try:
                out = self.parse_testcase(num, self.stream)
            except ValueError as ex:
                output["validation"]["cases"][num-1]["status"] = "invalid"
                output["validation"]["cases"][num-1]["message"] = str(ex)
                continue

            if isinstance(out, tuple):
                score, message = out
            else:
                score, message = out, ""

            if len(message) > 0:
                output["feedback"]["cases"][num-1]["message"] = message
            if score == 1.0:
                output["feedback"]["cases"][num-1]["correct"] = True
            if score < 0.0 or score > 1.0:
                score = 0.0
                output["feedback"]["cases"][num-1]["correct"] = False
                output["feedback"]["cases"][num-1]["message"] = "buggy checker detected!"

            total_score += score

        output["score"] = total_score/self.num_inputs
        return output


class TestParser(unittest.TestCase):
    def test_none_args(self):
        with self.assertRaises(TypeError):
            p = Parser(None, None, None)
            p.run()

    def test_none_eval(self):
        with self.assertRaises(TypeError):
            p = Parser(None, 1, io.StringIO("Case #1: 42"))
            p.run()

    def test_mismatch_cases(self):
        for i in range(2):
            with self.subTest(case_number=i):
                p = Parser(lambda x, y: int(x == y.int()), 1, io.StringIO("Case #42: 42\nCase #1: " + str(i)))
                self.assertEqual(p.run()["score"], float(i))

    def test_correct_integer(self):
        for k in (1, 2, 37, 131, 1009):
            with self.subTest(number_of_cases=k):
                lines = ["Case #%d: %d" % (i + 1, i) for i in range(k)]
                shuffle(lines)
                text = reduce(lambda x, y: x + "\n" + y, lines)
                def evaluate(case_number, stream):
                    n = stream.int()
                    stream.end()
                    return float(case_number == n + 1)
                p = Parser(evaluate, k, io.StringIO(text))
                self.assertEqual(p.run()["score"], 1.0)

    def test_correct_float(self):
        for k in (1, 2, 37, 131, 1009):
            with self.subTest(number_of_cases=k):
                lines = ["Case #%d: %f" % (i + 1, float(i)) for i in range(k)]
                shuffle(lines)
                text = reduce(lambda x, y: x + "\n" + y, lines)
                def evaluate(case_number, stream):
                    n = stream.float()
                    stream.end()
                    return float(abs(float(case_number) - n - 1.0) < 1e-6)
                p = Parser(evaluate, k, io.StringIO(text))
                self.assertEqual(p.run()["score"], 1.0)

    def test_correct_string(self):
        for k in (1, 2, 37, 131, 1009):
            with self.subTest(number_of_cases=k):
                def n2n(x):
                    if x % 2 == 0:
                        return "yay"
                    else:
                        return "nay"
                lines = ["Case #%d: %s" % (i + 1, n2n(i)) for i in range(k)]
                shuffle(lines)
                text = reduce(lambda x, y: x + "\n" + y, lines)
                def evaluate(case_number, stream):
                    n = stream.str()
                    stream.end()
                    return float(n2n(case_number + 1) == n)
                p = Parser(evaluate, k, io.StringIO(text))
                self.assertEqual(p.run()["score"], 1.0)

    def test_too_long_string(self):
        p = Parser(lambda x, y: float(y.str() == "wibblemonster"), 1, io.StringIO("Case #1: wibblemonster"), str_max_len=5, int_max_len=5, float_max_len=5)
        self.assertEqual(p.run()["score"], 0.0)

    def test_string_validator(self):
        def tester(case_number, stream):
            s = stream.str(lambda x: x == "foo")
            return float(s == "bar")  # pragma: no cover
        p = Parser(tester, 1, io.StringIO("Case #1: bar"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_char_validator(self):
        def tester(case_number, stream):
            c = stream.char(lambda x: x == "a")
            return float(c == "b")  # pragma: no cover
        p = Parser(tester, 1, io.StringIO("Case #1: b"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_int_validator(self):
        def tester(case_number, stream):
            n = stream.int(lambda x: x == 42)
            return float(n == 21)  # pragma: no cover
        p = Parser(tester, 1, io.StringIO("Case #1: 21"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_space(self):
        def tester(case_number, stream):
            c = stream.space()
            return float(c == " ")
        p = Parser(tester, 1, io.StringIO("Case #1: "), strict_spaces=True)
        self.assertEqual(p.run()["score"], 1.0)

    def test_space_wrong(self):
        def tester(case_number, stream):
            c = stream.space()
            return float(c == " ")  # pragma: no cover
        p = Parser(tester, 1, io.StringIO("Case #1:"), strict_spaces=True)
        self.assertEqual(p.run()["score"], 0.0)

    def test_space_validator(self):
        def tester(case_number, stream):
            c = stream.space(lambda x: x == "\n")
            return float(c == " ")  # pragma: no cover
        p = Parser(tester, 1, io.StringIO("Case #1: "), strict_spaces=True)
        self.assertEqual(p.run()["score"], 0.0)

    def test_multiple_spaces_case(self):
        p = Parser(lambda x, y: 1.0, 1, io.StringIO("Case   #1: "))
        self.assertEqual(p.run()["score"], 0.0)

    def test_same_cases(self):
        p = Parser(lambda x, y: float(y.int() == 0), 1, io.StringIO("Case #1: 1\nCase #1: 0"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_same_space_separated(self):
        p = Parser(lambda x, y: float(y.int() == 0), 1, io.StringIO("Case #1: 0 Case #1: 1"))
        self.assertEqual(p.run()["score"], 1.0)

    def test_same_invalid_separated(self):
        p = Parser(lambda x, y: float(y.int() == 0), 1, io.StringIO("Case #1: 0Case #1: 0"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_wrong_case_naming(self):
        p = Parser(lambda x, y: float(y.int() == 0), 1, io.StringIO("Caze #1: 0"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_too_few_arguments(self):
        def tester(case_number, stream):
            s = stream.str()
            stream.end()
            return float(s == "foobar")
        p = Parser(tester, 4, io.StringIO("Case #1: \nCase #2: foobar Case #3: foobar\tCase #4: foobar"))
        self.assertEqual(p.run()["score"], 0.5)

    def test_buggy_eval(self):
        p = Parser(lambda x, y: 45.0, 1, io.StringIO("Case #1: "))
        self.assertEqual(p.run()["score"], 0.0)

    def test_message(self):
        p = Parser(lambda x, y: (0.0, "foobar"), 1, io.StringIO("Case #1: "))
        self.assertEqual(p.run()["feedback"]["cases"][0]["message"], "foobar")

    def test_case_too_long(self):
        p = Parser(lambda x, y: 1.0, 1, io.StringIO("Case #" + str(2**2**2**2**2) + ": "))
        self.assertEqual(p.run()["score"], 0.0)

    def test_case_malformed(self):
        def tester(case_number, stream):
            n = stream.int()
            stream.end()
            return float(n == 42)
        p = Parser(tester, 4, io.StringIO("Case #1: 42\nCase #foobar: 42\nCase #3: 42\nCase #2: 21"))
        self.assertEqual(p.run()["score"], 0.5)

    def test_case_malformed_without_end(self):
        def tester(case_number, stream):
            n = stream.int()
            return float(n == 42)
        p = Parser(tester, 4, io.StringIO("Case #1: 42\nCase #foobar: 42\nCase #3: 42\nCase #2: 21"))
        self.assertEqual(p.run()["score"], 0.5)

    def test_case_malformed_alone(self):
        def tester(case_number, stream):
            n = stream.int()  # pragma: no cover
            return float(n == 42)  # pragma: no cover
        p = Parser(tester, 1, io.StringIO("Case #foobar: 42"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_early_eof(self):
        def tester(case_number, stream):
            n = stream.int()
            stream.end()
            return float(n == 42)  # pragma: no cover
        p = Parser(tester, 2, io.StringIO("Case #2: 42\nCas"))
        self.assertEqual(p.run()["score"], 0.0)

    def test_strict_nospaces(self):
        def tester(case_number, stream):
            (a, b) = (stream.int(), stream.int())
            stream.end()  # pragma: no cover
            return float(a == 42 and b == 42)  # pragma: no cover
        p = Parser(tester, 2, io.StringIO("Case #1:42 42"), strict_spaces=True)
        self.assertEqual(p.run()["score"], 0.0)

    def test_strict_has(self):
        def tester(case_number, stream):
            self.assertFalse(stream.has_int())
            self.assertFalse(stream.has_float())
            self.assertTrue(stream.has_space())
            _ = stream.space()
            s = stream.str()
            return float(s == "foobar")
        p = Parser(tester, 1, io.StringIO("Case #1: foobar"), strict_spaces=True)
        self.assertEqual(p.run()["score"], 1.0)

    def test_strict_has_int(self):
        def tester(case_number, stream):
            self.assertTrue(stream.has_int())
            n = stream.int()
            return float(n == 42)
        p = Parser(tester, 1, io.StringIO("Case #1:42"), strict_spaces=True)
        self.assertEqual(p.run()["score"], 1.0)

    def test_empty(self):
        p = Parser(lambda x, y: 1.0, 1, io.StringIO(""))
        self.assertEqual(p.run()["score"], 0.0)

    def test_strict_has_float(self):
        def tester(case_number, stream):
            self.assertTrue(stream.has_float())
            n = stream.float()
            return float(n == 42.0)
        p = Parser(tester, 1, io.StringIO("Case #1:42.0"), strict_spaces=True)
        self.assertEqual(p.run()["score"], 1.0)

    def test_has_int(self):
        def tester(case_number, stream):
            self.assertTrue(stream.has_int())
            n = stream.int()
            return float(n == 42)
        p = Parser(tester, 1, io.StringIO("Case #1: 42"))
        self.assertEqual(p.run()["score"], 1.0)

    def test_has_float(self):
        def tester(case_number, stream):
            self.assertTrue(stream.has_float())
            n = stream.float()
            return float(n == 42.0)
        p = Parser(tester, 1, io.StringIO("Case #1: 42.0"))
        self.assertEqual(p.run()["score"], 1.0)

    def test_has_space(self):
        def tester(case_number, stream):
            with self.assertRaises(RuntimeError):
                stream.has_space()
            return 1.0
        p = Parser(tester, 1, io.StringIO("Case #1: "))
        self.assertEqual(p.run()["score"], 1.0)

    def test_int_lower(self):
        with self.assertRaises(ValueError):
            p = Parser(lambda x, y: float(y.int() == 42), 1, io.StringIO("Case #1: 42"), str_max_len=1)
            self.assertEqual(p.run()["score"], 1.0)


class FuzzerParser(unittest.TestCase):
    def test_int(self):
        for i in range(FUZZER_RUNS):
            fuzz = "".join(choices(string.digits, k=randrange(FUZZER_LENGTH)))
            with self.subTest(run=i, fuzz=fuzz):
                p = Parser(lambda x, y: float(y.int() == -1), 1, io.StringIO("Case #1: " + fuzz))
                self.assertEqual(p.run()["score"], 0.0)

    def test_int_parameters(self):
        for i in range(FUZZER_RUNS):
            k = min(randrange(FUZZER_LENGTH), DEFAULT_STRING_MAX_LEN)
            fuzz = "".join(choices(string.digits, k=randrange(FUZZER_LENGTH)))
            with self.subTest(run=i, fuzz=fuzz, int_param=k):
                p = Parser(lambda x, y: float(y.int() == -1), 1, io.StringIO("Case #1: " + fuzz), int_max_len=k)
                self.assertEqual(p.run()["score"], 0.0)

    def test_float(self):
        for i in range(FUZZER_RUNS):
            fuzz = "".join(choices(string.digits, k=randrange(FUZZER_LENGTH // 2)))
            fuzz += "."
            fuzz += "".join(choices(string.digits, k=randrange(FUZZER_LENGTH // 2)))
            with self.subTest(run=i, fuzz=fuzz):
                p = Parser(lambda x, y: float(y.float() == -1.0), 1, io.StringIO("Case #1: " + fuzz))
                self.assertEqual(p.run()["score"], 0.0)

    def test_float_parameters(self):
        for i in range(FUZZER_RUNS):
            fuzz = "".join(choices(string.digits, k=randrange(FUZZER_LENGTH // 2)))
            fuzz += "."
            fuzz += "".join(choices(string.digits, k=randrange(FUZZER_LENGTH // 2)))
            k = min(randrange(FUZZER_LENGTH), DEFAULT_STRING_MAX_LEN)
            with self.subTest(run=i, fuzz=fuzz, float_param=k):
                p = Parser(lambda x, y: float(y.float() == -1.0), 1, io.StringIO("Case #1: " + fuzz), float_max_len=k)
                self.assertEqual(p.run()["score"], 0.0)

    def test_string(self):
        for i in range(FUZZER_RUNS):
            fuzz = "".join(choices(string.digits + string.ascii_uppercase + string.ascii_lowercase, k=randrange(FUZZER_LENGTH + 1)))
            with self.subTest(run=i, fuzz=fuzz):
                p = Parser(lambda x, y: float(y.str() == ""), 1, io.StringIO("Case #1:" + fuzz), strict_spaces=True)
                self.assertEqual(p.run()["score"], 0.0)

    def test_string_parameters(self):
        for i in range(FUZZER_RUNS):
            fuzz = "".join(choices(string.digits + string.ascii_uppercase + string.ascii_lowercase, k=randrange(FUZZER_LENGTH + 1)))
            k = max(randrange(FUZZER_LENGTH), DEFAULT_INT_MAX_LEN, DEFAULT_FLOAT_MAX_LEN)
            with self.subTest(run=i, fuzz=fuzz, string_param=k):
                p = Parser(lambda x, y: float(y.str() == ""), 1, io.StringIO("Case #1:" + fuzz), str_max_len=k, strict_spaces=True)
                self.assertEqual(p.run()["score"], 0.0)

    def test_raw(self):
        for i in range(FUZZER_RUNS):
            fuzz = "".join(choices(string.printable, k=randrange(FUZZER_LENGTH)))
            if fuzz[0:4].lower() in ("caso", "case"):
                fuzz = "a" + fuzz
            with self.subTest(run=i, fuzz=fuzz):
                p = Parser(lambda x, y: float(y.str() == ""), 1, io.StringIO(fuzz))
                self.assertEqual(p.run()["score"], 0.0)

    def test_raw_unicode(self):
        for i in range(FUZZER_RUNS):
            fuzz = ""
            for _ in range(randrange(FUZZER_LENGTH)):
                fuzz += chr(randrange(0x110000))
            if fuzz[0:4].lower() in ("caso", "case"):
                fuzz = "a" + fuzz
            with self.subTest(run=i, fuzz=fuzz):
                p = Parser(lambda x, y: float(y.str() == ""), 1, io.StringIO(fuzz))
                self.assertEqual(p.run()["score"], 0.0)


if __name__ == "__main__":
    unittest.main()
