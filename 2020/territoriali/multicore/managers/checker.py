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

solution_process = subprocess.run(
    [os.path.join(".", solution_exe), "1"],
    stdin=open(sys.argv[1], "r"),
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE)
correct_outputs = solution_process.stdout.decode().splitlines()

T = int(task_input.readline())


def evaluate(testcase, student_stream):
    risp = student_stream.int()
    student_stream.end()
    correct = int(correct_outputs[testcase-1])
    if correct == risp:
        return 1.0
    return (0.0, "Risposta errata. La risposta corretta era %d" % correct)


parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))
