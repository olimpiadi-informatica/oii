#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
import string

usage="""Generatore di "cena".

Il pattern è AB, la prima sequenza invece è AA..XYZ..BB
con aggiunto del rumore.
L'obiettivo è rendere il matching molto lungo (circa l'intera stringa S)

Parametri:
* S (numero di piatti)
* T (numero di tipi di piatto)
* s (seed)

Constraint:
* 1 <= S <= %d
* 1 <= T <= %d
""" % (MAXS, MAXT)

def run(S, T):
    print(S, 2)
    chars = list(range(T))
    shuffle(chars)
    A = chars[0]
    B = chars[1]
    chars = chars[2:]
    start = randint(3, S//5)
    end = randint(3, S//5)
    s = [A] * start + [choice(chars) for _ in range(S-start-end)]  + [B] * end
    for _ in range(S//10):
        s[randint(0, S-1)] = choice(chars)
    print(" ".join(map(str, s)))
    print(A, B)


if __name__ == "__main__":
    if len(argv) != 4:
        print(usage)
        exit(1)

    S, T, s = map(int, argv[1:])
    
    assert (1 <= S <= MAXS)
    assert (1 <= T <= MAXT)
    seed(s)
    run(S, T)

