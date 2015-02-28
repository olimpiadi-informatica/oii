#!/usr/bin/env python

# Sintassi:
#  - gen.py seed nonperiod M N
#    generatore casuale semplice
#  - gen.py seed periodico k m N
#    genera k ripetizioni di lunghezza m (M = m * k <= N)

import os, sys
import random

def usage():
    print("""Uso:
  - %s seed M N
    genera una parola di M bit qualsiasi
  - %s seed k m N
    genera una parola di m bit e la ripete k volte (M = m * k)""" % (os.path.basename(sys.argv[0]), os.path.basename(sys.argv[0])))
    return 1
    
def run():
    if len(sys.argv) == 4:
        # non periodico
        seed, M, N = sys.argv[1:]
        seed = int(seed)
        M = int(M)
        N = int(N)
        
        random.seed(seed)

        if N < M: return usage()

        bit = []
        print("%d %d" % (M, N))
        for i in xrange(M):
            bit.append(str(random.randint(0, 1)))
        print "".join(bit)

    elif len(sys.argv) == 5:
        seed, k, m, N = sys.argv[1:]
        random.seed(seed)
        seed = int(seed)
        k = int(k)
        m = int(m)
        N = int(N)
        
        M = k * m
        if N < M: return usage()
        
        print "%d %d" % (M, N)
        bit = []
        for i in xrange(m):
            bit.append(str(random.randint(0, 1)))
        print "".join(bit) * k
    else:
        return usage()

if __name__ == '__main__':
    sys.exit(run())
                                                                                                                    
