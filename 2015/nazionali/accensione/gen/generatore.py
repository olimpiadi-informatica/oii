#!/usr/bin/env python2

from limiti import *
from sys import argv, exit
from random import shuffle, seed, randint
from itertools import product

usage="""Generatore di "Accensione".

Parametri:
* N (numero di computer/pulsanti)
* S (seed)
* T (tipo)
    0: caso di esempio
    1: sono spenti esattamente i numeri primi
    2: qualsiasi
    3: degenere (tutti accesi o tutti spenti)

Constraint:
* %d <= N <= %d
""" % (MINN, MAXN)


def run(N, S, T):
    print N
    
    if T == 1:
        # Trovo i numeri primi fino a N
        isprime = [ 1 for i in range(N+1) ]
        isprime[1] = 0
        for i in range(2, N+1):
            j = 2*i
            while j <= N:
                isprime[j] = 0
                j += i
        
        for i in range(1, N+1):
            print 1 - isprime[i],
    
    elif T == 2:
        for i in range(0, N):
            print randint(0,1),
    
    elif T == 3:
        status = randint(0,1)
        for i in range(0, N):
            print status,

if __name__ == "__main__":
    try:
        N, S, T = map(int, argv[1:])
    except ValueError:
        print usage
        exit(1)

    # Se T==0 copia un input di esempio dal .tex
    if T == 0:
        print """6
0 1 0 1 0 0""",
        exit(0)
    seed(S)

    assert (MINN <= N <= MAXN)

    run(N, S, T)
