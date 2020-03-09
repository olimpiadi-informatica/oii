#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import MAXN
from sys import argv, exit
from random import randint, seed

usage = """Generatore di "lwf".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""

if __name__ == "__main__":
    if len(argv) < 3:
        print(usage)
        exit(1)

    T = 20

    S, _ = map(int, argv[1:])
    seed(S)
    print(T)
    for _ in range(T):
        N = randint(1, MAXN)
        print(N)
