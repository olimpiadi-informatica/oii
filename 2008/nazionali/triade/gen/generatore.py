#!/usr/bin/env python

import sys
import os
import random
import collections
import math

# probabilita' di agganciarsi a due nodi invece che a due
PROB2 = 0.80

def uniform(N):
    """Genera un grafo con distribuzione uniforme"""

    adj = [(0, 1)]

    if N == 1:
        adj = []
    elif N >= 2:
        for i in xrange(2, N):
            u = random.randrange(0, i)
            adj.append((u, i))
            if random.random() >= (1-PROB2):
                v = random.randrange(0, i-1)
                if v >= u: v += 1
                adj.append((v, i))

    return adj

def smallworlds(N):
    """Genera un grafo cercando di creare degli small world, in pratica quando si crea
    un nuovo nodo, si aggancia con maggiore probabilita' ad altri nodi con grado elevato

    """
    adj = [(0, 1)]

    if N == 1:
        adj = []
    elif N >= 2:
        choices = [0, 1]
        degree = collections.defaultdict(int)
        degree[0] = 1
        degree[1] = 1
        for i in xrange(2, N):
            u = random.choice(choices)
            
            adj.append((u, i))
            if random.random() >= (1-PROB2):
                v = u
                while v == u:
                    v = random.choice(choices)
                
                adj.append((v, i))
                choices.append(v)
                choices.append(i)
                degree[v] += 1
                degree[i] += 1

            for j in xrange(int(math.ceil(math.log(degree[u])))):
                choices.append(u)
            degree[u] += 1
            degree[i] += 1
            choices.append(i)
            
    return adj

def hub(N):
    """Genera un grafo come uniform, pero' uno dei due nodi a cui si aggancia
    e' sempre lo stesso. In questo modo un nodo avra' grado massimo.

    """
    adj = [(0, 1)]

    if N == 1:
        adj = []
    elif N >= 2:
        for i in xrange(2, N):
            adj.append((0, i))
            if random.random() >= (1-PROB2):
                u = random.randrange(1, i)
                adj.append((u, i))

    return adj

def chain(N):
    """Genera una catena"""
    
    if N == 1:
        return []
    else:
        return [(i, i+1) for i in xrange(N-1)]

def print_graph(N, adj):
    """Scrive il grafo rimappando i nodi"""
    
    print len(adj), N

    mapping = range(N)
    random.shuffle(mapping)
    for u, v in adj:
        if random.random() >= .5:
            u, v = v, u
        print mapping[u] + 1, mapping[v] + 1

def run():
    args = sys.argv[1:]

    if len(args) != 3:
        print >> sys.stderr, 'Usage: %s N T S' % os.path.basename(sys.argv[0])
        print >> sys.stderr, '       T = (U: uniform, W: small worlds, C: chain, H: hub)'
        return 1

    N = int(args[0])
    T = args[1]
    S = int(args[2])

    assert(N >= 1)

    random.seed(S)

    f = {'U': uniform,
         'W': smallworlds,
         'H': hub,
         'C': chain}[T]
    adj = f(N)
    print_graph(N, adj)

if __name__ == '__main__':
    try:
        import psycho
        psycho.full()
    except ImportError:
        pass
    sys.exit(run())

