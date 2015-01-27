#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "salti".

Parametri:
* N (primo numero in input)

Constraint:
* 1 <= N < %d
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import seed, random, randint
from random import choice, sample

if __name__ == "__main__":
    try:
        import psyco
        psyco.full()
    except ImportError:
        pass
    if len(argv) != 2:
        print usage
        exit(1)

    N, = [int(x) for x in argv[1:]]
    assert (1 <= N and N <= MAXN)
    print N
