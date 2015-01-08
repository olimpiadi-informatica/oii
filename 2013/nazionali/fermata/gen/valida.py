#!/usr/bin/env python2

from limiti import *

from sys import argv, exit, stderr
import os

def usage():
    print >> stderr, "Usage: %s file_input.txt" % \
        os.path.basename(argv[0])
    exit(1)

def run(f):
    assert(len(f) >= 1)
    prima = [int(x) for x in f[0].split()]
    assert(len(prima) == 3)
    N, S, C = prima
    assert(1 <= N <= MAXN)
    assert(1 <= S <= MAXS)
    assert(1 <= C <= MAXC)
    assert(len(f) == 1 + S*C + N)
    transition_rows = f[1:S*C+1]
    character_rows = f[S*C+1:]

    t_table = []
    for x in xrange(S):
        t_table.append([(-1,-1) for y in xrange(C)])
    for t_row in transition_rows:
        values = [int(x) for x in t_row.split()]
        assert(len(values) == 4)
        cur_s, cur_c, next_s, delta = values

        assert(0 <= cur_s < S)
        assert(0 <= cur_c < C)
        assert(0 <= next_s < S)
        # Dovrebbe assicurare che tutta la tabella delle transizioni
        # sia inizializzata.
        assert(t_table[cur_s][cur_c][0] == -1)
        t_table[cur_s][cur_c] = (next_s, delta)

    c_table = [0 for x in xrange(N)]
    for i, c_row in enumerate(character_rows):
        values = [int(x) for x in c_row.split()]
        assert(len(values)==1)
        char, = values
        c_table[i] = char
        for state in xrange(S):
            assert(i==0 or 0 <= i + t_table[state][char][1] < N)
    return 0 # Input corretto

if __name__ == "__main__":
    if len(argv) < 2:
        usage()

    f = open(argv[1]).readlines()
    exit(run(f))


