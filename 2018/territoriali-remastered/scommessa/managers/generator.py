#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import MAXN
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage = """Generatore di "oddcycle".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""


def run(N, mode):
    print(N)
    if mode == 0:
        nums = [str(x) for x in range(0, N)]
        shuffle(nums)
        print(' '.join(nums))
    elif mode == 1:
        nums = [str(x) for x in range(0, N)]
        print(' '.join(nums))
    elif mode == 2:
        even = [str(i * 2) for i in range(0, (N + 1) // 2)]
        odd = [str(i * 2 + 1) for i in range(0, N - 1 - N // 2)]
        shuffle(even)
        shuffle(odd)
        print(' '.join(even + odd))
    else:
        print("Tipo di generazione non valido")
        print(usage)
        exit(1)


if __name__ == "__main__":
    if len(argv) < 3:
        print(usage)
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    T = 10
    print(T)
    for _ in range(T):
        N = randint(1, (MAXN - 1) // 2)
        N = 2 * N + 1
        assert 1 <= N <= MAXN
        assert N % 2 == 1
        mode = randint(0, 2)
        run(N, mode)
