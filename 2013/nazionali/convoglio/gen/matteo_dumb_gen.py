#!/usr/bin/env python2

from limiti import *
from sys import argv
from random import randint, shuffle, seed

usage = """Generatore per "Convoglio".

Parametri:
* N (numero di navi e di messaggi)
* M (numero massimo di corrispondenze messaggio-nave)
* F (numero massimo di match differenti rispetto al match suggerito)
* S (seed)

Constraint:
* 2 <= N <= %d
* N <= M <= %d
* 0 <= F <= M-N
""" % (MAXN, MAXM)

def run(N, M, F, S):
    seed(S)

    message_number = range(0,N)
    ship_number = range(0,N)
    #shuffle(message_number)
    #shuffle(ship_number)


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

    print N, N + len(remaining_edges)
    for e in list(first_match_edges)+list(remaining_edges):
            print message_number[e[0]], ship_number[e[1]]

if __name__ == "__main__":
    if len(argv) != 5:
      print usage
      exit(1)

    N, M, F, S = [int(x) for x in argv[1:]]
    assert(2 <= N <= MAXN)
    assert(N <= M <= MAXM)
    assert(0 <= F <= M-N)
    run(N, M, F, S)
