#!/usr/bin/env python3

from limiti import *

import sys
import os


def usage():
    print("Usage: %s file_input.txt [subtask_number]" %
          os.path.basename(sys.argv[0]), file=sys.stderr)
    exit(1)


def run(f, st):
    C, = map(int, f[0].split())
    N, = map(int, f[1].split())
    rest = f[2:]

    limits = subtasks[st]

    maxN = limits.get('MAXN', MAXN)
    maxC = limits.get('MAXC', MAXC)
    maxX = limits.get('MAXX', MAXX)
    maxP = limits.get('MAXP', MAXP)

    assert 1 <= N <= maxN
    assert 0 <= C <= maxC

    assert len(rest) == N

    pos = set()
    for r in rest:
        x, p = map(int, r.split())
        assert x % 10 == 0
        assert p % 10 == 0
        assert 10 <= x <= maxX
        assert 10 <= p <= maxP
        pos.add((x, p))
    assert len(pos) == N


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    sys.exit(run(f, st))
