#!/usr/bin/env pypy

"""
    Genera un caso con tante tessere alte
    abbastanza da coprire il gap,
    ma impossibile, oppure con una soluzione unica (o quasi).

    Parametri
    H = lunghezza di un "blocco"
    S = numero di blocchi
    possibile = 1 se possibile, 0 altrimenti
"""

import random
import sys

if __name__ == "__main__":
    H, S, possibile_int = map(int, sys.argv[1:])

    assert possibile_int in (0,1)
    possibile = possibile_int == 1

    N = S*H + 2*H + 1

    raltezze = [None] * N
    altezze = [None] * N

    for i in range(0, S*H, H):
        altezze[i] = 2 * H
        for j in range(i+1,i+H):
            altezze[j] = i+H-j
    for i in range(S*H,S*H+H):
        altezze[i] = S*H+H-i
    for i in range(S*H+H,S*H+2*H):
        altezze[i] = 1
    altezze[N-1] = 1

    if possibile:
        P = random.randint(0,S*H)
        altezze[P] += 1

    print N
    print " ".join(str(a) for a in altezze)
