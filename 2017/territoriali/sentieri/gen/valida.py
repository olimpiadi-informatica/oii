#!/usr/bin/env pypy

from limiti import *

import os
import sys

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt" % \
        os.path.basename(sys.argv[0])
    sys.exit(1)

def run(f):
    assert(len(f) >= 2)
    prima = map(int, f[0].split())
    assert(len(prima) == 3)
    N, A, B = prima
    assert(len(f) == A+B+1)
    assert(5 <= N <= MAXN)
    assert(10 <= A+B <= MAXM)
    for i in xrange(A + B):
        riga = map(int, f[i+1].split())
        assert(len(riga) == 2)
        a, b = riga
        assert(1 <= a <= MAXN)
        assert(1 <= b <= MAXN)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    f = open(sys.argv[1]).readlines()
    sys.exit(run(f))
