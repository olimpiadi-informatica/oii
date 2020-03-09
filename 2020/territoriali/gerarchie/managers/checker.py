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
    N = int(task_input.readline().strip())
    parents = []
    values = []
    for _ in range(N):
        p, v = map(int, task_input.readline().strip().split())
        parents.append(p)
        values.append(v)
    tests.append((parents, values))

def evaluate(testcase, student_stream):
    risp = student_stream.int()
    student_stream.end()
    if risp < 0:
        raise ValueError("Risposta negativa (%d) non valida" % risp)

    parents, values = tests[testcase - 1]
    
    N = len(parents)
    value_to_node = [-1 for _ in range(N)]
    for i, v in enumerate(values):
        value_to_node[v] = i

    sol = 0
    for v in reversed(sorted(values)):
        i = value_to_node[v]
        while parents[i] != -1 and values[parents[i]] < values[i]:
            u = parents[i]
            vu = values[u]
            # scambio u con i
            value_to_node[vu] = i
            value_to_node[v] = u
            values[i] = vu
            values[u] = v
            i = u
            sol += 1

    if sol == risp:
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
