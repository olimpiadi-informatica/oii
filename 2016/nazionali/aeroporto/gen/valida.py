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
    assert(len(f) > 1)
    R = int(f[0])
    assert(len(f) == R+1)
    
    LastBegin = 0
    for i in range(0, R):
		    NextLine = [int(x) for x in f[i+1].split()]
		    assert(len(NextLine) == 2)
		    A, B = NextLine
		    assert(0 <= A <= B <= MAXT)
		    assert(LastBegin <= B)
		    LastBegin = max(LastBegin, A)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
