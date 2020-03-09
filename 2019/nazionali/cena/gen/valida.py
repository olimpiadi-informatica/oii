#!/usr/bin/env python3
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *

import sys
import os
import string

def usage():
    print("Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0]), file=sys.stderr)
    sys.exit(1)


# 0            -> corretto
# altro numero -> non corretto
# per testare la correttezza dell'input, usate assert()
def run(f, st):
    assert len(f) == 3
    S, P = map(int, f[0].strip().split())
    assert 1 <= S <= MAXS
    assert 1 <= P <= MAXP
    s = list(map(int, f[1].strip().split()))
    p = list(map(int, f[2].strip().split()))
    assert len(s) == S
    assert len(p) == P
    counter = dict()
    for c in p:
        if c not in counter:
            counter[c] = 0
        counter[c] += 1
        assert 0 <= c < MAXT
        assert counter[c] <= MAXrep

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    sys.exit(run(f, st))
