#!/usr/bin/env pypy

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
    assert len(f) == 2, "Il file non contiene esattamente due righe"
    N = int(f[0])
    assert 0 < N <= MAXN, "Il valore di N non rispetta le assunzioni"
    signs = list(f[1])
    assert signs[-1] == "\n", "Il file non termina con uno newline"
    assert len(signs) == N, "I segni in input non sono N-1"
    signs = set(signs[:-1])
    assert len(signs) == 2 and "<" in signs and ">" in signs, "I segni non sono esattamente \"<\" e \">\""
    return 0

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
