#!/usr/bin/env python3

from limits import MAXN
import sys

f = sys.stdin.readlines()
T = int(f[0])
row = 0
for i in range(T):
    row += 1
    assert len(f[row].strip()) == 0

    row += 1
    N, F, C = map(int, f[row].split())
    assert 1 <= N <= MAXN
    assert 1 <= F <= MAXN
    assert 1 <= C <= MAXN

assert len(f) == row + 1
