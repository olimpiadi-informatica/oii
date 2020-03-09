#!/usr/bin/env python3
import limits
import sys

f = sys.stdin.readlines()
T = int(f[0])

assert T == limits.T
assert len(f) == 1 + 3*T

for t in range(T):
    assert f[1+3*t] == "\n"
    
    N = int(f[2+3*t])
    assert 1 <= N <= limits.MAXN

    V = f[3+3*t].split()
    assert len(V) == N
    for v in V:
        assert v in ("-1", "+1")
