#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) >= 2)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 2)
    N, M = prima
    assert(1 <= N <= MAXN)
    assert(N <= M <= MAXM)
    assert(len(f) == M+1)

    edges = set()
    for riga in f[1:]:
        attuale = [int(x) for x in riga.split()]
        assert(len(attuale) == 2)
        assert(0 <= attuale[0] < N)
        assert(0 <= attuale[1] < N)
        edges.add(tuple(attuale))

    assert(len(edges) == M)

    left_side = []
    right_side = []
    for riga in f[1:N+1]:
        attuale = [int(x) for x in riga.split()]
        left_side += [attuale[0],]
        right_side += [attuale[1],]

    assert(sorted(left_side) == range(0,N))
    assert(sorted(right_side) == range(0,N))

    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


