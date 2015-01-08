#!/usr/bin/python

import random
import sys

def gen_chain(grafo, chain, S):
    for i in xrange(len(chain)-1):
        grafo[chain[i]] = chain[i+1]
    grafo[chain[-1]] = random.randint(0, S-1)

def gen_cycle(grafo, chain):
    for i in xrange(len(chain)-1):
        grafo[chain[i]] = chain[i+1]
    grafo[chain[-1]] = chain[0]

def stampa_grafo(N, S, grafo):
    print N, S, N

    for i in xrange(S):
        for j in xrange(N-1):
            newstate = grafo[(j+1) * S + i] % S
            newpos = grafo[(j+1) * S + i] // S

            print i, j + 1, newstate, newpos - (j + 1)

        print i, 0, 0, 0

    for i in xrange(N):
        print i

def genera(N, S, Nchain, Kchain, Ncycle, Kcycle):
    nodi = range(S, S * N)
    random.shuffle(nodi)
    grafo = dict()

    # generate Nchain distinct chains, each long Kchain
    for i in xrange(Nchain):
        gen_chain(grafo, nodi[Kchain * i:Kchain * (i+1)], S)

    # with remaining elements, generate random cycles
    for i in xrange(Ncycle):
        gen_cycle(grafo, nodi[Kchain * Nchain + Kcycle * i:
                              Kchain * Nchain + Kcycle * (i+1)])

    # with everything else, jump to random places
    remaining = (N-1) * S - Nchain * Kchain - Ncycle * Kcycle
    for i in xrange(remaining):
        which = random.randint(0, Nchain * Kchain + Ncycle + Kcycle - 1)
        who = nodi[which]
        me = nodi[i + Nchain * Kchain + Ncycle * Kcycle]
        grafo[me] = who

    stampa_grafo(N, S, grafo)

if __name__ == '__main__':
    genera(*(map(int, sys.argv[1:])))
