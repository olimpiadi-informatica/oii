#!/usr/bin/env python2

"""Genera un grafo delle dipendenze sempre risolvibile.

In pratica, dispone i nodi in un array, e crea una regola
per il nodo i, imponendo come dipendenze solo nodi di indice
superiore.

"""
import sys
import os
from random import randint, randrange, sample, shuffle, seed
from heapq import heappop, heappush

def usage():
    print """%s R K S
R = numero di regole
K = numero di sostanze gia' presenti nell'acqua
S = seed per i numeri casuali""" % os.path.basename(sys.argv[0])

def run():
    if len(sys.argv) < 4:
        usage()
        return -1

    R = int(sys.argv[1])
    K = int(sys.argv[2])
    S = int(sys.argv[3])

    seed(S)

    N = K + randrange(2, R)

    queue = [(0, x) for x in range(N-K)]
    shuffle(queue)
    rules = []
    
    for i in range(R):
        c, x = heappop(queue)
        heappush(queue, (c+1, x))
        j = randint(1, N - x - 1)
        rules.append((x, sample(xrange(x+1, N), j)))
    
    labels = range(2, N+1)
    shuffle(labels)
    labels.insert(0, 1)

    print K, R
    for i in range(N-K, N):
        print labels[i]
    for x, deps in rules:
        print labels[x], len(deps), ' '.join(map(str, (labels[y] for y in deps)))


if __name__ == '__main__':
    sys.exit(run())
