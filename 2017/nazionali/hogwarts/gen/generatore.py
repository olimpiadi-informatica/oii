#!/usr/bin/env pypy

from limiti import *
from varie import *
from graph import graph, ugraph
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from math import log

usage="""Generatore di "hogwarts".

Parametri:
* N (numero di nodi)
* M (numero di archi)
* T (tempo massimo)
* A (tipo di task) 0 = archi fissi, 1 = scompaiono soltanto, 2 = succede di tutto
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= M <= %d
* 1 <= T <= %d
* 0 <= A <= 2
""" % (MAXN, MAXM, MAXT)

tempi = [0]
tlen = 0
spread = 1

def tchoice():
    return tempi[randint(1,tlen)]

def tcouple():
    i = randint(0,tlen)
    j = i+randint(1,spread)
    return (tempi[i], tempi[j])

def run(N, M, T, A):
    # Stabilisco i tempi di comparsa e scomparsa degli archi
    def w(e):
        if (A == 0):
            return (0, T)
        elif (A == 1):
            return (0, tchoice())
        else:
            return tcouple()
    global tempi, tlen, spread
    runs = randint(1,5)
    while tempi[-1] < T:
        if randint(0, runs**3):
            tempi.append(tempi[-1] + randint(1,runs))
        else:
            tempi.append(randint(1, min(2**randint(0,int(log(T,2)+1)), T)) + tempi[-1])
    tempi = tempi[:-1]
    
    if (len(tempi) < 5):
        tempi = range(5)
    spread = min(randint(1,len(tempi)-2), randint(1,len(tempi)-2), randint(1,len(tempi)-2), randint(1,len(tempi)-2), randint(1,len(tempi)-2))
    tlen = len(tempi) - spread - 1
    
    if (A == 1 and T == 1):
        tempi = range(0, randint(3, 3*int(log(N,2))+1))
        tlen = len(tempi)-1

    # Devo costruire un grafo non diretto su N vertici con M archi
    G = ugraph(N, M, 'random', w)
    G.zero_based = True
    G.shuffle()
    print G

if __name__ == "__main__":
    if len(argv) != 6:
        print usage
        exit(1)

    N, M, T, A, S = map(int, argv[1:])
    
    assert (2 <= N <= MAXN)
    assert (1 <= M <= MAXM)
    assert (1 <= T <= MAXT)
    assert (0 <= A <= 2)
    assert ((N*(N-1)) >= 2*M)
    
    seed(S)
    run(N, M, T, A)
