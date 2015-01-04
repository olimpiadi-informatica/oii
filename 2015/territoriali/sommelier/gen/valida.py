#!/usr/bin/env python2

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
def run(f, st):
    if int(f[0]) > MAXN or int(f[0]) < MINN:
        return 1
    if len(f[1].split()) != int(f[0]):
        return 2
    return sum(map(lambda x: int(x) < MING or int(x) > MAXG, f[1].split()))

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
