#!/usr/bin/env python3

from limits import MAXN
import sys

sys.setrecursionlimit(100000)

f = sys.stdin.readlines()
T = int(f[0])
row = 0
for i in range(T):
    row += 1
    assert len(f[row].strip()) == 0

    row += 1
    N = int(f[row])
    assert 1 <= N <= MAXN

    root = -1
    adj = [[] for _ in range(N)]
    values = set()
    for i in range(N):
        row += 1
        p, v = map(int, f[row].strip().split())
        assert -1 <= p <= N-1
        assert v not in values
        assert 0 <= v <= N-1
        values.add(v)
        if p == -1:
            root = i
        else:
            adj[p].append(i)
    assert root != -1
    visited = [False for _ in range(N)]

    def dfs(u):
        assert not visited[u], "Not a tree"
        visited[u] = True
        for v in adj[u]:
            dfs(v)

    dfs(root)
    assert all(visited)

assert len(f) == row + 1
