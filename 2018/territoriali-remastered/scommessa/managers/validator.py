#!/usr/bin/env python3
from limits import MAXN
import sys

f = sys.stdin.readlines()
T = int(f[0].strip())
for i in range(T):
    N = int(f[2 * i + 1].strip())
    assert 1 <= N <= MAXN
    assert N % 2 == 1
    nums = list(map(int, f[2 * i + 2].strip().split(' ')))
    nums.sort()
    ok = list(range(0, N))
    assert nums == ok
