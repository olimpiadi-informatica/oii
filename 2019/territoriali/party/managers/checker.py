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

T = int(task_input.readline())
case = []
for _ in range(T):
    task_input.readline()
    task_input.readline()
    A = map(int, task_input.readline().split())
    case.append(A)

def evaluate(task, stream):
    out = stream.int()
    stream.end()
    A = case[task-1]
    sol = sum(a for a in A if a > 0)
    if sol == out:
        return 1.0
    return 0.0, "Il tuo programma dice %d ma la massima bellezza possibile è %d" % (out, sol)

parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))
