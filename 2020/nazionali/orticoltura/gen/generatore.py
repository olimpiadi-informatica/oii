#!/usr/bin/env pypy3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage = """Generatore di "orticoltura".

Parametri:
* N (numero di semi)
* C (costo degli irrigatori)
* maxX (posizione massima dei semi)
* maxP (profondità massima dei semi)
* S (seed)

Constraint:
* 1 <= N <= %d
* 0 <= C <= %d
* 1 <= maxX <= %d
* 1 <= maxP <= %d
""" % (MAXN, MAXC, MAXX, MAXP)


def hard_run(N, C, maxX, maxP):
    assert(10 * maxX >= N*(2*C+10))
    lengths = [randint(2, 3) for _ in range((N-1)//2)]
    if (N-1) % 2:
        lengths.append(1)
    assert(maxX >= 100 and maxP >= 50)
    positions = [(100, 50)]
    x = 1
    for l in lengths:
        if l == 1:
            positions.append((x, 1))
        if l == 2:
            positions.append((x, 1)), positions.append((x+1, 1))
        if l == 3:
            positions.append((x, 1)), positions.append((x+2, 1))
        x += l + 2*C // 10
        if randint(0, 1) == 0:
            x += 2
        if randint(0, 3) == 0:
            x += 1
        if randint(0, 15) == 0:
            x += 1

    shuffle(positions)

    print(C)
    print(N)
    for x, p in positions:
        print(10*x, 10*p)


def run(N, C, maxX, maxP):
    positions = set()
    while len(positions) < N:
        x = randint(1, maxX)
        p = randint(1, maxP)
        positions.add((x, p))
    positions = list(positions)
    shuffle(positions)
    print(C)
    print(N)
    for x, p in positions:
        print(10*x, 10*p)


if __name__ == "__main__":
    if len(argv) != 7:
        print(usage)
        exit(1)

    N, C, maxX, maxP, hard, S = map(int, argv[1:])

    assert (1 <= N <= MAXN)
    assert (0 <= C <= MAXC)
    assert (1 <= 10*maxX <= MAXX)
    assert (1 <= 10*maxP <= MAXP)

    seed(S)
    if hard:
        hard_run(N, C, maxX, maxP)
    else:
        run(N, C, maxX, maxP)
