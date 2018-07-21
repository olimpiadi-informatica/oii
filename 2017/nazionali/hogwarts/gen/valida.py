#!/usr/bin/env pypy
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
# per testare la correttezza dell'input, usate assert()
def run(f, st):
    N, M = map(int, f[0].split())
    assert(2 <= N <= MAXN)
    assert(1 <= M <= MAXM)
    assert(len(f) == M+1)
    
    T = 0 # Tiene la fine piu' grande
    it = 0
    s = set()
    for r in f[1:]:
        da, a, inizio, fine = map(int, r.split())
        assert(0 <= da < N)
        assert(0 <= a < N)
        assert(da != a)
        assert(0 <= inizio < fine <= MAXT)
        
        s.add(tuple(sorted((da,a))))
        
        if (st == 3 or st == 4):
            assert(inizio == 0)
        
        if (it == 0):
            T = fine
        if (st == 3):
            if (it >= 1):
                assert (T == fine)
        
        it += 1
        T = max(T, fine)
    assert(len(s) == M)
    
    if (st == 2):
        assert(N <= MAXN_st2)
        assert(M <= MAXM_st2)
        assert(T <= MAXT_st2)
    
    if (st == 5):
        assert(N <= MAXN_st5)
        assert(M <= MAXM_st5)
        assert(T <= MAXT_st5)
        
    return 0

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
