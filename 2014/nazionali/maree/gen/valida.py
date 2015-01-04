#!/usr/bin/env python

from sys import argv, exit, stderr
import os

N_lim = [(0, 200 * 1000),
         (9,          9),
         (2, 100 * 1000),
         (2,   3 * 1000),
         (2, 100 * 1000),
         (2, 200 * 1000)]
M_lim = [( 0, 3 * 1000 * 1000),
         (10,             10),
         ( 2, 2 * 1000 * 1000),
         ( 2,       20 * 1000),
         ( 2, 2 * 1000 * 1000),
         ( 2, 3 * 1000 * 1000)]
T_lim = [(0, 1 * 1000 * 1000 * 1000),
         (5,                      5),
         (0,                      0),
         (0, 1 * 1000 * 1000 * 1000),
         (0, 1 * 1000 * 1000 * 1000),
         (0, 1 * 1000 * 1000 * 1000)]


def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def assert_in(x, x_lims):
    assert x_lims[0] <= x <= x_lims[1]

def run(f, subtask):
    edges = set()

    N, M, T = (int(x) for x in f[0].split())

    assert_in(N, N_lim[subtask])
    assert_in(M, M_lim[subtask])
    assert_in(T, T_lim[subtask])

    assert len(f) == M + 1

    for i in xrange(M):
        start, end = [int(x) for x in f[i+1].split()]
        assert_in(start, (0, N-1))
        assert_in(end, (0, N-1))
        assert start != end
        assert (start, end) not in edges
        edges.add((start, end))

    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    st = 0
    if len(argv) >= 3:
        st = int(argv[2])
    exit(run(f, st))
