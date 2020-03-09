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

T = int(task_input.readline())
tests = []
for i in range(T):
    task_input.readline()
    N, F, C = map(int, task_input.readline().strip().split())
    tests.append((N, F, C))

def evaluate(testcase, student_stream):
    ans_f = student_stream.int()
    ans_c = student_stream.int()
    student_stream.end()
    if ans_f < 0 or ans_c < 0:
        raise ValueError("Risposta negativa ({} {}) non valida".format(ans_f, ans_c))

    N, F, C = tests[testcase - 1]

    if  ans_f == N // F and ans_c == (N % F) // C:
        return 1.0
    else:
        return 0.0


parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))
