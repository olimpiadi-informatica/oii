#!/usr/bin/env pypy

# Utilizza la nuova libreria per la generazione di grafi in /util/gen_lib
# Compilare e piazzare Graph.so nella directory.

from limiti import *
from varie import *
from graph import *
from sys import argv, exit, stderr
import os
from random import choice, sample, shuffle, seed as rseed
try:
    from numpy.random import randint, seed as nseed
except:
    nseed = rseed
    from random import randint as _r
    def randint(A, B):
        return _r(A, B-1)

usage="""Generatore di "bottleneck".

Parametri:
* N (numero di nodi o di righe se T=2)
* M (numero di archi o di colonne se T=2)
* W1 (peso minimo)
* W2 (peso massimo)
* D (distanza tra i due)
* T (tipo di grafo: linea, ciclo, griglia, grafo, grafo a potenziali)
* S (seed)

Constraint:
* 2 <= N <= %d
* N-1 <= M <= %d
* 2 <= N, M <= %d se T=2
* 0 <= W1 <= W2 <= %d
* 1 <= D <= N-1 o N+M-2 se T=2
* -1 <= T <= 3
""" % (MAXN,MAXM,MAXC,MAXW)


def run(N,M,W1,W2,D,T):
    e = []
    x = [0,0]
    if 0 <= T < 2:
        x[0] = randint(1,N-D+1)
        x[1] = x[0] + D
        shuffle(x)
        print N, N-1+T, x[0], x[1], -1, -1
        g = ugraph(N,type='path' if T == 0 else 'cycle')
        g.w = lambda: randint(W1,W2+1)
        print g.printedges()

    if T == 2:
        R = N
        C = M
        h = randint(max(0,D-C+1),min(D+1,R))
        w = (D-h)*(2*randint(0,2)-1)
        x[0] = [randint(1,R-h+1),randint(1-min(w,0),C-max(w,0)+1)]
        x[1] = [x[0][0]+h,x[0][1]+w]
        shuffle(x)
        print R*C, 2*R*C-R-C, (x[0][0]-1)*C+x[0][1], (x[1][0]-1)*C+x[1][1], R, C
        g = ugraph(C,type='path') * ugraph(R,type='path')
        g.w = lambda: randint(W1,W2+1)
        print g.printedges()

    if T == 3:
        g = ugraph(D+1, type='path') + ugraph(N-D-1)
        g.w = lambda: randint(W1,W2+1)
        perm = range(g.N())
        shuffle(perm)
        g.shuffle(perm)
        g.connect()
        g.addedges(M-N+1)
        print N, M, perm[0]+1, perm[D]+1, -1, -1
        print g.printedges()

    if T == -1:
        g = ugraph(D+1, type='path') + ugraph(N-D-1)
        g.w = lambda: randint(W1,W2+1)
        k = range(D+1) + [randint(1,D) for i in xrange(N-D-1)]
        l = [[] for i in xrange(D+1)]
        for i in xrange(N):
            l[k[i]] += [i]
            if i != D:
                g += (i, k[i]+1)
        
        for i in xrange(D):
            for x in l[i]:
                for y in l[i+1]:
                    if g.M() >= M:
                        break
                    g += (x,y)
        
        perm = range(g.N())
        shuffle(perm)
        g.shuffle(perm)
        print N, g.M(), perm[0]+1, perm[D]+1, -1, -1
        print g.printedges()

if __name__ == "__main__":
    if len(argv) != 8:
        print usage
        exit(1)

    N, M, W1, W2, D, T, S = map(int, argv[1:])
    
    # su seed non positivo copia un input di esempio dal .tex
    if S <= 0:
        print extract_input(cmsbooklet=True)[-S],
        exit(0)
    
    assert(2 <= N <= (MAXC if T==2 else MAXN))
    assert(T < 2 or (2 if T==2 else N-1) <= M <= (MAXC if T==2 else MAXM))
    assert(0 <= W1 <= W2 <= MAXW)
    assert(1 <= D <= N-1+(M-1 if T == 2 else 0))
    assert(-1 <= T <= 3)
    
    nseed(S)
    rseed(S)
    run(N,M,W1,W2,D,T)
