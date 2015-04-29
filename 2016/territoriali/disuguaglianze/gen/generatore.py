#!/usr/bin/env python2

from limiti import *
from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

usage="""Generatore di "disuguaglianze".

Parametri:
* N (numero di caselle)
* S (seed)

Constraint:
* 1 <= N <= %d
""" % (MAXN)


def run(N):
    print N

    L = range(1, N+1)
    shuffle(L)

    signs = []
    for i in xrange(N-1):
        signs.append("<" if L[i] < L[i+1] else ">")

    print "".join(signs)

if __name__ == "__main__":
    if len(argv) != 3:
        print usage
        exit(1)

    N, S = map(int, argv[1:])

    assert 1 <= N <= MAXN

    nseed(S)
    rseed(S)
    run(N)
