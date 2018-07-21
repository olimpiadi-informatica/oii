#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "wlf".

Parametri:
* N (numero)

Constraint:
* 1 <= N <= %d
""" % (MAXN)

if __name__ == "__main__":
    if len(argv) != 2:
        print(usage)
        exit(1)

    N, = map(int, argv[1:])
    
    assert (1 <= N <= MAXN)
    print(N)
