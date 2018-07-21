#!/usr/bin/env python2
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
# per testare la correttezza dell'input, usate assert()
def run(f, st):
    assert len(f) == 2
    N = int(f[0])
    altezze = map(int, f[1].split())

    assert 1 <= N <= MAXN
    assert len(altezze) == N

    for a in altezze:
        assert 1 <= a <= MAXA

    if st == 2:
        assert len(set(altezze)) == 1

    if st == 3:
        # TODO: check gia' risolta o irrisolvibile
        assert N <= 5000

    if st == 4:
        # TODO: check gia' risolta o irrisolvibile
        pass

    if st == 5:
        assert N <= 100

    if st == 6:
        assert N <= 1000

    if st == 7:
        assert N <= 3000

    if st == 8:
        assert N <= 100000

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
