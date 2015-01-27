#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "scuola".

Parametri:
* N (numero di eroi)
* P (tipo di prova)

Constraint:
* 1 <= N < %d
* P == 1 || P == 2
* P == 2 => N = 2^n
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import seed, random, randint
from random import choice, sample

def run(N, S):
    print N, P

if __name__ == "__main__":
    if len(argv) != 3:
        print usage
        exit(1)

    N, P = [int(x) for x in argv[1:]]
    run(N, P)
