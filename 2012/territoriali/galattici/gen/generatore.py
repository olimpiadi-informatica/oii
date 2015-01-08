#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "galattici".

Parametri:
* N (numero di configurazioni)
* K (numero di lettere)
* S (seed)

Constraint:
* 2 <= N < %d
* 2 <= K < %d
""" % (MAXN, MAXK)

from sys import argv, exit, stderr
import os
from numpy.random import seed, random, randint
from random import choice, sample
import random

def run(N, K, S):
    random.seed(S)
    seed(S)
    s = ""
    for i in range(K):
        s += choice("abcdefghijklmnopqrstuvwxyz")
    Q = randint(1, N+1)
    trip = {}
    curr = 1
    for i in s:
        if (curr, i) in trip:
            curr = trip[(curr, i)]
        else:
            dest = randint(1, N+1)
            trip[(curr, i)] = dest
            curr = dest

    M = randint(K, MAXM+1)
    tent = 0
    while tent < 100 and len(trip) != M:
        curr = randint(1, N+1)
        c = choice("abcdefghijklmnopqrstuvwxyz")
        if (curr, c) not in trip:
            dest = randint(1, N+1)
            trip[(curr, c)] = dest
        else:
            tent += 1

    print len(trip), N, K
    for i in s:
        print i,
    print
    for i in trip:
        print i[0], trip[i], i[1]
    
if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)

    N, K, S = [int(x) for x in argv[1:]]
    assert (2 <= N and N <= MAXN)
    assert (2 <= K and K <= MAXK)
    run(N, K, S)
