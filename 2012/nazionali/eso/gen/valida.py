#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 2)
    N, M = prima
    assert(len(f) == N+1)
    assert(1 <= N <= MAXN)
    data = map(lambda x: [int(y) for y in x.strip().split()], f[1:])

    # Controlla che le righe abbiano la lunghezza giusta
    assert(set(map(lambda x: len(x), data)) == set([M]))

    # Controlla che la parentesizzazione sia corretta
    for eso in data:
        pars = filter(lambda x: x < 0, eso)
        # La prima parentesi deve essere aperta tonda
        assert(pars[0] == -1)
        stack = []
        for pos, p in enumerate(pars):
            if p == -1 or p == -3:
                stack.append(p)
            elif p == -2 or p == -4:
                assert(stack.pop() == p+1)
            else:
                assert("Numero negativo errato" is None)
            # Controlla che lo stack non sia vuoto se non all'ultima
            # parentesi chiusa
            if len(stack) == 0:
                assert(pos == len(pars)-1)
        assert len(stack) == 0
    
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    try:
        import psyco
        psyco.full()
    except ImportError:
        stderr.write("Installa psyco per un po' di velocita` in piu`.\n")

    f = open(argv[1]).readlines()
    exit(run(f))


