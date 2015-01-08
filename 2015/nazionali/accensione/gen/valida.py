#!/usr/bin/env python2

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)

num_righe = None
num_colonne = None
S = None

# 0            -> corretto
# altro numero -> non corretto
def run(f, st):
    N = int(f[0])
    vals = map(int, f[1].split())
    
    if not MINN <= N <= MAXN:
        return 1
    
    for v in vals:
        if not 0 <= v <= 1:
            return 2
    if len(vals) != N:
        return 3
    
    if st == 1:
        if N != 6:
            return 4
        if vals != [0, 1, 0, 1, 0, 0]:
            return 5
    
    elif st == 2:
        if N > 10:
            return 6
    
    elif st == 3:
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 101, 11251, 464197]
        for p in primes:
            if p <= N and vals[p-1] != 0:
                return 7
        
        notprimes = [1, 4, 6, 8, 9, 10, 12, 91, 39843]
        for n in notprimes:
            if n <= N and vals[n-1] != 1:
                return 8
    
    elif st == 4:
        if N > 1000:
            return 9
    
    elif st == 5:
        if N > 100000:
            return 10
    
    return 0

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
