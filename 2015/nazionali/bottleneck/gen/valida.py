#!/usr/bin/env pypy
# -*- coding: utf-8 -*-
from limiti import *
try:
    import blist
    print "NOOOOOOOO"
except:
    pass

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f, st):
    assert(len(f) > 1)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 6)
    N, M, W, L, R, C = prima
    assert(1 <= W <= N)
    assert(1 <= L <= N)
    assert(W != L)
    if (st == 4):
        assert(2 <= R <= MAXC)
        assert(2 <= C <= MAXC)
        assert(N == R*C)
        assert(M == 2*N-R-C)
    else:
        if st != 1:
            assert(R == -1 and C == -1)
        assert(2 <= N <= MAXN_ST[st-1])
        assert(1 <= M <= MAXM_ST[st-1])

    assert(len(f) == 1+M)
    
    # Verifico la validita' di tutti gli archi e li inserisco in una
    # lista di adiacenza
    adjlist = {}
    for i in f[1:]:
      edge = [int(x) for x in i.split()]
      assert(len(edge) == 3)
      u,v,c = edge
      assert(1 <= u <= N)
      assert(1 <= v <= N)
      assert(u != v)
      assert(0 <= c <= MAXW)
      
      if u not in adjlist:
        adjlist[u] = set()
      adjlist[u].add(v)
      
      if v not in adjlist:
        adjlist[v] = set()
      adjlist[v].add(u)
    
    # Verifico l'assenza di archi ripetuti
    assert(sum(map(len, adjlist.itervalues())) == 2*M)
    
    # Verifico che sia connesso
    visited = set([1])
    frontier = [1]
    while len(frontier)>0:
      i = frontier.pop()
      for j in adjlist[i]:
        if j not in visited:
          visited.add(j)
          frontier.append(j)
    assert(len(visited) == N)
    return 0 # Input corretto


if __name__ == "__main__":
    if len(argv) < 2:
        usage()
    
    # Di default, ignora i subtask
    st = 0

    if len(argv) == 3:
        st = int(argv[2])

    f = open(argv[1]).readlines()
    exit(run(f, st))
