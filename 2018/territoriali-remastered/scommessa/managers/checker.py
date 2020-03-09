#!/usr/bin/env python3

from itertools import accumulate
from parser import Parser
from sys import argv, exit, stderr
import json

if len(argv) != 3:
    print("Usage: %s input_file output_file" % argv[0], file=stderr)
    exit(1)

task_input = open(argv[1], "r")
human_output = open(argv[2], "r")

# reading input file and generating correct output
T = int(task_input.readline())

outputs = [[]]
for _ in range(T):
    task_input.readline()
    data = list(map(int, task_input.readline().split()))
    parity = [-1 if x % 2 == 1 else 1 for x in data]
    prefix = [0] + list(accumulate(parity))
    suffix = (list(reversed(list(accumulate(reversed(parity))))) + [0])[1:]
    outputs.append(
        set(data[i] for i in range(len(data))
            if prefix[i] == 0 and suffix[i] == 0))


def evaluate(num, stream):
    correct_output = outputs[num]
    K = stream.int()
    output = []
    for i in range(K):
        output.append(stream.int())
    stream.end()
    output_set = set(output)
    if len(output) != len(output_set):
        return 0.0, "Elementi duplicati"
    if output_set == correct_output:
        return 1.0
    else:
        return 0.0


parser = Parser(evaluate, T, human_output, int_max_len=20, strict_spaces=False)

print(json.dumps(parser.run()))
