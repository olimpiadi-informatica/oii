#!/usr/bin/env python3

from sys import argv, exit, stderr
from parser import Parser
import json

if len(argv) != 3:
    print("Usage: %s input_file output_file" % argv[0], file=stderr)
    exit(1)

task_input = open(argv[1], "r")
human_output = open(argv[2], "r")

# reading input file and generating correct output
T = int(task_input.readline())

inputs = [-1]
for _ in range(T):
    inputs.append(int(task_input.readline()))

fibo = [1, 1]
for i in range(50):
    fibo.append(fibo[-1] + fibo[-2])


def evaluate(num, stream):
    num = inputs[num]
    out = stream.str()
    stream.end()
    out_sum = 0
    for i in range(len(out)):
        if out[i] == '1':
            out_sum += fibo[i]
    return 1.0 if out_sum == num else 0.0


parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))
