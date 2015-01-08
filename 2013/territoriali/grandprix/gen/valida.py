#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    N, M = [int(x) for x in f[0].split()]
    assert(1 <= N <= MAXN)
    assert(1 <= M <= MAXM)
    assert(len(f) == 1+N+M)
    for i in range(N):
        assert( 1 <= int(f[i+1]) <= N )
    for i in range(M):
        riga = [int(x) for x in f[1+N+i].split()]
        assert(len(riga) == 2)
        assert( 1 <= riga[0] <= N )
        assert( 1 <= riga[1] <= N )
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))
