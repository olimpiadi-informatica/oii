#!/usr/bin/env python3

T = int(input())

for caso in range(1, T + 1):
    input()
    N = int(input())
    V = [int(x) for x in input().split(" ") if x != ""]
    def splitter(v):
        sets = []
        last_set = []
        for i in v:
            if i == 0:
                sets.append(last_set)
                last_set = []
                continue
            last_set.append(i)
        sets.append(last_set)
        return sets
    solution = 0
    sets = splitter(V)
    while len(sets) > 0:
        top = sets.pop()
        if len(top) == 0:
            continue
        minimum = min(top)
        solution += minimum
        for i in range(len(top)):
            top[i] -= minimum
        sets += splitter(top)
    print("Case #", caso, ": ", solution, sep='')
