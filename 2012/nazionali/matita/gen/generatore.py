#!/usr/bin/env python2
# -*- coding: utf-8 -*-
# Generatore per matita:
# Scelgo un nodo a caso come inizio ed ad ogni step scelgo un vicino a caso
# Alla fine riordino gli archi in maniera casuale
# NOTA BENE: c'e la possibilita di finire in un nodo senza uscita! in quel caso il programma va in ciclo infinito. non mi é ancora capitato, in caso diminuire il numero di archi o cambiare il seed

from limiti import *

usage="""Generatore per "matita".

Parametri:
* N (numero di nodi)
* M (numeri di archi)
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= M <= %d
""" % (MAXN, MAXM)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, randrange, seed as rseed

def is_in(edges, edge):
    return edge in edges or (edge[1], edge[0]) in edges

def run(N, M, S):
    nseed(S)
    rseed(S)
    edges = set()
    start = randrange(0, N)
    cur = start

    # Inizia con un super-ciclo, tanto per farlo connesso
    for i in xrange(0, N):
        edges.add((i, (i+1)%N))

    # E poi tutto il resto, a caso
    for i in xrange(N, M):
        next = randrange(0, N)
        while next == cur or is_in(edges, (cur, next)) or (i == M-1 and next == start):
            next = randrange(0, N)
        edges.add((cur, next))
        cur = next
    stop = cur

    # Genera una permutazione dei vertici
    perm = range(N)
    shuffle(perm)

    print N, M, perm[start]+1, perm[stop]+1
    for edge in edges:
        if randint(0, 1) == 0:
            print perm[edge[0]]+1, perm[edge[1]]+1
        else:
            print perm[edge[1]]+1, perm[edge[0]]+1

if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)
    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    N, M, S = [int(x) for x in argv[1:]]
    assert (1 <= N <= MAXN)
    assert (1 <= M <= MAXM)
    run(N, M, S)
