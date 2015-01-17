#!/usr/bin/env python2

MAXN = 500

usage="""Generatore per "sbarramento" scritto da Matteo Boscariol.

Parametri:
* N (dimensione del campo di battaglia)
* S (seed)

Constraint:
* 2 <= N <= %d
""" % MAXN

from numpy.random import seed, randint
from sys import argv

if len(argv)!=3:
	print usage
	exit(1)

N , S = [int(x) for x in argv[1:]]
seed(S)

assert(2<=N and N<=MAXN)

print N, randint(1,N+1)
for i in xrange(N):
	print randint(1,N+1), randint(1,N+1)

