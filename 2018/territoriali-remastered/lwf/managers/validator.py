#!/usr/bin/env python3
from limits import MAXN
import sys

f = sys.stdin.readlines()
T = int(f[0].strip())
for i in range(T):
    N = int(f[i + 1].strip())
    assert 1 <= N <= MAXN
