#!/usr/bin/python

usage="""Generatore per "numeri".

Parametri:
* N (numero antipatico et massimo numero di rose/pianta)
* M (lunghezza dell'array di input)
* P (percentuale di zeri)
* Q (massimo numero di rose per pianta)
* S (seed)

Constraint:
* 1 <= N < %d
* 1 <= M < %d
* 0 <= P <= 100
* 0 <= Q <= N
""" % (MAXN, MAXM)

from sys import argv, exit
from numpy.random import seed, random, randint
from numpy import sqrt

from limiti import *

if len(argv) != 6:
    print usage
else:
    N, M, P, Q, S = [int(x) for x in argv[1:]]
    
    seed(S)

    assert (1 <= N and N <= MAXN)
    assert (1 <= M and M <= MAXM)
    assert (0 <= P and P <= 100)
    assert (0 <= Q and Q <= N)
    
    print N, M

    for i in xrange(M):
        r = 100* random()
        if r < P:
            print 0,
        else:
            r -= P
            m = Q*(Q+1)/2
            R = m - r*m/(100.0-P)
            print (int)((1 + sqrt(1 + 8*R)) / 2.0),
    print
        
