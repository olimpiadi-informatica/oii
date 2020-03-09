#!/usr/bin/env python3

from limits import MAXN, MAXV
import sys

f = sys.stdin.readlines()
T = int(f[0])
row = 0
for i in range(T):
    row += 1
    assert len(f[row].strip()) == 0

    row += 1
    N = int(f[row])
    assert 1 <= N <= MAXN

    row += 1
    riga = list(map(int, f[row].split()))
    assert len(riga) == N, "%d" % len(riga)
    assert all(0 <= x <= MAXV for x in riga)
assert len(f) == row + 1
