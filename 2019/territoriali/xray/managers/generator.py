#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit
from random import randint, seed, shuffle
import random

usage = """Generatore di "xray".

Parametri:
* S - seed
* 0 - il valore zero
"""

cases = 0

def _ctz(i):
    c = 0
    while i and not i & 1:
        c += 1
        i //= 2
    return c


def start_case(N):
    global cases
    print()
    print(N)
    cases += 1


def generandom(N, A):
    start_case(N)
    print(*[randint(10**(A - 1), (10**A) - 1) for _ in range(N)])

def rampa(N, A):
    start_case(N)
    valori = [randint(10**(A - 1), (10**A) - 1) for _ in range(N)]
    valori.sort()
    if random.randint(0, 1) == 0:
        valori.reverse()
    print(*valori)

def ctz(N):
    start_case(N)
    valori = [2**_ctz(i+1) for i in range(N)]
    K = randint(0, MAXV-max(valori)-1)
    print(*[v+K for v in valori])

def allK(N, K):
    start_case(N)
    print(*[K]*N)

if __name__ == "__main__":
    if len(argv) < 3:
        print(usage)
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    print(T)

    # esempi/a mano
    generandom(5, 1)  # a mano
    generandom(8, 1)  # a mano

    tipi = ["random"]*9 + ["ctz"]*4 + ["rampa"]*3 + ["allK"]*1
    shuffle(tipi)

    for tipo in tipi:
        if tipo == "random":
            generandom(randint(100, 1000), randint(1, 3))
        elif tipo == "rampa":
            rampa(randint(100, 1000), randint(1, 3))
        elif tipo == "ctz":
            ctz(randint(550, 1000))
        elif tipo == "allK":
            allK(666, randint(0, MAXV))

    assert cases == T
