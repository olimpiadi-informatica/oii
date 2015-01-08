#!/usr/bin/env python2

from limiti import *

usage="""Generatore per "turni".
WARNING: genera solo input "risolubili"
(in cui e` possibile coprire tutti i giorni).

Parametri:
* K (numero di giorni)
* N (numero di intervalli)
* C (la soluzione sara` <= C)
* S (seed)

Constraint:
* 1 <= K <= %d
* 1 <= N <= %d
* 1 <= C <= N
""" % (MAXK, MAXN)

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, seed as rseed

def genint(a, b):
    x = randint(a, b)
    y = randint(a, b)
    x, y = min(x, y), max(x, y)
    x = change(x, y, lambda x: x + 1, p=90)
    y = change(y, x, lambda x: x - 1, p=90)
    return (x, y)

def change(x, lim, f, p=20):
    while x != lim and randint(100) > p:
        x = f(x)
    return x

def genera(a, b, n):
    l = sorted([randint(a, b) for _ in xrange(n-1)])
    t = []
    t.append([a, l[0]])
    for i in xrange(1, n-1):
        t.append([min([l[i], b-1, l[i-1]+1]), l[i]])
    t.append([l[n-2], b-1])
    for i in xrange(n):
        m = a
        if i > 0:
            m = max(a, t[i-1][0])
        t[i][0] = change(t[i][0], m, lambda x: x-1)
    return t


def run(K, N, C, S):
    nseed(S)
    rseed(S)
    print K
    print N
    l = genera(0, K, C)
    l1 = []
    for i in xrange(N-C):
        j = randint(0, len(l))
        l1 += [genint(l[j][0], l[j][1]+1)]
    l = l+l1
    shuffle(l)
    for x, y in l:
        print x, y

if __name__ == "__main__":
    if len(argv) != 5:
        print usage
        exit(1)

    K, N, C, S = [int(x) for x in argv[1:]]
    assert(1 <= K <= MAXK)
    assert(1 <= N <= MAXN)
    assert(1 <= C <= N)
    run(K, N, C, S)
