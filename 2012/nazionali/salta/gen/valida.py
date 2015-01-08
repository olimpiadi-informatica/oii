#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) == 2)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 1)
    N, = prima
    assert(1 <= N <= MAXN)
    seconda = [int(x) for x in f[1].split()]
    assert(len(seconda) == N)
    assert(0 <= min(seconda))
    assert(max(seconda) <= MAXVI)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    f = open(argv[1]).readlines()
    exit(run(f))


