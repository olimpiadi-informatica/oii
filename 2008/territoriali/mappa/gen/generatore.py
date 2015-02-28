#!/usr/bin/env python2

import os, random, sys


def do_path(m, N):
    p = [0, 0]
    for i in xrange(2):
        newp = [random.randint(0, N-1), random.randint(0, N-1)]
        connect(m, p, newp)
        p = newp
    connect(m, p, [N-1, N-1])

def connect(m, p1, p2):
    d = [p1[i] - p2[i] for i in xrange(2)]
    M = max([abs(d[0]), abs(d[1])])
    for i in xrange(M):
        m[p1[0] + (p2[0] - p1[0]) * i / M][p1[1] + (p2[1] - p1[1]) * i / M] = '*'


def run():
    if len(sys.argv) < 5:
        print """Usage: %s N M Fill Seed
  N = dimension (1 - 100)
  M = number of paths (1 -)
  Fill = random fill percentage (1 - 100)
  Seed = random seed
""" % os.path.basename(sys.argv[0])
        return 1

    N, M, Fill, Seed = [int(x) for x in sys.argv[1:]]
    random.seed(Seed)

    m = []
    for i in xrange(N):
        m.append(['+'] * N)

    m[0][0] = m[N-1][N-1] = '*'

    for i in xrange(M):
        do_path(m, N)

    for i in xrange(Fill * N * N / 100):
        m[random.randint(0, N-1)][random.randint(0, N-1)] = '*'

    print N
    for i in xrange(N):
        print ''.join(m[i])

if __name__ == '__main__':
    sys.exit(run())
