#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) > 2)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 1)
    K, = prima
    seconda = [int(x) for x in f[1].split()]
    assert(len(seconda) == 1)
    N, = seconda
    assert(1 <= K <= MAXK)
    assert(1 <= N <= MAXN)
    assert(len(f) == N+2)
    for i in xrange(2, N+2):
        riga = [int(x) for x in f[i].split()]
        assert(len(riga) == 2)
        a, b = riga
        assert (0 <= a <= b < K)

    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


