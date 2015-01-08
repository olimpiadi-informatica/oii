#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "fermata".

Parametri:
* N  (primo numero in input)
* ST (numero di stati)
* D  (massimo valore assoluto dei salti)
* S  (seed)

Constraint:
* 2 <= N <= %d
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def run(N, ST, D, S):
    nseed(S)
    rseed(S)
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

if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    N, ST, D, S = [int(x) for x in argv[1:]]
    run(N, ST, D, S)
