#!/usr/bin/env python2

import sys


linea = sys.stdin.readline()
N, M = [int(x) for x in linea.split()]
linea = sys.stdin.readline()
s = [int(x) for x in linea.split()]

indietro = 0
avanti = 0
somma = 0
while True:
    somma += s[avanti]
    avanti += 1
    while somma > N:
        somma -= s[indietro]
        indietro += 1
    if somma == N:
        print indietro+1
        sys.exit(0)
