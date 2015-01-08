#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "barbablu".

Parametri:
* N (nodi)
* M (archi)
* K (sacche d'aria)
* W (peso massimo)
* S (seed)

Constraint:
* 2 <= N <= %d
* N-1 <= M <= %d
* 1 <= K <= N
""" % (MAXN,MAXM)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed
from graph import *
from string import split, join

def run(N, M, K, W, S):
    nseed(S)
    rseed(S)
    def wh():
        return randint(1,W+1)
    out = ugraph(N,type='tree',w=wh)
    out.addedges(M-N+1)
    out.shuffle()
    air = sample( range(1,N+1), K )
    C = randint(1, K)
    if len(air) > 1:
        while air[C] == 1:
            C = randint(1, K)
    print N, M, air[C], K
    for i in range(K):
        print air[i],
    print
    s = split(str(out), '\n')
    print join(s[1:-1], '\n')

if __name__ == "__main__":
    if len(argv) != 6:
        print usage
        exit(1)

    N, M, K, W, S = [int(x) for x in argv[1:]]
    assert (2 <= N <= MAXN)
    assert (N-1 <= M <= MAXM)
    assert (0 <= K <= N)
    run(N, M, K, W, S)
