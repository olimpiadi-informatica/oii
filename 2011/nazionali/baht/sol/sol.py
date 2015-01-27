#!/usr/bin/env python2
# Roberto

import sys

MaxSum = 2**31 - 1

cin = sys.stdin
linea = cin.readline()
P = [int(x) for x in linea.split()][0]

for i in range(P):
    linea = cin.readline()
    N = [int(x) for x in linea.split()][0]
    linea = cin.readline()
    S = [int(x) for x in linea.split()]

    # check input params
    assert( N == len(S))
    assert( sum(S) < MaxSum )

    #start computation
    maxi = 0

    for x in sorted(S):
        if maxi+1 < x:
            break
        else:
            maxi += x

    assert( sum(S) != maxi )
    out = sys.stdout
    out.write('%d\n' % (maxi+1))
    
