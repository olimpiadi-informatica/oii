#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from limiti import *

usage="""Generatore per "fibstr".

Parametri:
* N (lunghezza della stringa)
* A (algoritmo)
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= A <= 3
""" % MAXN

from sys import argv, exit, stderr
import os
from numpy.random import random, randint, seed as nseed
from random import choice, sample, shuffle, randrange, seed as rseed

def fibonacci(N):
    """Restituisce un vettore con i Fibonacci più piccoli di N,
    ordinati.

    """
    if N == 0:
        return [0]
    elif N == 1:
        return [0, 1, 1]
    else:
        fibs = [0, 1, 1]
        next = 2
        while next <= N:
            fibs.append(next)
            next = fibs[-1] + fibs[-2]
        return fibs

def genera_fibstr(x, y, fiblen):
    if fiblen == 0:
        return ''
    elif fiblen == 1:
        return x
    elif fiblen == 2:
        return y
    else:
        prev = y
        fibstr = x+y
        for i in xrange(3, fiblen):
            tmp = fibstr
            fibstr += prev
            prev = tmp
        return fibstr

def run_random(N, S):
    """Genera una stringa completamente casuale.

    """
    nseed(S)
    rseed(S)
    print N
    print "".join(map(lambda x: choice("qwertyuiopasdfghjklzxcvbnm"), range(N)))

def run_con_fibstr(N, S):
    """Genera una stringa di Fibonacci e ci mette attorno roba
    casuale.

    """
    nseed(S)
    rseed(S)
    print N
    alphabet = set("qwertyuiopasdfghjklzxcvbnm")
    x = choice(list(alphabet))
    alphabet.remove(x)
    y = choice(list(alphabet))
    fibs = fibonacci(N)
    fiblen = randrange(3, len(fibs))
    before = randint(0, N-fibs[fiblen])
    after = N-fibs[fiblen]-before

    print "".join(map(lambda z: choice("qwertyuiopasdfghjklzxcvbnm"), range(before))) + \
        genera_fibstr(x, y, fiblen) + \
        "".join(map(lambda z: choice("qwertyuiopasdfghjklzxcvbnm"), range(after)))

def run_con_fibstr_cattiva(N, S):
    """Genera una stringa di Fibonacci e ci mette attorno roba casuale
    usando gli stessi due simboli.

    """
    nseed(S)
    rseed(S)
    print N
    alphabet = set("qwertyuiopasdfghjklzxcvbnm")
    x = choice(list(alphabet))
    alphabet.remove(x)
    y = choice(list(alphabet))
    fibs = fibonacci(N)
    fiblen = randrange(3, len(fibs))
    before = randint(0, N-fibs[fiblen])
    after = N-fibs[fiblen]-before

    print "".join(map(lambda z: choice([x, y]), range(before))) + \
        genera_fibstr(x, y, fiblen) + \
        "".join(map(lambda z: choice([x, y]), range(after)))

if __name__ == "__main__":
    if len(argv) != 4:
        print usage
        exit(1)
    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    N, A, S = [int(x) for x in argv[1:]]
    assert (1 <= N <= MAXN)
    assert (1 <= A <= 3)
    if A == 1:
        run_random(N, S)
    elif A == 2:
        run_con_fibstr(N, S)
    elif A == 3:
        run_con_fibstr_cattiva(N, S)
