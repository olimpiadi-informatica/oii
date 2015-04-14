#!/usr/bin/env pypy

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f, st):
    N, R = map(int, f[0].split())
    assert (2 <= N <= MAXN)
    assert (len(f) == N+1)

    s = set()
    for line in f[1:]:
        i, j = map(int, line.split())
        assert (1 <= i <= N)
        assert (1 <= j <= N)
        s.add((i, j))

    assert (len(s) == N)

    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(argv) == 3:
        st = int(argv[2])

    f = open(argv[1]).readlines()
    exit(run(f, st))
