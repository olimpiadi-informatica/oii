#!/usr/bin/env python2

from limiti import *
from varie import *
from sys import argv, exit
from random import shuffle, seed
from itertools import product

usage="""Generatore di "mojito".

Parametri:
* X (numero di righe)
* Y (numero di colonne)
* N (numero di ragazzi)
* S (seed)

Constraint:
* %d <= X, Y, N <= %d
""" % (MINN, MAXN)


def single_cell():
    return " ".join(map(str, map(lambda x: x+1, cells.pop())))

def run(X, Y, N, S):
    print X, Y
    print single_cell()
    print N
    for i in xrange(N):
        print single_cell(), single_cell()

if __name__ == "__main__":
    try:
        X, Y, N, S = map(int, argv[1:])
    except ValueError:
        print usage
        exit(1)

    # su seed non positivo copia un input di esempio dal .tex
    if S <= 0:
        print extract_input()[-S],
        exit(0)
    seed(S)

    assert (MINN <= X <= MAXN)
    assert (MINN <= Y <= MAXN)
    assert (MINN <= N <= MAXN)

    # genera tutte le celle possibili
    cells = list(product(range(X), range(Y)))
    # mischiale
    shuffle(cells)

    run(X, Y, N, S)
