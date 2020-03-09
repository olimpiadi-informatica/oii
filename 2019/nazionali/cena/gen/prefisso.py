#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
import string

usage="""Generatore di "cena".

Genera in modo casuale p, mentre s ha p come suffisso, gli altri caratteri
sono causali con un gran bias verso il primo carattere di p

Parametri:
* S (numero di piatti)
* P (numero di tutor)
* T (numero di caratteri distinti da usare)
* s (seed)

Constraint:
* 1 <= S <= %d
* 1 <= P <= %d
* 1 <= T <= %d
""" % (MAXS, MAXP, MAXT)

def run(S, P, T):
    print(S, P)
    p = [randint(0, T-1) for _ in range(P)]
    s = [p[0] if random() < 0.8 else randint(0, T-1) for _ in range(S-P)] + p
    print(" ".join(map(str, s)))
    print(" ".join(map(str, p)))


if __name__ == "__main__":
    if len(argv) != 5:
        print(usage)
        exit(1)

    S, P, T, s = map(int, argv[1:])
    
    assert (1 <= S <= MAXS)
    assert (1 <= P <= MAXP)
    assert (1 <= T <= MAXT)
    assert T >= P/MAXrep
    seed(s)
    run(S, P, T)
