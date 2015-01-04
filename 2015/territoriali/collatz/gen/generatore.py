#!/usr/bin/env python2

from limiti import *
from varie import *
from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

usage="""Generatore di "prova".

Parametri:
* N (numero)
* S (seed)

Constraint:
* 1 <= N <= %d
""" % (MAXN)


def run(N):
    print N

if __name__ == "__main__":
    if len(argv) != 3:
        print usage
        exit(1)

    N, S = map(int, argv[1:])
    assert (1 <= N <= MAXN)

    # su seed non positivo copia un input di esempio dal .tex
    if S <= 0:
        print extract_input()[-S],
        exit(0)
    nseed(S)
    rseed(S)
    run(N)
