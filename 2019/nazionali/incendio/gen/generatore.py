#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "incendio".

Parametri:
* N (dimensione griglia)
* M (numero di incendi)
* T (numero subtask)
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= M <= %d
""" % (MAXN, MAXM)


#
# Funzioni di stampa modulari per file binari o in chiaro
#
BINARY = False

def bwrite(x, l):
    if isinstance(x, str):
        if len(x) == l:
            stdout.buffer.write(x.encode('ascii'))
        else:
            stdout.buffer.write(len(x).to_bytes(4, 'little'))
            stdout.buffer.write(x.encode('ascii'))
    else:
        stdout.buffer.write(x.to_bytes(l, 'little'))

def print_nums(*args, byte_len=4):
    if isinstance(byte_len, int):
        byte_len = [byte_len for _ in range(len(args))]
    if BINARY:
        for i in range(len(args)):
            bwrite(args[i], byte_len[i])
    else:
        print(' '.join(map(str, args)))

def print_vectors(*args, byte_len=4, interleaved=True):
    if isinstance(byte_len, int):
        byte_len = [byte_len for _ in range(len(args))]
    if BINARY:
        for i in range(len(args)):
            for x in args[i]:
                bwrite(x, byte_len[i])
    elif interleaved:
        for i in range(len(args[0])):
            print(' '.join(str(x[i]) for x in args))
    else:
        for i in range(len(args)):
            print(' '.join(map(str, args[i])))
#
# Fine
#


def run(N, M, T):
    print_nums(N, M) # T ?

    p = set()
    while len(p) < M:
      x = randint(0, N-1)
      y = randint(0, N-1)
      if x == 0 and y == 0:
        continue
      if x == N-1 and y == N-1:
        continue
      p.add( (x,y) )

    for xy in p:
      x, y = xy
      print_nums(x, y)

if __name__ == "__main__":
    if len(argv) != 5:
        print(usage)
        exit(1)

    N, M, T, S = map(int, argv[1:])

    assert (1 <= N <= MAXN)
    assert (1 <= M <= MAXM)
    assert (1 <= M <= (N*N-2))
    seed(S)
    run(N, M, T)
