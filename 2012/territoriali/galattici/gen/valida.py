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
    assert(len(prima) == 3)
    M, N, K = prima
    assert(2 <= M and M <= MAXM)
    assert(2 <= N and N <= MAXN)
    assert(2 <= K and K <= MAXK)
    seconda = [x for x in f[1].split()]
    assert(len(seconda) == K)
    for i in seconda:
        assert(i in "abcdefghijklmnopqrstuvwxyz")
    assert(len(f) == M+2)
    for i in range(2, M+2):
        riga = [x for x in f[i].split()]
        assert(len(riga) == 3)
        a, b, c = riga
        a = int(a)
        b = int(b)
        assert(1 <= a and a <= N)
        assert(1 <= b and b <= N)
        assert(c in "abcdefghijklmnopqrstuvwxyz")
    # Nota: la presenza di una tripletta per ogni necessita` viene
    # controllata dal solutore.
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


