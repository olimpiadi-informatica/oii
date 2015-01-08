#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 4)
    N,M,X,Y = prima
    assert(1 <= N <= MAXN) 
    assert(1 <= M <= MAXM)
    assert(1 <= X <= MAXN)
    assert(1 <= Y <= MAXN)
    assert(X!=Y)
    archi = set()
    degree=[0]*N
    for i in range(M):
        arco = [int(x) for x in f[i+1].split()]
        assert(len(arco)==2)
        u,v = arco
        assert(1 <= u <= N)
        assert(1 <= v <= N)
        assert(u != v)
        u,v = min(u,v),max(u,v)
        assert((u,v) not in archi)
        archi.add((u,v))
        degree[u-1]+=1
        degree[v-1]+=1
    assert(degree[X-1]%2==1)
    assert(degree[Y-1]%2==1)
    assert(min(degree)>0)
    for i in range(N):
        if (i+1)!= X and (i+1)!=Y:
            assert(degree[i]%2==0)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    f = open(argv[1]).readlines()
    exit(run(f))


