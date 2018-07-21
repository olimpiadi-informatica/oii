#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "scommessa".

Parametri:
* N (numero)
* mode (tipo di generazione)
  - 0 random
  - 1 ordinato
  - 2 pari-pari-pari-...-dispari-dispari-dispari
* S (seed)

Constraint:
* 1 <= N <= %d
""" % (MAXN)

def run(N, mode):
    print(N)
    
    if mode == 0:
        nums = [str(x) for x in range(0, N)]
        shuffle(nums)
        print(' '.join(nums))
    elif mode == 1:
        nums = [str(x) for x in range(0, N)]
        print(' '.join(nums))
    elif mode == 2:
        even = [str(i*2) for i in range(0, (N+1)//2)]
        odd = [str(i*2+1) for i in range(0, N-1-N//2)]
        shuffle(even)
        shuffle(odd)
        print(' '.join(even + odd))
    else:
        print("Tipo di generazione non valido")
        print(usage)
        exit(1)

if __name__ == "__main__":
    if len(argv) != 4:
        print(usage)
        exit(1)

    N, mode, S = map(int, argv[1:])
    
    assert (1 <= N <= MAXN)
    assert (N % 2 == 1)
    
    seed(S)
    run(N, mode)
