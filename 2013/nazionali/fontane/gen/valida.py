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
    assert(len(prima) == 2)
    N, M = prima
    assert(1 <= N <= MAXN)
    assert(1 <= M <= MAXM)
    assert(len(f) == N+M+2)
    assert(set([len(x.split()) for x in f[1:]]) == set([2]))
    for i in xrange(N):
        prima = [int(x) for x in f[i+1].split()]
        dopo  = [int(x) for x in f[i+2].split()]
        assert(prima[0] == dopo[0] or prima[1] == dopo[1])
        assert(prima[0] != dopo[0] or prima[1] != dopo[1])

    fontane = set()
    for i in xrange(N+2, N+M+2):
        cur_f = tuple([int(x) for x in f[i].split()])
        fontane.add(cur_f)
    assert(len(fontane) == M)
    assert(max([max([int(x) for x in f[i].split()]) for i in xrange(1,N+M+2)]) <= MAXX)
    print "OK"
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


