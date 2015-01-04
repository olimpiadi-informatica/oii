#!/usr/bin/env python2

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)

num_righe = None
num_colonne = None
S = None

def verifica_cella(a, b):
    assert(1 <= a <= num_righe)
    assert(1 <= b <= num_colonne)
    S.add((a, b))
    return True

# 0            -> corretto
# altro numero -> non corretto
def run(f, st):
    global num_righe, num_colonne, S
    # verifica assunzioni sulle dimensioni della griglia
    X, Y = map(int, f[0].split())
    assert(MINN <= X <= MAXN)
    assert(MINN <= Y <= MAXN)
    num_righe = X
    num_colonne = Y
    # verifica che Mojito sia dentro la griglia
    S = set()
    assert(verifica_cella(*map(int, f[1].split())))
    # veririca assunzione sul numero di ragazzi
    N = int(f[2])
    assert(MINN <= N <= MAXN)
    # verifica che i ragazzi (ed i rispettivi target) siano dentro la griglia
    for i in xrange(N):
        a, b, c, d = map(int, f[3 + i].split())
        verifica_cella(a, b)
        verifica_cella(c, d)
    # verifica che le celle occupate siano 1 + (2 per ciascun ragazzo)
    assert(len(S) == 1 + 2 * N)
    # verifica il numero di righe del file di input
    assert(len(f) == 3 + N)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
