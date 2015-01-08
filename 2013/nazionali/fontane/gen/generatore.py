#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "fontane".

Parametri:
* N (numero tratti percorso)
* M (numero fontanelle)
* F (fontanelle lungo il percorso)
* T (soluzione attesa)
* X (dimensione X della mappa)
* Y (dimensione Y della mappa)
* K (numero del subtask: se K==1 allora N==1, se K==2 allora N==4)
* Seed

Constraint:
* 1 <= N <= %d
* 0 <= F <= M <= %d
* 2 <= X,Y <= %d
* 1 <= T <= %d
* 1 <= K <= 3
""" % (MAXN,MAXM,MAXX,MAXT)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

TRIES = 10

def randbetween(a, b):
    return randint(min(a,b),max(a,b)+1)

def randcentered(a, b, c):
    x = randint(a,b)
    y = randint(a,b)
    return x if (abs(x-c) < abs(y-c)) else y

def run(N, S, P, T, X, Y, K, Seed):
    nseed(Seed)
    rseed(Seed)
    piano_stazioni = [randint(N) for i in xrange(P)]
    piano_stazioni.sort()
    piano_stazioni.reverse()

    stazioni=set()
    rect=[randint(X)+1,randint(X-1)+1,randint(Y)+1,randint(Y-1)+1]
    if rect[1] >= rect[0]:
        rect[1] += 1
    if rect[3] >= rect[2]:
        rect[3] += 1
    new=[randint(X)+1,randint(Y)+1]
    if K == 2:
        new=[rect[0],rect[2]]
    direction = randint(2)
    vertices = [[new[0], new[1]]]
    for i in xrange(N):
        old=list(new)
        direction = direction if (randint(4) == 0 and K != 2) else 1-direction
        if direction == 0:
            new[0]=randcentered(1,X,old[0] + (2*randint(2)-1)*(T*P/N))
            if old[0] <= new[0]:
                new[0] += 1
            if K == 2:
                new[0] = rect[0] if old[0] == rect[1] else rect[1]
        else:
            new[1]=randcentered(1,Y,old[1] + (2*randint(2)-1)*(T*P/N))
            if old[1] <= new[1]:
                new[1] += 1
            if K == 2:
                new[1] = rect[2] if old[1] == rect[3] else rect[3]
        vertices += [[ new[0], new[1]]]
        while (len(piano_stazioni) > 0 and piano_stazioni[-1] == i):
            piano_stazioni.pop()
            stazione_corrente = (randbetween(old[0],new[0]),randbetween(old[1],new[1]))
            for r in xrange(TRIES):
                if stazione_corrente in stazioni:
                    stazione_corrente = (randbetween(old[0],new[0]),randbetween(old[1],new[1]))
            stazioni.add(stazione_corrente)
    for i in xrange(S-len(stazioni)):
            stazione_corrente = (randint(X)+1,randint(Y)+1)
            for r in xrange(TRIES):
                if stazione_corrente in stazioni:
                    stazione_corrente = (randint(X)+1,randint(Y)+1)
            stazioni.add(stazione_corrente)

    stazioni = list(stazioni)
    print N, len(stazioni)
    for v in vertices:
        print v[0], v[1]
    shuffle(stazioni)
    for s in stazioni:
        print s[0], s[1]

def line_test(N, M, X0, X1, xi, y, P):
    fountains = set((randbetween(X0, X1), y) for i in xrange(M))
    while len(fountains)<M:
        fountains |= set((randbetween(X0, X1), y) for i in xrange(M-len(fountains)))

    segments = [(xi, y)]

    for i in xrange(N):
        l1 = xi - X0
        l2 = X1 - xi
        f = random()
        if f < float(l1)/(l1+l2):
            d = int(float(l1 * P)/100)
            xi = randbetween(X0, xi - d - 1)
        else:
            d = int(float(l2 * P)/100)
            xi = randbetween(X1, xi + d + 1)
        segments += [(xi, y)]
    return fountains, segments

def run_hard(N, M, X0, X1, P, Seed):
    """
    N: numero segmenti
    M: numero fontane
    X0: inizio linea
    X1: fine linea
    P: lunghezza percentuale del salto
    """
    nseed(Seed)
    rseed(Seed)

    fountains, segments = line_test(N/3, M/3, X0, X1, randbetween(X0, X1), 
        randbetween(1, MAXX), P)
    fountains2, segments2 = line_test(N/3-1, M/3, X0, X1, segments[-1][0], 
        randbetween(1, MAXX), P)
    fountains3, segments3 = line_test(N/3-1, M/3, X0, X1, segments2[-1][0], 
        randbetween(1, MAXX), P)

    F = fountains|fountains2|fountains3
    S = segments+segments2+segments3

    print len(S)-1, len(F)

    for s in S:
        print s[0], s[1]
    for f in F:
        print f[0], f[1]

def run_line(N, M, X0, X1, P, Seed):
    """
    N: numero segmenti
    M: numero fontane
    X0: inizio linea
    X1: fine linea
    P: lunghezza percentuale del salto
    """
    nseed(Seed)
    rseed(Seed)

    y = randbetween(1, MAXX)
    fountains = set((randbetween(X0, X1), y) for i in xrange(M))
    while len(fountains)<M:
        fountains |= set((randbetween(X0, X1), y) for i in xrange(M-len(fountains)))

    print N, M
    xi = randbetween(X0, X1)
    print xi, y

    for i in xrange(N):
        l1 = xi - X0
        l2 = X1 - xi
        f = random()
        if f < float(l1)/(l1+l2):
            d = int(float(l1 * P)/100)
            xi = randbetween(X0, xi - d - 1)
        else:
            d = int(float(l2 * P)/100)
            xi = randbetween(X1, xi + d + 1)
        print xi, y

    for f in fountains:
        print f[0], f[1]

def example_case():
    print """7 2
0 400
300 400
300 0
600 0
600 700
800 700
800 500
400 500
300 100
600 500"""

if __name__ == "__main__":
    if len(argv) < 2:
        print usage
        exit(1)

    ST = int(argv[1])
    if ST == 1:
        example_case()
    elif 2 <= ST <= 4:
        if len(argv) != 10:
            print usage
            exit(1)
        N, S, P, T, X, Y, K, Seed = [int(x) for x in argv[2:]]
        assert (1 <= N <= MAXN)
        assert (0 <= P <= S <= MAXM)
        assert (2 <= X <= MAXX)
        assert (2 <= Y <= MAXX)
        assert (1 <= T <= MAXT)
        assert (1 <= K <= 3)
        if K == 1:
            assert (N == 1)
        if K == 2:
            assert (N == 4)
        run(N, S, P, T, X, Y, K, Seed)
    elif ST == 5:
        N, M, X0, X1, P, Seed = [int(x) for x in argv[2:]]
        assert (1 <= N <= MAXN)
        assert (0 <= M <= MAXM)
        assert (1 <= X0 < X1 <= MAXX)
        assert (0 <= P <= 100)
        run_line(N, M, X0, X1, P, Seed)
    elif ST == 6:
        N, M, X0, X1, P, Seed = [int(x) for x in argv[2:]]
        assert (1 <= N <= MAXN)
        assert (0 <= M <= MAXM)
        assert (1 <= X0 < X1 <= MAXX)
        assert (0 <= P <= 100)
        run_hard(N, M, X0, X1, P, Seed)
