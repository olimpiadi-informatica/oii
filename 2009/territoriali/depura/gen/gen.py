#!/usr/bin/env python2

"""Genera un grafo delle dipendenze aciclico che rappresenta in quale
ordine possono essere inserite le sostanze; tra le foglie, alcune sono
considerate gia` inserite mentre altre no. Se delle foglie sotto il
nodo 1 sono non inserite, il problema non ha soluzione.

"""
import sys
import os
from random import randint, randrange, sample, shuffle, seed
from heapq import heappop, heappush
from collections import defaultdict

def usage():
    print """%s R K E X S
R = numero di regole
K = numero di sostanze gia' presenti nell'acqua
E = il massimo numero di sostanze da cui deve dipendere la sostanza 1 (< R)
X = risolvibile (1) o non risolvibile (0)
S = seed per i numeri casuali""" % os.path.basename(sys.argv[0])

def run():
    if len(sys.argv) < 5:
        usage()
        return -1

    R = int(sys.argv[1])
    K = int(sys.argv[2])
    E = int(sys.argv[3])
    X = bool(int(sys.argv[4]))
    S = int(sys.argv[5])

    if E > R:
        usage()
        return -1
    
    seed(S)
    
    # N = numero di sostanze coinvolte (al piu`)
    # P = il posto che occupa la sostanza 1 prima del rietichettamento
    #     dargli il valore K+E-1 implica che puo' dipendere al piu' da E sostanze
    #     non gia` inserite; visto che il DAG che facciamo e' abbastanza denso,
    #     la vera soluzione sara` probabilmente non molto inferiore ad E.
    N = K + R
    P = K + E - 1

    present = range(0,K)
    rules_owner = range(K, N)
    rules = range(R)

    # Ogni regola e' un sample casuale delle sostanze con indice minore
    for i in range(R):
        rules[i] = sample(range(K+i), randint(1,K+i))

    # Se non deve essere risolubile, aggiungo un impedimento in un discendente della sostanza 1
    if X == False:
        # Qui metto in descendants tutti i discendenti della sostanza 1
        des = {}
        def calcola_des(i):
            if i < K:
                des[i] = set([])
                return des[i]
            else:
                r = set([i])
                for j in rules[i-K]:
                    if not des.has_key(j):
                        calcola_des(j)
                    r = r.union(des[j]);
                des[i] = r
                return des[i]
        descendants = calcola_des(P)
        
        # Ne scelgo uno
        x = sample(descendants, 1)[0]
        if x in present:
            # Se e` una sostanza gia` presente, la tolgo dalle presenti e ne metto una ininfluente
            i = present.index(x)
            present[i] = N
            N += 1
            print present
            
        else: # x in rules_owner
            # Se e` un rules_owner, aggiungo alla regola una dipendenza non inseribile
            i = rules_owner.index(x)
            rules[i] += [N]
            N += 1

    # Rinomino casualmente le sostanze
    labels = range(1, N+1)
    shuffle(labels)
    # Mi assicuro che P = 1
    x = labels[P]
    y = labels.index(1)
    labels[P] = 1
    labels[y] = x

    print K, R
    for i in range(K):
        print labels[present[i]]
    shuffled_rules = zip(rules_owner, rules);
    shuffle(shuffled_rules)
    for x, deps in shuffled_rules:
        print labels[x], len(deps),
        print ' '.join([str(labels[y]) for y in deps])


if __name__ == '__main__':
    sys.exit(run())
