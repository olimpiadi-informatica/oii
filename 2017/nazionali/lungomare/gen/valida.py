#!/usr/bin/env pypy
# Usare pypy solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.
# Non controllo che siano rispettate le ipotesi dei subtask...

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
    #~ return 0
    assert (len(f) == 3)
    
    prima_riga = [int(x) for x in f[0].split()]
    assert (len(prima_riga) == 2)
    N = prima_riga[0]
    L = prima_riga[1]
    assert (1 <= N <= MAXN)
    assert (1 <= L <= MAXL)
    
    D = [int(x) for x in f[1].split()]
    assert (len(D) == N)
    for i in range(N-1):
        assert (0 < D[i] < D[i+1])
    assert (D[N-1] < L)
    
    P = [int(x) for x in f[2].split()]
    assert (len(P) == N)
    for i in range(N):
        assert (1 <= P[i] <= MAXL)
    
    if (st == 2 or st == 3 or st == 4):
        length_passerelle = P[0]
        for i in range(N):
            assert (P[i] == length_passerelle)
    
    if (st == 2):
        dist_passerelle = 0
        if (N >= 2):
            dist_passerelle = D[1] - D[0]
        for i in range(1, N):
            assert (D[i] - D[i-1] == dist_passerelle)
    
    if (st == 3):
        assert (N <= MAXN_st3)
    
    if (st == 4):
        assert (N <= MAXN_st4)
    
    if (st == 5):
        assert (N <= MAXN_st5)
    
    if (st == 6):
        assert (N <= MAXN_st6)
    
    if (st == 7):
        assert (N <= MAXN_st7)
    
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
