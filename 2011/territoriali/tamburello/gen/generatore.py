#!/usr/bin/env python2

import sys
import os
from numpy.random import seed, random, randint

def usage():
    print >> sys.stderr, "Usage: %s Seed Periodo Ripetizioni QuasiPeriodica" % os.path.basename(sys.argv[0])
    sys.exit(1)

def periodica(l):
    N = len(l)
    for i in range(1, N):
        if N % i != 0: continue
        p = True
        for k in xrange(i, N):
            if l[k-i] != l[k]:
                p = False
                break
        if p:
            return True
    return False
            
    
if __name__ == "__main__":
    if len(sys.argv) != 5:
        usage()
    
    S = int(sys.argv[1])
    P = int(sys.argv[2])
    R = int(sys.argv[3])
    Q = int(sys.argv[4])
    # Se Q = 0, non succede niente. Se Q > 0, il periodo e` quasi
    # periodico di periodo Q con le ultime cifre cambiate
    N = P*R
    assert(2 <= N and N <= 10000)
    assert(0 < P)
    assert(0 < R)
    assert(0 == Q or (1 <= Q and P % Q == 0))
    
    print N
    seed(S)

    # Genera sequenza non-periodica lunga P
    if Q == 0:
        l = [randint(0,2) for i in range(P)]
        while periodica(l):
            l = [randint(0,2) for i in range(P)]
    if Q != 0:
        t = [randint(0,2) for i in xrange(Q)]
        l = t*(P/Q)
        l[-1] = 1-l[-1]
        while periodica(l):
            t = [randint(0,2) for i in xrange(Q)]
            l = t*(P/Q)
            l[-1] = 1-l[-1]
    for i in xrange(R):
        for j in xrange(P):
            print l[j],
    print
            
