#!/usr/bin/env python3
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *
from valida import run as valida_run
import sys
import os
import string

def usage():
    print("Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0]), file=sys.stderr)
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
# per testare la correttezza dell'input, usate assert()
def run(f, st):
    valida_run(f, st)
    S, P = map(int, f[0].strip().split())
    p = f[2].strip().split()
    assert p == [p[0]] * P

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
