#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "sbarramento" scritto da Matteo Boscariol.

Parametri:
* N (dimensione del campo di battaglia)
* S (seed)

Constraint:
* 2 <= N <= %d
""" % MAXN

from numpy.random import seed, randint
from sys import argv

if len(argv) != 3:
	print usage
	exit(1)

N, S = map(int, argv[1:])
seed(S)

assert 2 <= N <= MAXN

visti = set()

print N, randint(1, N+1)
for i in xrange(N):
    a, b = randint(1, N+1), randint(1, N+1)

    while (a, b) in visti:
        a, b = randint(1, N+1), randint(1, N+1)

    visti.add((a, b))
    print a, b
