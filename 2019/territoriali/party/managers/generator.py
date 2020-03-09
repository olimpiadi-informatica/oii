#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit, stderr
from random import randint, seed, shuffle, choice
usage = """Generatore di "antivirus".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""

cases = 0

def start_case(N, A):
    global cases
    print()
    print(N)
    print(" ".join(map(str, A)))
    cases += 1


def casuale(N, minA, maxA):
    start_case(N, [randint(minA, maxA) for _ in range(N)])


if __name__ == "__main__":
    if len(argv) < 3:
        print(usage)
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    print(T)

    # a mano
    casuale(10, -10, 10)

    i = randint(2, T)

    # non a mano davvero
    for t in range(2, T+1):
        if t == i:
            casuale(MAXN, MINA, 0)
        else:
            casuale(randint(3*MAXN//4, MAXN), MINA, MAXA)

    assert cases == T
