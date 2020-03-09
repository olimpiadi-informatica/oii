#!/usr/bin/env python3
import limits
import sys

f = sys.stdin.readlines()
T = int(f[0])

assert T == limits.T
assert len(f) == 1 + 7*T

for t in range(T):
    assert f[1+7*t] == "\n"
    N = list(map(int, f[1+7*t+1].split()))
    M = int(f[1+7*t+2])
    S = [s.strip() for s in f[1+7*t+3:1+7*t+7]]

    for l,s in zip(N, S):
        assert len(s) == l
        assert l >= M
        assert all(c in limits.CHARS for c in s)

    sets = [set(), set(), set(), set()]
    for i, s in enumerate(S):
        for j in range(len(s)-M+1):
            sets[i].add(s[j:j+M])
    common = sets[0] & sets[1] & sets[2] & sets[3]
    assert len(common) == 1
