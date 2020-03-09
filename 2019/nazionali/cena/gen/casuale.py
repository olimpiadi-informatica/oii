#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
import string

usage="""Generatore di "cena".

Genera due sequenze causali, nota che il valore della soluzione è
tendenzialmente basso.

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
    print(" ".join(str(randint(0, T-1)) for _ in range(S)))
    pool = [ str(c) for _ in range(MAXrep) for c in range(T) ]
    shuffle(pool)
    print(" ".join(pool[:P]))


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
