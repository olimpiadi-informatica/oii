#!/usr/bin/env pypy

from limiti import *
from graph import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from sortedcontainers import SortedSet as sortedset

usage="""Generatore di "footing".

Parametri:
* N (num nodi)
* M (num archi)
* W (max peso)
* S (seed)

Constraint:
* 3 <= N <= %d
* 3 <= M <= %d
* 1 <= W <= %d
""" % (MAXN, MAXM, MAXW)


def run(N, M, W):
    g = ugraph(N, w=lambda: randint(1, W))
    g.addedges(M)

    print N, M
    print g.printedges()

if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    N, M, W, S = map(int, argv[1:])

    assert (3 <= N <= MAXN)
    assert (3 <= M <= MAXM)
    assert (1 <= W <= MAXW)

    seed(S)
    run(N, M, W)
