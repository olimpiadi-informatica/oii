#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "domino" scritto da Giorgio Audrito.

Parametri:
* N (numero di tessere)
* R (lower bound della risposta)
* S (seed)

Constraint:
* 2 <= N <= %d
* 0 <= R <= N
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def run(N, R, S):
    nseed(S)
    rseed(S)
    print N
    out = [];
    new = randint(0,7)
    for i in range(R):
        old = new
        new = randint(0,7)
        if random() < 0.5:
            out.append([old,new])
        else:
            out.append([new,old])
    for i in range(R+1,N+1):
        out.append([randint(0,7),randint(0,7)])
    shuffle(out)
    for i in out:
        print i[0], i[1]

if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)

    N, R, S = [int(x) for x in argv[1:]]
    assert (2 <= N and N <= MAXN and 0 <= R and R <= N)
    run(N, R, S)
