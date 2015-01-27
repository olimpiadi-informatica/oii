#!/usr/bin/env python2
# Roberto

import sys
from operator import itemgetter, attrgetter
from numpy.random import seed, randint, permutation
import numpy as np
from limiti import *

def run():
    try:
        N, M, OnlyGreen, Seed = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4])
    except:
        print 'Usage: %s N M OnlyGreen Seed' % sys.argv[0]
        return 1

    # check input params and start seed
    assert (3 <= N <= MaxN)
    assert (N < M <= MaxM)
    seed(Seed)

    edges = []
    # generate test case: cycle of N/4 green edges
    cyclelen = randint(max(3, N/4), max(3,N/2)+1 )
    for i in range(cyclelen-1):
        edges += [ (i, i+1, 1) ]
    edges += [ (0, cyclelen-1, 1) ]

    # add other green edges without creating cycles
    for j in range(N-1,cyclelen-1,-1):
        i = randint(0, j)
        edges += [ (i,j,1) ]

    # decide if only green
    if OnlyGreen:
        # generate another cycle of N/4 green edges
        cyclelen = randint(max(3, N/4), max(3,N/2)+1 )
        for i in range(cyclelen-1):
            edges += [ (i, i+1, 1) ]
        edges += [ (0, cyclelen-1, 1) ]

        # add other green edges without creating cycles
        for j in range(N-1,cyclelen-1,-1):
            i = randint(0, j)
            edges += [ (N+i,N+j,1) ]
        N *= 2
    else:
        # add many random red edges, some will be discarded later
        for l in range(2*M):
            j = i = randint(0, N)
            while j == i:
                j = randint(0, N)        
            if i > j:
                i,j = (j,i)
            edges += [ (i,j,0) ]

    # remove duplicates
    edges.sort()
    last = (-1,-1,0)
    R = []
    for e in edges:
        assert e[0] < e[1]
        if e[0]==last[0] and e[1]==last[1]:
            R[len(R)-1] = e
        else:
            R += [e]
        last = e

    
    T = permutation( sorted( R, key=itemgetter(2), reverse=True )[0:M] )
    I = permutation([i+1 for i in range(N)])

    # output test case
    cout = sys.stdout
    cout.write('%d %d\n' % (N,len(T)))
    for x in T:
        assert 0 <= x[0] < N and 0 <= x[1] < N
        cout.write('%d %d %d\n' % (I[x[0]],I[x[1]],x[2]))


# main
if __name__ == '__main__':
    sys.exit(run())
