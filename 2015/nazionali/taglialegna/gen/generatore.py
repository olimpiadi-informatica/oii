#!/usr/bin/env pypy

from limiti import *
from varie import *
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

usage="""Generatore di "taglialegna".

Parametri:
* N (numero di alberi)
* H (altezza massima)
* M (numero di sottointervalli in cui dividere per generare l'input)
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= H <= %d
""" % (MAXN,MAXH)


def fill_interval(L,H):
    # Riempio un intervallo in modo che gli alberi non caschino fuori
    assert L > 0
    return [ randint(0, min(H, i+1, L-i))+1 for i in range(L) ]

def run(N,H,M):
    
    print N
    
    if M == 0:
        # Una istanza (quasi) priva di alberi di altezza 1 sarebbe molto facile,
        # quindi fisso una certa quantita' di alberi ad altezza 1
        short = randint(0,N+1)
        trees = [randint(2,H+1) for _ in xrange(N-short)] + ([1,]*short)
        shuffle(trees)
        
        for i in trees:
          print i,
  
    else:
        # Divido in sottointervalli, in modo che sottointervalli diversi non si influenzino
        assert M <= N
        
        division_points = [0] + sample(range(1,N), M-1) + [N]
        division_points.sort()
        
        partition = [ division_points[i+1] - division_points[i] for i in xrange(M) ]
        
        for L in partition:
            interval = fill_interval(L,H)
            for a in interval:
                print a,

    

if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    N, H, M, S = map(int, argv[1:])
    
    # Finche' generiamo elementi distinti, non ha senso avere L<3.
    assert (1 <= N <= MAXN)
    assert (1 <= H <= MAXH)

    # su seed non positivo copia un input di esempio dal .tex
    if S <= 0:
        print extract_input(cmsbooklet=True)[-S],
        exit(0)
    nseed(S)
    rseed(S)
    
    run(N,H,M)
