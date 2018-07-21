#!/usr/bin/env python2

from limiti import *
from graph import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from math import sqrt, ceil

usage="""Generatore di "oddcycle".

Parametri:
* N (nodi)
* M (archi o altri nodi)
* T (tasktype)
* S (seed)

Constraint:
* 1 <= N <= %d
* 2 <= T <= 6
""" % (MAXN)



def run(N, M, T):
    assert M >= N >= 3

    # clique
    if T == 2:
        assert N*(N-1)/2 <= MAXM
        g = ugraph(N,type='clique')
    # star piu' altri archi a caso
    if T == 3:
        g = ugraph(N,type='star')
        g.addedges(M-N+1)
    # due cicli con un nodo in comune
    if T == 4:
        assert (N % 2) or (M % 2)
        assert N + M <= MAXN
        g = ugraph(N-1) + ugraph(M, type='cycle')
        g = ugraph(N, type='cycle') | g
    # random
    if T == 5:
        C = 2*randint(1,(N-1)/2)+1
        g = ugraph(C, type='cycle') + ugraph(N-C)
        g.connect()
        g.addedges(M-g.M())
    # bipartito piu' almeno un arco mal fatto
    if T == 6:
        assert M <= (N/2)*((N+1)/2) + 1
        x = int(ceil( (N - sqrt(N*N - 4*M + 4))/2 ))
        N1 = randint(x,N-x)
        N2 = N - N1
        g = ugraph(N1, N2, type='bipartite')
        g.addedges(M-N, edgerange(g,[0,N1],[N1,N]))
        r = xrange(0,N1) if (N1>1 and randint(0,1)) or N2==1 else xrange(N1,N)
        g += sample(r, 2)
    g.zero_based = True
    g.shuffle()
    print g


if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    N, M, T, S = map(int, argv[1:])
    
    assert (2 <= T <= 6)
    seed(S)
    run(N, M, T)
