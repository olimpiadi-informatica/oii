#!/usr/bin/env python3

from parser import Parser

from sys import argv, exit, stderr
import json
import sys

if len(argv) != 3:
    print("Usage: %s input_file output_file" % argv[0], file=stderr)
    exit(1)

task_input = open(argv[1], "r")
human_output = open(argv[2], "r")

# reading input file and generating correct output
T = int(task_input.readline())

case = []
for _ in range(T):
    task_input.readline()
    N = int(task_input.readline())
    A = list(map(int, task_input.readline().split()))
    case.append(A)


def max_people(A):
    m = 0
    M = 0
    S = 0
    for x in A:
        S += x
        m = min(m, S)
        M = max(M, S)
    
    return M - m


def evaluate(task, stream):
    out = stream.int()
    stream.end()
    correct_res = max_people(case[task-1])

    if out != correct_res:
        return 0.0, "Risposta errata!"
    else:
        return 1.0

parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))
