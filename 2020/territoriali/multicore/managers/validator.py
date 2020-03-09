#!/usr/bin/env python3

from limits import *
import sys

f = sys.stdin.readlines()
t = int(f[0])
assert T == t
row = 0
for i in range(t):
    row += 1
    assert len(f[row].strip()) == 0

    row += 1
    N, P = [int(x) for x in f[row].strip().split(" ")]
    assert 1 <= N <= MAXN
    assert 1 <= P <= MAXP

    for _ in range(N):
        row += 1
        v, w = [int(x) for x in f[row].strip().split(" ")]
        assert 1 <= v <= MAXC
        assert 1 <= w <= P

assert len(f) == row + 1
