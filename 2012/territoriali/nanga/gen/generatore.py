#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "nanga" scritto da Giorgio Audrito.

Parametri:
* N (lunghezza della sequenza)
* P (massimo dislivello)
* S (seed)

Constraint:
* 2 <= N <= %d
* 0 <= P <= %d
""" % (MAXN, MAXP)

from sys import argv, exit, stderr
import os
from numpy.random import seed, random
from random import choice, sample, shuffle, randint

def run(N, P, S):
    seed(S)
    Validato = False
    # genera sequenze di numeri casuali finche' non ne ha una con "moda" unica
    while not Validato:
        out = []
        for i in range(N):
            out.append( randint(-P,P+1) )
        # calcola la sequenza di altezze
        sum = [5000]
        for i in range(1,N+1):
            sum.append( sum[i-1] + out[i-1] )
        # calcola la moda (con molteplicita') sul vettore sum
        sum.sort()
        j = 0
        max = 0
        nmax = 0
        for i in range(1,N+1):
            if sum[i] != sum[i-1]:
                if i-j > max:
                    max = i-j
                    nmax = 1
                elif i-j == max:
                    nmax += 1
                j = i
        if nmax == 1:
            Validato = True
    print N
    for i in out:
        print i

if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)

    N, P, S = [int(x) for x in argv[1:]]
    assert (2 <= N and N <= MAXN)
    assert (0 <= P and P <= MAXP)
    run(N, P, S)
