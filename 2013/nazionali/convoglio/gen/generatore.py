#!/usr/bin/env python2

from limiti import *
from sys import argv
from random import randint, shuffle, seed, sample

usage = """Generatore per "Convoglio".

Parametri:
* N (numero di navi e di messaggi)
* M (numero massimo di corrispondenze messaggio-nave)
* T (tipo di grafo generato)
* S (seed)

Constraint:
* 2 <= N <= %d
* N <= M <= %d
* -1 <= T <= 3
""" % (MAXN, MAXM)

def old_gen(N,M,F):
    common_part = range(0,N-F)
    first_residual = range(N-F, N)
    second_residual = range(N-F, N)
    shuffle(first_residual)
    shuffle(second_residual)

    # Swap per dare la garanzia di almeno un match distinto
    # per F>=2
    if F >= 2:
        if first_residual[0] == second_residual[0]:
            tmp = second_residual[0]
            second_residual[0] = second_residual[1]
            second_residual[1] = tmp

    first_match = common_part + first_residual
    second_match = common_part + second_residual

    first_match_edges = set([(i, first_match[i]) for i in xrange(0,N)])
    remaining_edges = set([(i, second_match[i]) for i in xrange(0,N)])
    remaining_edges.update(set([(randint(0,N-1), randint(0, N-1) ) for _ in xrange(0,M-N-F)]))
    remaining_edges.difference_update(first_match_edges)
    return first_match_edges,remaining_edges

def no_match(N,M):
    first_match = set([(i,i) for i in xrange(0,N)])
    left=M-N
    others=set()
    while left>0:
        i=randint(0,N-2)
        j=randint(i+1,N-1)
        if (i,j) not in others:
            others.add((i,j))
            left-=1
    
    return first_match,others

def cycle_match(N,NP):
    first_match = set([(i,i) for i in xrange(0,N)])
    second_match = set([(i,i+1) for i in xrange(0,NP-1)])
    second_match.add((NP-1,0))
    return first_match,second_match

def lowdeg(N,NP):
    first_match = set([(i,i) for i in xrange(0,N)])
    second_match=set(zip(range(0,NP),sample(range(0,N),NP)))
    return first_match,second_match
        

def run(N, M, T, S):
    seed(S)

    message_number = range(0,N)
    ship_number = range(0,N)
    shuffle(message_number)
    shuffle(ship_number)
    
    if T==0:
        first_match_edges,remaining_edges=old_gen(N,M,randint(0,M-N))
    elif T==1:
        first_match_edges,remaining_edges=no_match(N,M)
    elif T==2:
        first_match_edges,remaining_edges=cycle_match(N,M-N)
    else:
        first_match_edges,remaining_edges=lowdeg(N,M-N);
    
    print N, N + len(remaining_edges)
    for e in list(first_match_edges)+list(remaining_edges):
            print message_number[e[0]], ship_number[e[1]]

if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    N, M, T, S = [int(x) for x in argv[1:]]
    if T==-1:
        print "3 6"
        print "0 2"
        print "1 0"
        print "2 1"
        print "0 0"
        print "1 2"
        print "2 2"
        exit(0)
    assert(2 <= N <= MAXN)
    assert(N <= M <= MAXM)
    assert(0 <= T <= 3)
    run(N, M, T, S)
