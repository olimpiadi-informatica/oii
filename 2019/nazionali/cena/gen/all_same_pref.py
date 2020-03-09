#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
import string

usage="""Generatore di "cena".

La prima sequenza è causale, la seconda è composta da un solo tipo ripetuto.

Questo è un subtask del problema

Parametri:
* S (numero di piatti)
* P (numero di tutor)
* T (numero di tipi di piatto)
* s (seed)

Constraint:
* 1 <= S <= %d
* 1 <= P <= %d
* 1 <= T <= %d
""" % (MAXS, MAXP, MAXT)

def run(S, P, T):
    print(S, P)
    c = randint(0, T-1)
    print(" ".join(str(c if random() < 0.5 else randint(0, T-1)) for _ in range(S)))
    print(" ".join([str(randint(0, T-1))] * P))


if __name__ == "__main__":
    if len(argv) != 5:
        print(usage)
        exit(1)

    S, P, T, s = map(int, argv[1:])
    
    assert (1 <= S <= MAXS)
    assert (1 <= P <= MAXP)
    assert P <= MAXrep
    assert 1 <= T <= MAXT
    seed(s)
    run(S, P, T)
