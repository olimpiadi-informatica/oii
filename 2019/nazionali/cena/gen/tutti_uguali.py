#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
import string

usage="""Generatore di "cena".

Genera s e p usando sempre lo stesso carattere, aggiunge un po' di rumore
ad s.

Lo scopo è rendere praticamente massimo il valore in output

Parametri:
* S (numero di piatti)
* P (numero di tutor)
* K (numero di errori da aggiungere ad S)
* T (numero di caratteri distinti da usare)
* s (seed)

Constraint:
* 1 <= S <= %d
* 1 <= P <= %d
* 1 <= T <= %d
""" % (MAXS, MAXrep, MAXT)

def run(S, P, K, T):
    print(S, P)
    c = randint(0, T-1)
    s = [c] * S
    for _ in range(K):
        s[randint(0, S-1)] = randint(0, T-1)
    print(" ".join(list(map(str, s))))
    print(" ".join(list(map(str, [c] * P))))


if __name__ == "__main__":
    if len(argv) != 6:
        print(usage)
        exit(1)

    S, P, K, T, s = map(int, argv[1:])
    
    assert (1 <= S <= MAXS)
    assert (1 <= P <= MAXP)
    assert P <= MAXrep
    assert 1 <= T <= MAXT
    seed(s)
    run(S, P, K, T)
