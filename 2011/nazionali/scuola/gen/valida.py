#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
from math import log
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) == 1)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 2)
    N, P = prima
    assert (2 <= N and N <= MAXN)
    assert (P == 1 or P == 2)
    if (P == 2):
        assert(int(log(N, 2)) == log(N, 2))
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


