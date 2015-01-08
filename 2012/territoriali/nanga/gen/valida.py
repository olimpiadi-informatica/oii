#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) >= 1)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 1)
    N, = prima
    assert(2 <= N and N <= MAXN)
    for i in range(1, N+1):
        riga = [int(x) for x in f[i].split()]
        assert(len(riga) == 1)
        disl, = riga
        assert(-MAXP <= disl and disl <= MAXP)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


