#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 1)
    P, = prima
    assert(1 <= P and P <= MaxIter)
    assert(len(f) == 2*P+1)
    for i in range(P):
        riga = [int(x) for x in f[2*i+1].split()]
        assert(len(riga) == 1)
        N, = riga
        assert(1 <= N and N <= MaxN)
        riga = [int(x) for x in f[2*i+2].split()]
        assert(len(riga) == N)
        assert(sum(riga) <= MaxSum)
        for j in riga:
            assert(1 <= j and j <= MaxVal)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


