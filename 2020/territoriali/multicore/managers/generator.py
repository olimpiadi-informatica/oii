#!/usr/bin/env python2
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit, stderr
from random import randint, seed, shuffle, choice

usage = """Generatore di "cores".

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
    cases += 1
    return N

def randgen(N, M = None):
    if M is None:
        M = N
    return lambda : randint(1, N) if randint(0,19) > 0 else randint(1,M)

def constgen(N):
    N = randint(1, N)
    return lambda : N

if __name__ == "__main__":
    if len(argv) < 3:
        print usage
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    print T

    testcases = [(constgen(MAXC),randgen(MAXP/100),MAXN) for _ in xrange(3)] + [(randgen(MAXC),constgen(MAXP/100),MAXN) for _ in xrange(3)] + [(randgen(MAXC),randgen(1000),MAXN)]*5 + [(randgen(MAXC),randgen(MAXP/100),MAXN)]*12
    testcases = [(randgen(16),randgen(1000),N) for N in [5,10,15,20]] + testcases
    for Cg, Pg, N in testcases:
        N = start_case(N)
        C = [Cg() for _ in xrange(N)]
        P = [Pg() for _ in xrange(N)]
        B = randint(max(P), min(sum(P),MAXP))
        print N, B
        for i in xrange(N):
            print C[i], P[i]

    assert cases == T
