#!/usr/bin/env python2
# -*- coding: utf8 -*-

from limits import *
from graph import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from math import sqrt, ceil

usage="""Generatore di "oddcycle".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""



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
    if len(argv) != 3:
        print usage
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)

    # T = 2 -- clique
    # T = 3 -- star più altri archi a caso
    # T = 4 -- due cicli con un nodo in comune
    # T = 5 -- random
    # T = 6 -- bipartito più almeno un arco mal fatto

    params = [
        [3, 3, 2], [4, 4, 2], [5, 5, 2], [6, 6, 2], [7, 7, 2], [8, 8, 2],
        [30, 30, 3], [19, 22, 3], [19, 26, 3], [18, 27, 3], [14, 19, 3], [29, 29, 3],
        [3, 10, 4], [5, 22, 4], [13, 14, 4], [13, 15, 4], [13, 16, 4], [9, 16, 4], [10, 17, 4], [13, 17, 4], [11, 19, 4],
        [6, 10, 5], [6, 10, 5], [8, 10, 5], [17, 20, 5], [17, 20, 5], [30, 30, 5], [16, 30, 5], [16, 30, 5], [16, 30, 5], [26, 30, 5], [6, 15, 5], [6, 15, 5], [23, 26, 5], [23, 26, 5], [25, 27, 5], [25, 27, 5],
        [14, 30, 6], [15, 30, 6], [10, 24, 6], [11, 24, 6], [11, 25, 6], [13, 27, 6], [9, 18, 6], [9, 18, 6], [12, 28, 6], [13, 28, 6], [12, 29, 6], [12, 29, 6], [13, 29, 6],
    ]

    shuffle(params)

    print(len(params))
    for N, M, T in params:
        run(N, M, T)
