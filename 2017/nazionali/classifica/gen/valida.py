#!/usr/bin/env python2
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
    assert(len(f) >= 1)
    prima_riga = [int(x) for x in f[0].split()]
    assert (len(prima_riga) == 2)
    N = prima_riga[0]
    Q = prima_riga[1]
    assert (1 <= N <= MAXN)
    assert (1 <= Q <= MAXQ)
    assert (len(f) == Q+2)
    
    ids = [int(x) for x in f[1].split()]
    assert (len(ids) == N)
    presente = [False] * (N)
    for i in range(N):
        assert (0 <= ids[i] <= N-1)
        assert (not presente[ids[i]])
        presente[ids[i]] = True
    
    prec = [0] * (N+1)
    succ = [0] * (N+1)
    for i in range(N):
        if (i >= 1):
            prec[ids[i]] = ids[i-1]
        else:
            prec[ids[i]] = N
            succ[N] = ids[i]
        if (i <= N-2):
            succ[ids[i]] = ids[i+1]
        else:
            succ[ids[i]] = N
            prec[N] = ids[i]
    
    in_gara = N
    aggiornamento = True # aggiornamento = True se l'ultima operazione e' un aggiornamento (supera o squalifica). Serve per controllare se le chiamate a partecipante vengono tutte alla fine.
    squalifica_chiamata = False
    supera_chiamata = False
    partecipa_allafine = 0
    
    for r in range(Q):
        comando = f[r+2].split()
        assert (len(comando) == 2)
        
        if (comando[0] == 'p'):
            if aggiornamento:
                partecipa_allafine += 1
                aggiornamento = False
            pos = int(comando[1])
            assert (1 <= pos <= in_gara)
        
        elif (comando[0] == 'x'):
            squalifica_chiamata = True
            aggiornamento = True
            
            id_el = int(comando[1])
            assert (0 <= id_el <= N-1)
            assert (presente[id_el])
            
            presente[id_el] = False
            in_gara -= 1
            
            p = prec[id_el]
            s = succ[id_el]
            succ[p] = s
            prec[s] = p
        
        elif (comando[0] == 's'):
            supera_chiamata = True
            aggiornamento = True
            
            id_sup = int(comando[1])
            assert (0 <= id_sup <= N-1)
            assert (presente[id_sup])
            assert (prec[id_sup] != N)
            
            p = prec[id_sup]
            pp = prec[p]
            s = succ[id_sup]
            
            succ[pp] = id_sup
            prec[p] = id_sup
            succ[p] = s
            prec[id_sup] = pp
            succ[id_sup] = p
            prec[s] = p
        
        else:
            assert (False) # Lettera non valida  
    
    if (st == 2):
        assert (N <= MAXN_st2)
        assert (Q <= MAXQ_st2)
    
    if (st == 3):
        assert (not squalifica_chiamata)
        assert (Q <= MAXQ_st3)
    
    if (st == 4):
        assert (partecipa_allafine <= 1)
        assert (Q <= MAXQ_st4)
    
    if (st == 5):
        assert (not supera_chiamata)
    
    if (st == 6):
        assert (Q <= MAXQ_st6)
    
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
