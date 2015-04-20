#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "trovaparola" scritto da Giulio Carlassare.

Parametri:
* R (numero di righe)
* C (numero di colonne)
* T (risolvibile = 0/1)
* S (seed)

Constraint:
* 2 <= R, C <= %d
""" % MAX

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed
from string import split, join, uppercase

def run(R, C, T, S):
    nseed(S)
    rseed(S)
    #La matrice con le lettere
    matr = []
    for i in xrange(R):
        temp = []
        for j in xrange(C):
            temp.append(choice(uppercase))
        matr.append(temp)
    lung_parola = randint((R+C)/10+2, R+C if T == 1 else (R+C)/2)
    parola = ""
    posr, posc = 0, 0
    for i in xrange(lung_parola):
        parola += matr[posr][posc]
        if random() > 0.5:
            if posr < R-1:
                posr += 1
            else:
                posc += 1
        else:
            if posc < C-1:
                posc += 1
            else:
                posr += 1
    if T == 0:
        for i in xrange(randint(0, (R+C)/2-2)):
            parola += choice(uppercase)

    print R, C
    print parola
    for i in xrange(R):
        temp = ""
        for j in xrange(C):
            temp += matr[i][j]
        print temp


if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    R, C, T, S = map(int, argv[1:])
    assert (2 <= R <= MAX and 2 <= C <= MAX)
    assert (T in (0, 1))
    run(R, C, T, S)
