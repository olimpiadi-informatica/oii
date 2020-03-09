#!/usr/bin/env python2
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit, stderr
from random import randint, seed, shuffle, choice
from graph import *

usage = """Generatore di "gerarchie".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""

DEBUG = False
cases = 0

def start_case(N):
    global cases
    print
    N = randint(20, N) if N > 20 else N
    print N
    cases += 1
    return N

def stella(N):
    return dgraph(N, type='star')

def linea(N):
    return dgraph(N, type='path')

def casuale(N):
    return dgraph(N, type='tree')

if __name__ == "__main__":
    if len(argv) < 3:
        print usage
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    print T

    testcases = [(stella,MAXN,0)]*2 + [(linea,MAXN,0)]*4 + [(casuale,MAXN,1), (casuale,MAXN,-1)] + [(casuale,MAXN,0)]*8
    shuffle(testcases)
    testcases = [(casuale,n,0) for n in [5,10,15]] + testcases
    for type, N, order in testcases:
        g = type(start_case(N))
        g.shuffle()
        N = g.N()
        parents = [-1 for _ in xrange(N)]
        for e in g:
            parents[e[1]] = e[0]
        #print("parents: ", parents)
        inv = range(N)
        for i in range(N):
            inv[g.lbl[i]] = i
        #print("inv: ", inv)
        values = list(reversed(range(N))) if order == 1 else range(N)
        if order == 0:
            shuffle(values)
        for i in xrange(N):
            p = parents[inv[i]]
            if p != -1:
                p = g.lbl[p]
            print p, values[inv[i]]

    assert cases == T
