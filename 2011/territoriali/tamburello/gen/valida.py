#!/usr/bin/env python2

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt" % \
        os.path.basename(sys.argv[0])
    sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
    
    try:
        input = open(sys.argv[1]).readlines()
    except:
        print >> sys.stderr, "Impossibile aprire il file di input %s." % \
            sys.argv[1]
        sys.exit(1)

    # 2 righe
    if len(input) != 2: sys.exit(1)

    # prima riga solo 2 <= N <= 10000
    tmp = input[0].strip().split()
    if len(tmp) != 1: sys.exit(1)
    try:
        N = int(tmp[0])
    except ValueError:
        sys.exit(1)
    if N < 2 or N > 10000: sys.exit(1)

    # seconda riga N valori 0 o 1
    tmp = input[1].strip().split()
    if len(tmp) != N: sys.exit(1)
    for i in xrange(N):
        try:
            x = int(tmp[i])
        except ValueError:
            sys.exit(1)
        if x not in [0, 1]: sys.exit(1)

    sys.exit(0)
                
