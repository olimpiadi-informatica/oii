#!/usr/bin/env pypy

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "nemesi".

Parametri:
* N (bambini)
* T (tipo di testcase: 0 = inimicizia simmetrica, 1 = ciclo grande, 2 = random, 3 = solo cicli, 4 = albero di fibonacci)
* C (lunghezza del ciclo nel caso T = 1)
* S (seed)

Constraint:
* 2 <= N <= %d
* 0 <= T <= 4
* 0 <= C <= N
""" % (MAXN)


def run(N, T, C):
	print N
	nemici = [0 for _ in xrange(N)]
	
	# inimicizia simmetrica
	if T == 0:
		assert(N%2 == 0)
		bambini = range(N)
		shuffle(bambini)
		for i in range(0, N, 2):
			nemici[bambini[i]] = bambini[i+1]
			nemici[bambini[i+1]] = bambini[i]
	
	# ciclo grande
	if T == 1:
		assert(C >= 2)
		ciclo = sample(range(N), C)
		fatto = [0]*N
		for i in range(C):
			nemici[ciclo[i]] = ciclo[(i+1)%C]
			fatto[ciclo[i]] = 1
		for i in range(N):
			if fatto[i] == 0:
				nemici[i] = randint(0, N-1)
				while nemici[i] == i:
					nemici[i] = randint(0, N-1)
		 
	# random
	if T == 2:
		for i in range(N):
			nemici[i] = randint(0, N-1)
			while nemici[i] == i:
				nemici[i] = randint(0, N-1)
	
	# solo cicli
	if T == 3:
		nemici = range(N)
		punti_fissi = True
		while punti_fissi:
			shuffle(nemici)
			punti_fissi = False
			for i in range(N):
				if nemici[i] == i:
					punti_fissi = True
					break

	# albero di fibonacci
	if T == 4:
		def fib(N, a):
			nemici = [a-1]
			while (2*len(nemici) <= N):
				nemici[-1] = a+2*len(nemici)-1
				nemici += [i+len(nemici) for i in nemici]
				nemici[-1] = a+len(nemici)-2
			return nemici
		nemici = fib(N,0)
		while (len(nemici) < N):
			t = len(nemici)-1
			nemici += fib(N-len(nemici),len(nemici))
			nemici[-1] = t
		bambini = range(N)
		shuffle(bambini)
		nemici2 = list(nemici)
		for i in xrange(N):
			nemici2[bambini[i]] = bambini[nemici[i]]
		nemici = nemici2
		

	print " ".join( map(str, nemici) )

if __name__ == "__main__":
	try:
		N, T, C, S = map(int, argv[1:])
	except ValueError:
		print usage
		exit(1)

	assert (2 <= N <= MAXN)
	assert (0 <= T <= 4)
	assert (0 <= C <= N)
	seed(S)
	run(N, T, C)
