#!/usr/bin/env python2

from limiti import *
from graph import graph, ugraph
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from math import log, sqrt

usage="""Generatore di "corteo".

Parametri:
* N (numero di nodi)
* M (numero di archi)
* T (tipo di subtask) e' 1 per "generico", 2 per "sorgente = destinazione", 3 per "ciclo", 4 per "ruota", 5 per "solouno"
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= M <= %d
""" % (MAXN, MAXM)

def run(N, M, T):
    # Devo scegliere i 4 nodi per le partenze/arrivi (non necessariamente distinti)
    P1 = randint(0, N-1)
    P2 = randint(0, N-1)
    if (T != 2):
        D1 = randint(0, N-1)
        D2 = randint(0, N-1)
    else:
        D1 = P1
        D2 = P2

    # Devo costruire un grafo connesso non diretto su N vertici con M archi
    if (T == 3):
        NG = min(randint(1, N), randint(1, N))
        G = ugraph( NG, NG, 'cycle')
        Nrem = N-G.N()
        while Nrem > 0:
            NGrem = min(randint(1, Nrem), randint(1, Nrem))
            Gpath = ugraph( NGrem, NGrem, 'path')
            Nrem -= NGrem
            G += Gpath
        P1 = 0
        P2 = G.N()-1
        D1 = P2
        D2 = P1
    elif (T == 4):

        rD = randint( int(N/4), int(N/2) )
        rN = int( N / rD )
	# print rD,"+"rN
        GD = ugraph( rD, rD, "path")
        GN = ugraph( rN, rN, "cycle")
        G = GD*GN
	P1 = randint(0, G.N())
	P2 = randint(0, G.N())
	D1 = randint(0, G.N())
	D2 = randint(0, G.N())
        G += ugraph(1, 1)
        for i in xrange(rN):
            G += (i, G.N()-1)
    elif (T == 5):
        Gpath = ugraph( int(N/2), type="path")
        Ggraph = ugraph( N- Gpath.N(), M - Gpath.M() - 2, "connected");
        G = Gpath + Ggraph
        G += (Gpath.N()-1, Gpath.N())
        P1 = D1 = 0
        P2 = Gpath.N() + randint(0, Ggraph.N()-1)
        D2 = Gpath.N() + randint(0, Ggraph.N()-1)
    elif (T == 6):
        Gpath = ugraph( int(N/2), type="path")
        Gpath2 = ugraph( N-int(N/2), type="path")
        G = Gpath + Gpath2
        G += (int(N/2)-1, int(3*N/4))
        P1 = D1 = 0
        P2 = int(N/2)
        D2 = N-1
    elif (T == 333):
        G = ugraph(N, N, 'cycle')
	P1 = randint(0, G.N()-1)
	P2 = randint(0, G.N()-1)
	D1 = randint(0, G.N()-1)
	D2 = randint(0, G.N()-1)
    else:
        G = ugraph(N, M, 'connected') #mmh

    G.connect()
    G.zero_based = True
    G.shuffle()

    # Devo stampare prima N e M, poi i numeri Pi e Di e infine gli archi
    # Attenzione: M puo' essere diverso da quello che e' stato dato in input, in particolare puo' essere piu' basso.
    print G.N(), G.M()
    print G.lbl[P1], G.lbl[D1], G.lbl[P2], G.lbl[D2]
    print G.printedges()

if __name__ == "__main__":
    if len(argv) != 5:
        print(usage)
        exit(1)

    N, M, T, S = map(int, argv[1:])

    assert (2 <= N <= MAXN)
    assert (1 <= M <= MAXM)
    assert ((N*(N-1)) >= 2*M)

    seed(S)
    run(N, M, T)
