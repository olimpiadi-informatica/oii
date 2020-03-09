#!/usr/bin/env python3
import limits
import sys

f = sys.stdin.readlines()
T = int(f[0])

assert T == limits.T
assert len(f) == 1 + 3*T

for t in range(T):
    assert f[1+3*t] == "\n"
    N = int(f[1+3*t+1])
    A = map(int, f[1+3*t+2].split())

    assert 2 <= N <= limits.MAXN
    assert all(limits.MINA <= a <= limits.MAXA for a in A)
