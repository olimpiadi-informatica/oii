#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "gardaland" scritto da Giulio Carlassare.

Parametri:
* N (numero di nazioni)
* L (numero di informazioni)
* S (seed)

Constraint:
* 2 <= N <= %d
* N <= L <= %d
""" % (MAXN, MAXL)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, multinomial, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def run(N, L, S):
	nseed(S)
	rseed(S)
	risolvi = random() > 0.5
	print "risolvi:", risolvi
	print N, L
	out = []
	#Numero di indicazioni per ogni nazione
	indic_nazioni = list(multinomial(L-N, [1./N]*N))
	for i in range(len(indic_nazioni)):
		indic_nazioni[i] += 1
	#Numero di ragazzi in ogni nazione
	ragazzi = [0]*N
	for i in range(N):
		for j in range(indic_nazioni[i]):
			temp = randint(1, MAXR/indic_nazioni[i]);
			ragazzi[i] += temp
			out.append("{0} {1}".format(i, temp if (risolvi or (random() > .85)) else temp-1))
	shuffle(out)
	for x in ragazzi:
		print x
	for x in out:
		print x

if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)

    N, L, S = map(int, argv[1:])
    assert (2 <= N <= MAXN and N <= L <= 1000)
    run(N, L, S)
