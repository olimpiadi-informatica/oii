#!/usr/bin/env python2

from sys import argv, exit, stderr
import os

N_lim = [( 1, 20 * 1000 * 1000),
         (11,               11),
         ( 1,              500),
         ( 1,         5 * 1000),
         ( 1,  1 * 1000 * 1000),
         ( 1, 20 * 1000 * 1000)]
K_lim = (0, 1 * 1000 * 1000 * 1000)
S_lim = (0, 10)

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def assert_in(x, x_lims):
    assert x_lims[0] <= x <= x_lims[1]

def run(f, subtask):
    assert len(f) == 2

    N, K = (int(x) for x in f[0].split())
    assert_in(N, N_lim[subtask])
    assert_in(K, K_lim)

    S = [int(x) for x in f[1].split()]
    assert len(S) == N
    for i in xrange(N):
        assert_in(S[i], S_lim)

    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    st = 0
    if len(argv) >= 3:
        st = int(argv[2])
    exit(run(f, st))
