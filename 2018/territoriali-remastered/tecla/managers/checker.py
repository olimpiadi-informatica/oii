#!/usr/bin/env python3

from sys import argv, exit, stderr
from parser import Parser
import json

if len(argv) != 3:
    print("Usage: %s input_file output_file" % argv[0], file=stderr)
    exit(1)

task_input = open(argv[1], "r")
human_output = open(argv[2], "r")

#print(task_input.read(), file=stderr)
#print(human_output.read(), file=stderr)
#exit(0)

# reading input file and generating correct output
T = int(task_input.readline())

edges = [[]]
for i in range(T):
    edges.append([])
    N, M = map(int, task_input.readline().split())
    for j in range(M):
        a, b = tuple(map(int, task_input.readline().split()))
        edges[i+1].append((a, b))
        edges[i+1].append((b, a))


def evaluate(num, stream):
    current_edges = edges[num]
    lung = stream.int()
    prev = stream.int()
    start = prev
    for i in range(lung):
        nxt = stream.int()
        if (prev,nxt) not in current_edges:
            return 0.0, "Arco non esistente"
            print("arco non esistente", file=stderr)
        prev = nxt
    if start != prev:
        return 0.0, "Non è un ciclo"
        print("no ciclo", file=stderr)
    stream.end()
    return 1.0


parser = Parser(evaluate, T, human_output, int_max_len=20, strict_spaces=False)

print(json.dumps(parser.run()))
