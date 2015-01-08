#!/usr/bin/env pypy

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f, st):
    assert(len(f) == 2)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 1)
    N, = prima
    assert (1 <= N <= MAXN_ST[st-1])

    trees = [int(x) for x in f[1].split()]
    
    assert (len(trees) == N)
    
    for h in trees:
      assert (1 <= h <= MAXH_ST[st-1])

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


