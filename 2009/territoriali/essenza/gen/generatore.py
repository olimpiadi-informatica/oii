#!/usr/bin/env python2

import os, random, sys


def run():
    if len(sys.argv) < 5:
        print """Usage: %s N K MaxValue Offset Seed
  N = length (1 - 1000)
  K = validity (1 - 1000)
  MaxValue = max price
  Seed = random seed
""" % os.path.basename(sys.argv[0])
        return 1

    N, K, MV, Seed = [int(x) for x in sys.argv[1:]]
    random.seed(Seed)

    print K, N
    for i in xrange(N):
        print (random.randint(1, Seed) * random.randint(1, Seed) * random.randint(1, Seed) * random.randint(1, Seed)) % random.randint(1, MV) + 1,
    print
            
if __name__ == '__main__':
    sys.exit(run())
        
