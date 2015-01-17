#!/usr/bin/env python2

MAXN = 8
MAXM = 8

usage="""Generatore per "quasipal" scritto da Matteo Boscariol.

Parametri:
* M (numero di righe)
* N (numero di cifre decimali)
* P (percentuale di zeri)
* S (seed)

Constraint:
* 2 <= M <= %d
* 2 <= N <= %d
* 0 <= P <= 100
""" % (MAXM, MAXN)

from numpy.random import seed, randint, permutation
from sys import argv

if len(argv)!=5:
	print usage
	exit(1)
	
M, N , P, S = [int(x) for x in argv[1:]]
seed(S)

assert(2<=N and N<=MAXN and 2<=M and M<=MAXM and 0<=P and P<=100)

grid = [ [0]*N for j in xrange(M)]

for i in xrange((M+1)/2):
	for j in xrange(N):
		grid[i][j]=grid[M-1-i][j]=randint(1,10)		
		
for i in xrange(M):
	for j in xrange(N):
		if(randint(1,101)<=P):
			grid[i][j]=0

grid = permutation(grid)

print M,N
for i in xrange(M):
	s = ""
	for j in xrange(N):
		s+=repr(grid[i][j])
	print s

