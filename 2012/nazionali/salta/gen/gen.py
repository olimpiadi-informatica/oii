#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "salta".

Parametri:
* N (lunghezza)
* M (lunghezza del periodo)
* A (lunghezza dell'antiperiodo)
* S (seed)

Constraint:
* 2 <= N <= %d
* 1 <= M <= N
* 0 <= A <= N
* A+M <= N
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def run(N, S, M, A):
    nseed(S)
    rseed(S)
    print N

    # Decide quali elementi saranno presi, in modo che 1 sia nel
    # periodo o nell'antiperiodo
    numeri = range(1, N)
    shuffle(numeri)
    numeri = [0] + numeri

    # Crea un array di base che contiene numeri brutti per le
    # posizioni che non saranno mai raggiunte
    salti = []
    for i in xrange(N):
        salti.append(randint(0, N-1))

    # Modifica alcuni numeri in modo che venga compiuto il percorso
    # voluto
    for i in xrange(A+M-1):
        dist = numeri[i+1] - numeri[i]
        if dist < 0:
            dist += N
        salti[numeri[i]] = dist
    dist = numeri[A] - numeri[A+M-1]
    if dist < 0:
        dist += N
    salti[numeri[A+M-1]] = dist

    print " ".join(map(str, salti))

if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)
    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    N, S, M, A = [int(x) for x in argv[1:]]
    assert (2 <= N <= MAXN)
    assert (1 <= M <= N)
    assert (0 <= A <= N)
    assert (A+M <= N)
    run(N, S, M, A)
