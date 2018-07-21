#!/usr/bin/env python2
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *

import sys
import os
from Queue import Queue

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


def run(f, st):
    N, M = map(int, f[0].split(" "))
    assert 2 <= N <= MAXN
    assert 1 <= M <= MAXM
    assert len(f) == M+2
    P1, D1, P2, D2 = map(int, f[1].split(" "))
    assert 0 <= P1 < N
    assert 0 <= P2 < N
    assert 0 <= D1 < N
    assert 0 <= D2 < N
    grafo = [ [] for _ in range(N) ]
    for l in f[2:]:
        A, B = map(int, l.split(" "))
        grafo[A].append(B)
        grafo[B].append(A)
    vis = [False] * N
    vis[0] = True
    queue = Queue()
    queue.put(0)
    while not queue.empty():
        u = queue.get()
        for v in grafo[u]:
            if not vis[v]:
                vis[v] = True
                queue.put(v)
    for visited in vis:
        assert visited
            



if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
