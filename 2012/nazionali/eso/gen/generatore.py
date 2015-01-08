#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "eso".

Parametri:
* N (numero di sequenze)
* M (lunghezza di ciascuna sequenza)
* P (numero di coppie di parentesi tonde)
* Q (numero di coppie di parentesi quadrate)
* C (numero di classi di equivalenza in media)
* S (seed)

Constraint:
* M >= 3*(P+Q)
"""

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed
from string import maketrans

def eso(M, P, Q):
    global count1, count3, index
    while( True ):
        count1 = P
        count3 = Q
        index = 0
        espr = [-1 ] + create(M-2, False) + [-2 ]
        if (count1 == 0 and count3 == 0):
            return espr

def create(M, yespar):
    global count1, count3, index
    assert( M >= 1)
    if M <= 2:
        res = []
        while M > 0:
            res += [[randseq[index]]]
            index += 1
            M = M-1
        return res
    tipo = randint(1,3)   # parentesi o numero?
    if tipo == 1 and (count1 != 0 or count3 != 0) and yespar:
     	aperta = randint( 0,2 )*2 - 3  # [ oppure ( ?
	if aperta == -1:
            if count1 > 0:
                count1 = count1 -1 
            else:
                aperta = -3
                count3 = count3 -1
        else: # aperta = -3
            if count3 > 0:
                count3 = count3 -1 
            else:
                aperta = -1
                count1 = count1 -1
        chiusa = aperta-1
        return [[aperta] + create(M, False) + [chiusa]]
    else: 
         ell = randint(1,M)
         return create( ell, True ) + create( M-ell, True )

def gen_equiv( e ):
    e1 = e[1:-1]
    if randint(0,2) == 0:
        return [-1] + rec_equiv( e1 ) + [-2]
    else:
        shuffle(e1)
        return [-1] + rec_equiv( e1 ) + [-2]

def rec_equiv( s ):
    res = []
    for i in xrange( len(s) ):
        if s[i][0] == -1:
            s1 = s[i][1:-1]
            if randint(0,2) == 0:
                res += [[-1] + rec_equiv( s1 ) + [-2]]
            else:
                shuffle(s1)
                res += [[-1] + rec_equiv( s1 ) + [-2]]
        elif s[i][0] == -3:
            s1 = s[i][1:-1]
            if randint(0,2) == 0:
                res += [[-3] + rec_equiv( s1 ) + [-4]]
            else:
                s1.reverse()
                res += [[-3] + rec_equiv( s1 ) + [-4]]
        else:
            res += [s[i]]
    return res

def flatten( e ):
    s = str( e )
    return s.translate(None, "[]," )

def run(N, M, P, Q, C, S):
    global randseq
    nseed(S)
    rseed(S)
    last = 0
    randseq = []
    for i in xrange(M+1):
        last += randint(1,10)
        randseq += [last]
    shuffle( randseq )
    #print N, M, P, Q, C, S
    origM = M
    M -= 2*(P+Q)
    e = eso(M, P, Q)
    seqs = [flatten(e)]
    for i in xrange( N-1 ):
        if randint(0,N) < C:
            e = eso(M, P, Q)
        else:
            e = gen_equiv( e )
        seqs += [flatten(e)] 
    seqs = list(set(seqs))
    shuffle( seqs )
    print len(seqs), origM
    for i in xrange(len(seqs)):
        print "%s" % seqs[i]


if __name__ == "__main__":
    #print >> stderr, "Cambiare il generatore!"
    if len(argv) != 7:
        print usage
        exit(1)
    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    N, M, P, Q, C, S = [int(x) for x in argv[1:]]
    assert (MAXM >= M >= 3*(P+Q))
    assert ( 1 <= C <= N <= MAXN )
    run(N, M, P, Q, C, S)
