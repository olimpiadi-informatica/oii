#!/usr/bin/env python2

#GENERATORE per GALATTICI 2012 modificato per ricercare
# la parola chiave piu' corta con automa aciclico

from limiti import *

usage="""Generatore per "galattici" scritto da Giorgio Audrito.

Parametri:
* N (numero di stati)
* M (numero di transizioni)
* U (garantisce una soluzione lunga U)
* L (ogni soluzione e' lunga almeno L)
* S (seed)

Constraint:
* 2 <= N <= %d
* 2 <= M <= %d
* 1 <= L <= U <= N-1
* 1 <= L <= U <= M
* M <= N(N-1)/2
* M <= (N-L+2)(N-L-1)/2 + N-1
""" % (MAXN, MAXM)

from sys import argv, exit, stderr
import os
from numpy.random import seed, random
from random import choice, sample, shuffle, randint

def makegraph(N, M, U, L):

    # divido i nodi 1..N in L zone,
    # controllando che la divisione scelta mi consenta
    # di mettere davvero M archi
    znok = False
    while not znok:
        zones = [1]
        zones.extend( sample(range(2,N), L-1) )
        zones.extend( [N, N+1] );
        zones.sort()
        znCapacity = [ (zones[i+1]-zones[i])*(2*zones[i+2]-zones[i+1]-zones[i]-1)/2 for i in range(L) ]
        znTot = sum( znCapacity )
        if M <= znTot:
            znok = True

    # creo un cammino di lunghezza U
    # prima mi faccio un piano di quanti nodi mettere in ogni zona,
    # almeno uno e massimo quanti ce ne sono,
    # scelti in maniera uniforme
    plan = [ 1 for i in range(L+1)  ]
    plan[0] = 0
    for i in range(L):
        znCapacity[i] -= 1
        znTot -= 1
    zn = 0
    planscheme = sample( range(1,N-L), U-L )
    planscheme.sort()
    for i in planscheme:
        while i >= zones[zn+1]-zn-1:
            zn += 1
        plan[zn] += 1
        znCapacity[zn] -= 1
        znTot -= 1
    # poi mi faccio il cammino
    path = [1]
    path.extend( sample(range(2,zones[1]), plan[0]) )
    for i in range(1,L+1):
        path.extend( sample(range(zones[i],zones[i+1]), plan[i]) )
    path.sort()

    # creo una lista di adiacenza con il cammino scelto
    adiacenza = [ set([]) for i in range(N) ]
    for i in range(U):
        adiacenza[path[i]].add( path[i+1] )
    # aggiungo altri archi a caso
    edge = [0,0]
    for i in range(U,M):
        nedge = randint(0,znTot-1)
        edzone = 0
        while nedge >= znCapacity[edzone]:
            nedge -= znCapacity[edzone]
            edzone += 1
        edge[0] = zones[edzone]
        while nedge >= zones[edzone+2] - edge[0] - 1 - len(adiacenza[edge[0]]):
            nedge -= zones[edzone+2] - edge[0] - 1 - len(adiacenza[edge[0]])
            edge[0] += 1
        edge[1] = choice( list(set(range(edge[0]+1,zones[edzone+2]))
                               - adiacenza[edge[0]]) )
        assert(edge[1] not in adiacenza[edge[0]])
        adiacenza[edge[0]].add( edge[1] )
        znCapacity[edzone] -= 1
        znTot -= 1
    return adiacenza

def valida(N, adiacenza):
    return True;

def run(N, M, U, L, S):
    seed(S)
    Validato = False
    while not Validato:
        adiacenza = makegraph(N, M, U, L)
        Validato = valida(N, adiacenza)
    # decido una permutazione dei nomi dei nodi
    nodeshuffle = range(2,N)
    shuffle( nodeshuffle )
    nodeshuffle.append( N )
    nodeshuffle.insert( 0, 1 )
    # converto adiacenza in lista di archi e mescolo
    out = []
    for i in range(1,N):
        for j in adiacenza[i]:
            out.append( [nodeshuffle[i-1],nodeshuffle[j-1]] )
    shuffle( out )
    # stampo
    print N, M
    for i in out:
        print i[0], i[1], chr(randint(ord('a'), ord('z')))

if __name__ == "__main__":
    if len(argv) != 6:
        print usage
        exit(1)

    N, M, U, L, S = [int(x) for x in argv[1:]]
    assert (2 <= N and N <= MAXN)
    assert (2 <= M and M <= MAXM)
    assert (1 <= L <= U <= N-1)
    assert (1 <= L <= U <= M)
    assert (M <= N*(N-1)/2)
    assert (M <= (N-L+2)*(N-L-1)/2 + N-1)
    run(N, M, U, L, S)
