#!/usr/bin/env pypy

from limiti import *

import os
import sys

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt" % \
        os.path.basename(sys.argv[0])
    sys.exit(1)

def run(f):
    assert(len(f) == 1)
    G, P = map(int, f[0].split())
    assert(10 <= G <= MAXG)
    assert(2 <= P <= MAXP)
    P -= 1

    toto = 0;
    i = 1
    while G > 0:
        G -= min(i, G)

        if G == 0:
            break
        else:
            assert G >= P

        G -= P
        i += 1

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    f = open(sys.argv[1]).readlines()
    run(f)
