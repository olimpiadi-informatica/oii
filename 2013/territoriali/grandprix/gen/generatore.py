#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "grandprix".

Parametri:
* N (numero di macchine)
* M (numero di sorpassi)
* S (seed)

Constraint:
* 2 <= N <= %d
* 1 <= M <= %d
""" % (MAXN,MAXM)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def run(N, M, S):
    nseed(S)
    rseed(S)
    print N, M
    partenza=range(1,N+1)
    shuffle(partenza)
    for i in partenza:
        print i
    for i in range(M):
        idx=randint(1,N)
        print partenza[idx], partenza[idx-1]
        t=partenza[idx];
        partenza[idx]=partenza[idx-1]
        partenza[idx-1]=t

if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)

    N, M, S = [int(x) for x in argv[1:]]
    assert (2 <= N <= MAXN)
    assert (1 <= M <= MAXM)
    run(N, M, S)
