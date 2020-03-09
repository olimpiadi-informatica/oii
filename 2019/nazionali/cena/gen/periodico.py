#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
import string

usage="""Generatore di "cena".

Genera un periodo e, sia s che p, sono il periodo ripetuto.
Ad s e p viene aggiunto del rumore.

L'obiettivo è avere un alto valore in output

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
    L = P//10+1
    err_s = int(S * 20 / 100)
    err_p = int(P * 0 / 100)
    period = [randint(0, T-1) for _ in range(L)]
    s = period * (S//L) + period[:(S%L)]
    p = period * (P//L) + period[:(P%L)]
    for _ in range(err_s):
        s[randint(0, S-1)] = randint(0, T-1)
    for _ in range(err_p):
        p[randint(0, P-1)] = randint(0, T-1)
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
