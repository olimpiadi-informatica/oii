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
    task_input.readline()
    M = int(task_input.readline())
    S = [task_input.readline() for _ in range(4)]
    case.append((M, S))

def evaluate(task, stream):
    out = [stream.int() for _ in range(4)]
    stream.end()
    M, S = case[task-1]
    for i in range(4):
        o = out[i]
        if o < 0 or o > len(S[i])-M:
            raise ValueError("La posizione %d indicata per il file %d è fuori dall'intervallo [0,%d]" % (o, i+1, len(S[i])-M))

    virus = [S[i][out[i]:out[i]+M] for i in range(4)]
    if len(set(virus)) == 1:
        return 1.0
    return 0.0, "I 4 virus indicati non sono uguali: '%s', '%s', '%s', '%s'" \
        % (virus[0], virus[1], virus[2], virus[3])

parser = Parser(
    evaluate,
    T,
    human_output,
    int_max_len=20,
    str_max_len=50,
    strict_spaces=False)

print(json.dumps(parser.run()))
