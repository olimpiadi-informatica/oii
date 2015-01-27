#!/usr/bin/env python2
# Valida gli input per fuga, ma non controlla che ci siano cicli

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 2)
    N, M = prima
    assert(1 <= N and N <= MaxN)
    assert(1 <= M and M <= MaxM)
    assert(len(f) == M+1)
    for i in xrange(M):
        riga = [int(x) for x in f[i+1].split()]
        assert(len(riga) == 3)
        x, y, c = riga
        assert(1 <= x and x <= N)
        assert(1 <= y and y <= N)
        assert(c in [0, 1])
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


