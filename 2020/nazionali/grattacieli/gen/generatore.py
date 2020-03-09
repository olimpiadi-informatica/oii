#!/usr/bin/env python2

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from graph import *

usage="""Generatore di "grattacieli".

Parametri:
* N (numero di nodi)
* M (numero di archi)
* L (profondita' albero cammini minimi)
* W (massimo peso archi)
* H (massimo peso nodi)
* O (se gli archi [u,v] vanno dati ordinati u<v oppure no)
* R (se i pesi vanno generati a caso oppure no)
* S (seed)

Constraint:
* %d <= N <= %d
* %d <= M <= %d
* N-1 <= M <= (N-1)*N
* 1 <= L <= N
* L <= W <= %d
* L+W <= H <= %d
* O,R in [0,1]
* meglio se N >= 8
""" % (MIN_N, MAX_N, MIN_M, MAX_M, MAX_C, MAX_H)


def run(mN, mM, mL, mW, mH, O, R):
    assert MIN_N <= mN <= MAX_N
    assert MIN_M <= mM <= MAX_M
    assert mN-1 <= mM <= mN*(mN-1)
    assert 1 <= mL <= mN
    assert mL <= mW <= MAX_C
    assert mW + mL <= mH <= MAX_H
    assert 0 <= O <= 1
    assert 0 <= R <= 1
    
    def randhigh(a, b):
        return max([randint(a,b) for _ in xrange(2)])
    def randlow(a, b):
        return min([randint(a,b) for _ in xrange(2)])
    
    # potrebbe fallire se N <= 8
    N = mN if mN <= 8 else randhigh(8, mN)
    L = 1 if mL == 1 else N if mL == mN else (
        randhigh(1, 1+(mL-1)*(N-1)/(mN-1)) if randint(0,1) else randlow(1+(mL-1)*(N-1)/(mN-1), N)
    )
    W = randhigh(L, mW * L / mL)
    Y = randint(W+L, min(mH * (W+L) / (mW+mL), N*W if R else N*W/4)) # massimo H
    S = N/L # step tra due nodi consecutivi nel path
    K = N if R else L*S*W/Y # massima differenza ammessa tra estremi degli archi
    M = N-1 + randhigh(0, min((mM-mN+1)*(N-1)**2/(mN-1)**2, K*(2*N-K-1)/2))

    D = [0 for _ in xrange(N)] # distanze finali dal nodo -1
    H = [0 for _ in xrange(N)] # archi  diretti  dal nodo -1
    # parent nell'albero dei cammini minimi
    P = [i-S if i%S == 0 and i < L*S else randint(max(0,i-K),i-1) for i in xrange(N)]
    
#    print "DEBUG:", N, M, L, W, Y, "|||", S, K

    def weight(e):
        u,v = e
        if u == P[v]:
            return D[v] - D[u]
        return max(H[v]-H[u],1) + randint(0, 2*W/L)

    g = (dag if O else dgraph)(
        N, D = K,
        nw = (lambda: randint(MIN_H, Y)) if R else (lambda n: H[n]),
        w  = (lambda: randint(MIN_C, W)) if R else weight
    )
    D[0] = randint(1, 2*W/L)
    H[0] = D[0] + randint(1, 2*(Y-W)/L)
    for i in range(1,N):
        g += (P[i], i)
        D[i] = D[P[i]] + randint(1, 2*W/L)
        H[i] = D[i] - D[P[i]] + H[P[i]] + randint(1, 2*(Y-W)/L)
    g.addedges(M-N+1) # aggiunge solo archi con (v-u) <= K
    g.zero_based = True
    if not O:
        g.shuffle()
    print g


if __name__ == "__main__":
    if len(argv) != 9:
        print(usage)
        exit(1)

    N, M, L, W, H, O, R, S = map(int, argv[1:])
    seed(S)

    run(N, M, L, W, H, O, R)
