#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "Fermata".

Parametri:
* K  (tipo di generazione)
* S  (seed)

* Se K == 0:
  Generazione random:
  * N  (primo numero in input)
  * ST (numero di stati)
  * D  (massimo valore assoluto dei salti)

* Se K == 1:
  Generazione a catene e cicli:
  * N  (numero di celle)
  * S  (numero di stati)
  * Nchain (numero di catene che conducono al termine)
  * Kchain (lunghezza di ogni catena)
  * Ncycle (numero di cicli)
  * Kcycle (lunghezza di ogni ciclo)

Constraint:
* 2 <= N <= %d
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

import cycler

def run(N, ST, D):
    transitions = []
    characters = [0 for _ in xrange(N)]
    for i in xrange(N-1, 0, -1):
        min_delta = -i
        max_delta = N-1-i
        good_characters = []
        for j, t in enumerate(transitions):
            if min(t) >= min_delta and max(t) <= max_delta:
                good_characters += [j]
        choice = randint(0, len(good_characters)+1)
        if choice == len(good_characters):
            # Aggiungi un nuovo elemento.
            transitions.append([randint(max(min_delta, -D), min(max_delta,D)) for _ in xrange(ST)])
            characters[i] = len(transitions)-1
        else:
            characters[i] = good_characters[choice]
    characters[0] = randint(0, len(transitions))
    C = len(transitions)
    print N, ST, C
    for cur_st in range(0,ST):
        for cur_c in range(0,C):
            print cur_st, cur_c, randint(0,ST), transitions[cur_c][cur_st]
    for i in xrange(0,N):
        print characters[i]

def example_case():
    print """5 2 3
0 0 1 -2
0 1 0 -2
0 2 0 1
1 0 1 -1
1 1 0 -1
1 2 0 2
0
2
1
0
1"""

if __name__ == "__main__":
    S, K = map(int, argv[1:3])
    args = map(int, argv[3:])

    if (K == 0 and len(args) != 3) or \
       (K == 1 and len(args) != 6):
        print usage
        exit(1)

    nseed(S)
    rseed(S)

    if K == -1:
        example_case()
    elif K == 0:
        run(*args)
    else:
        cycler.genera(*args)
