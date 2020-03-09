#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit
from random import randint, random, seed, shuffle


cases = 0

if __name__ == "__main__":
    if len(argv) < 3:
        print("Generatore di 'download'")
        print("{} SEED 0".format(argv[0]))
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    
    # Numeri di test
    print(T)

    tipi =  ["primo_zero"]*1 +\
            ["secondo_zero"]*1 +\
            ["entrambi_zero"]*1 +\
            ["random"]*3
    shuffle(tipi)

    for tipo in tipi:
        if tipo == "random":
            N = randint(MAXN//2, MAXN)
            F = randint(MAXN//1000, MAXN//20)
            rimasti = N % F
            C = randint(1, max(1, rimasti//100))
        elif tipo == "primo_zero":
            N = randint(20, MAXN//2)
            F = randint(N+1, MAXN)
            C = randint(1, N//20)
        elif tipo == "secondo_zero":
            N = randint(20, MAXN)
            F = randint(1, N//20)
            rimasti = N % F
            C = randint(rimasti+1, MAXN)
        elif tipo == "entrambi_zero":
            N = randint(1, MAXN//2)
            F = randint(N+1, MAXN)
            C = randint(N+1, MAXN)
        cases += 1
        print()
        print("{} {} {}".format(N, F, C))

    assert cases == T
