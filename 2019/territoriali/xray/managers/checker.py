#!/usr/bin/env python3
import os
import sys
import subprocess
import json
import platform

from parser import Parser

if len(sys.argv) != 3:
    print("Usage: %s input_file output_file" % sys.argv[0], file=sys.stderr)
    exit(1)

task_input = open(sys.argv[1], "r")
human_output = open(sys.argv[2], "r")
solution_exe = sys.argv[0].replace("checker", "solution")
os.chmod(solution_exe, 0o555)

solution_process = subprocess.Popen(
    [os.path.join(".", solution_exe), sys.argv[1]],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE)

T = int(task_input.readline())


def evaluate(testcase, student_stream):
    risp = student_stream.int()
    student_stream.end()
    if risp < 0:
        raise ValueError("Risposta negativa (%d) non valida" % risp)
    solution_process.stdin.write(b"%d %d\n" % (testcase, risp))
    solution_process.stdin.flush()
    score = float(solution_process.stdout.readline().decode())
    explaination_length = int(solution_process.stderr.readline().decode())
    explaination = solution_process.stderr.read(explaination_length).decode()
    if score == 1.0:
        return 1.0
    return (score, explaination)


parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))

# Close the child process
solution_process.communicate(input=b"0\n")
