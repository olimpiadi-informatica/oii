#!/usr/bin/env python2

import os, sys
import random

MinN, MaxN = 1, 100
MinD, MaxD = 1, 365
MinS, MaxS = 1, 365

def run():
    global MinN, MaxN, MinD, MaxD, MinS, MaxS
    
    if len(sys.argv) < 3:
        print 'Usage: %s N seed' % os.path.basename(sys.argv[0])
        return 1
    
    N, Seed = sys.argv[1:]
    random.seed(int(Seed))

    print N

    assert(MinN <= int(N) <= MaxN)

    thr = int(N) * 5
    MaxD, MaxS = min(thr, MaxD), min(thr, MaxS)

    missioni = []
    for i in xrange(int(N)):
        d, s = (random.randint(MinD, MaxD), random.randint(MinS, MaxS))
        if s < d:
            d, s = s, d
        missioni.append( (s, d) )

    missioni.sort()

    for i in xrange(int(N)):
        print "%d %d" % (missioni[i][1], missioni[i][0])
        
if __name__ == '__main__':
    sys.exit(run())
