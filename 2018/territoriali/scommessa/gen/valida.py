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
def run(f):
    N = int(f[0].strip())
    assert(1 <= N <= MAXN)
    assert(N % 2 == 1)

    nums = map(int, f[1].strip().split(' '))
    nums.sort()
    ok = list(range(0, N))
    assert(nums == ok)
    
    return 0

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    f = open(sys.argv[1]).readlines()
    exit(run(f))
