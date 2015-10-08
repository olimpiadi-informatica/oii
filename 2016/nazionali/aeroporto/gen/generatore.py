#!/usr/bin/env pypy

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "aeroporto".

Parametri:
* R (numero di atterraggi)
* T (massimo dei tempi)
* A (minima lunghezza intervallo)
* B (massima lunghezza intervallo)
* K (minima risposta)
* S (seed)

Constraint:
* 1 <= R <= %d
* 0 <= A <= B <= T <= %d
* 0 <= K <= T/(R-1)
""" % (MAXR, MAXT)


def run(R, T, A, B, K):
	print R
	starts = [randint(0, T-A-K*(R-1)) for _ in xrange(R)]
	starts.sort()
	for i in xrange(R):
		starts[i] += i*K
	r = randint(0,B-A)
	for s in starts:
		if (randint(0,10) == 0):
			r = randint(0,B-A)
		a = [randint(0,r) for _ in xrange(2)]
		a.sort()
		print max(s-a[0],0), min(s+A+a[1]-a[0],T)


if __name__ == "__main__":
	try:
		R, T, A, B, K, S = map(int, argv[1:])
	except ValueError:
		print usage
		exit(1)

	assert (1 <= R <= MAXR)
	assert (0 <= A <= B <= T <= MAXT)
	assert (0 <= K <= (T-A)/(R-1))
	seed(S)
	run(R, T, A, B, K)
