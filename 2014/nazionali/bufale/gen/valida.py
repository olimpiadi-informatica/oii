#!/usr/bin/env python

from sys import argv, exit, stderr
import os

N_lim = [(0, 10 * 1000 * 1000),
         (8,                8),
         (2,         5 * 1000),
         (2,      1000 * 1000),
         (2,         5 * 1000),
         (2,      1000 * 1000),
         (2, 10 * 1000 * 1000)]
MP_lim = [(0, 10 * 1000 * 1000),
          (0,               10),
          (0,                1),
          (0,                1),
          (0,               10),
          (0,               10),
          (0, 10 * 1000 * 1000)]


def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def assert_in(x, x_lims):
    assert x_lims[0] <= x <= x_lims[1]

def run(f, subtask):
    N = int(f[0])
    assert_in(N, N_lim[subtask])
    assert N % 2 == 0
    assert len(f) == N + 1

    for i in xrange(N):
        M, P = [int(x) for x in f[i+1].split()]
        assert_in(M, MP_lim[subtask])
        assert_in(P, MP_lim[subtask])

    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    st = 0
    if len(argv) >= 3:
        st = int(argv[2])
    exit(run(f, st))
