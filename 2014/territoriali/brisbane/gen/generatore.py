#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "Brisbane" scritto da Giulio Carlassare.

Parametri:
* N  (nodi)
* A  (attrazioni)
* Mg (collegamenti gratuiti)
* Mb (collegamenti col bus)
* Mt (collegamenti col traghetto)

Constraint:
* 2 <= N <= %d
* N <= Mb + Mg + Mt <= %d
""" % (MAXN,MAXM)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed
from graph import *
from string import split, join

def run(N, A, Mg, Mb, Mt, S):
    nseed(S)
    rseed(S)
    grafo = ugraph(N)
    grafo.addedges(Mg+Mb+Mt)
    grafo.shuffle()
    #Attrazioni
    attr = sample(xrange(1, N), A)
    #Lista degli archi
    archi = list(grafo)
    shuffle(archi)
    #Collegamenti gratuiti
    gratis = archi[:Mg]
    archi = archi[Mg:]
    shuffle(archi)
    #Collegamenti bus
    bus = archi[:Mb]
    archi = archi[Mb:]
    shuffle(archi)
    #Collegamenti traghetto
    trag = archi
    del archi

    print N, A, Mg, Mb, Mt
    for x in attr:
        print x
    for x in gratis:
        print x[0], x[1]
    for x in bus:
        print x[0], x[1]
    for x in trag:
        print x[0], x[1]

if __name__ == "__main__":
    if len(argv) != 7:
        print usage
        exit(1)

    N, A, Mg, Mb, Mt, S = map(int, argv[1:])
    assert (2 <= N <= MAXN)
    assert (N <= Mg+Mb+Mt <= MAXM)
    run(N, A, Mg, Mb, Mt, S)
