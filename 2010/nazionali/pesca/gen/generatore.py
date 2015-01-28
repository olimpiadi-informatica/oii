#!/usr/bin/env python2

import sys
import logging
from numpy.random import seed, uniform, normal, shuffle, randint, sample
import numpy as np
from itertools import chain
from functools import partial

from limiti import *

def genera_punti_percorso(punti_x):
    y = 0
    for x in punti_x:
        try:
            if randint(0, 2) == 0:
                p = (x, y)
            else:
                if y+1 == x: continue
                y = randint(y+1, x)
                p = (x, y)
            yield p
        except:
            logging.exception('Cosa succede?')

def ripeti_alcuni(seq):
    for x in seq:
        yield x
        if randint(0, 3) > 0:
            yield x

def genera_percorso(M, l):
    punti_x = (np.array(sample(M/4)) * (l-2)) + 1
    punti_x = sorted(map(int, punti_x))

    punti_percorso = chain(genera_punti_percorso(ripeti_alcuni(punti_x)), [(l, l)])
    prev = (0, 0)
    for x, y in punti_percorso:
        if prev == (x, y): continue
        if prev[0] == x:
            yield y - prev[1]
        elif prev[1] == y:
            yield -(x - prev[0])
        else:
            yield -(x - prev[0])
            yield y - prev[1]
        prev = (x, y)

def run():
    logging.basicConfig(level=logging.INFO)

    try:
        N, P, M, G, S = map(int, sys.argv[1:6])
    except:
        logging.exception('Usage: %s N P M G S')
        return 1
    logging.info('Generating...')

    # check bounds
    assert (MinN <= N <= MaxN)
    assert (MinP <= P <= MaxP)
    assert (MinM <= M <= MaxM)
    assert (G in (1, 2, 3))

    seed(S)

    # genera il rettangolo
    l = randint(max(N/8, M), max(N, M+1))
    assert l > 2
    sx = randint(0, N - l)
    sy = randint(0, N - l)
    ex = sx + l
    ey = sy + l

    seq1 = np.array(list(genera_percorso(M, l)))
    seq2 = np.array(list(genera_percorso(M, l)))
    if randint(0, 3) == 0:
        seq2 *= -1
    else:
        seq1 *= -1

    # genera i pesci
    fishes = set()
    xmean = sx + l/2
    xsigma = l/2
    ymean = sy + l/2
    ysigma = l/2

    if G == 1:
        randomnumx = partial(normal, xmean, xsigma)
        randomnumy = partial(normal, ymean, ysigma)
    elif G == 2:
        randomnumx = partial(uniform, 0, N)
        randomnumy = partial(uniform, 0, N)

    if G == 3:
        fishes = []
        for x in xrange(N):
            for y in xrange(N):
                fishes.append((x, y))
        P = len(fishes)
    else:
        while len(fishes) < P:
            x = int(round(randomnumx()))
            y = int(round(randomnumy()))
            if x < 0: x = 0
            if y < 0: y = 0
            if x >= N: x = N-1
            if y >= N: y = N-1
            fishes.add((x, y))

    # output
    print P
    print sx+1, sy+1
    for x, y in fishes:
        print x+1, y+1

    out = sys.stdout
    for seq in (seq1, seq2):
        for c in seq:
            if c > 0:
                out.write('+%d ' % c)
            else:
                out.write('%d ' % c)
        out.write('0\n')

if __name__ == '__main__':
    sys.exit(run())
    
