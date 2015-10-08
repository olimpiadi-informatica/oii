#!/usr/bin/env pypy

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "paletta".

Parametri:
* N (elementi da ordinare)
* T (tipo: -1 = random, 0 = ordinabile random, 1+ = disordinato con T scambi)
* S (seed)

Constraint:
* 1 <= N <= %d
* T >= -1
""" % (MAXN,)


def run(N, T):
	print N
	V = range(N)
	if T<0:
		if (randint(0,1) == 0):
			shuffle(V)
		else:
			a = 2*randint(0,N/2);
			b = 2*randint(0,(N-1)/2)+1;
			V[a], V[b] = V[b], V[a]
	elif T==0:
		tempV = V[0::2]
		shuffle(tempV)
		V[0::2] = tempV
		tempV = V[1::2]
		shuffle(tempV)
		V[1::2] = tempV
	elif T>0:
		for i in range(T):
			j = randint(0, N-3)
			V[j], V[j+2] = V[j+2], V[j]
	print " ".join( map(str, V) )

if __name__ == "__main__":
	try:
		N, T, S = map(int, argv[1:])
	except ValueError:
		print usage
		exit(1)
		

	assert (1 <= N <= MAXN)
	assert (-1 <= T)
	seed(S)
	run(N, T)
