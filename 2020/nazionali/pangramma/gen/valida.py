#!/usr/bin/env pypy3

import limiti
import array

import sys
import os

def usage():
    print("Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0]), file=sys.stderr)
    exit(1)


# per testare la correttezza dell'input, usate assert()
def run(data, st):
    print(data)

    limiti_st = limiti.subtasks[st]

    MIN_N = limiti_st.get('MIN_N', limiti.MIN_N)
    MAX_N = limiti_st.get('MAX_N', limiti.MAX_N)
    MIN_K = limiti_st.get('MIN_K', limiti.MIN_K)
    MAX_K = limiti_st.get('MAX_K', limiti.MAX_K)

    etero = limiti_st.get('etero', False)
    below_mod = limiti_st.get('below_mod', False)

    N, K = data[0:2]

    assert MIN_N <= N <= MAX_N
    assert MIN_K <= K <= MAX_K

    V = data[2:]
    assert len(V) == N

    taken = [False] * K

    for v in V:
        assert 0 <= v < K
        taken[v] = True
    
    assert all(taken)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    with open(sys.argv[1], 'rb') as f:
        data = array.array("i", f.read())

    run(data, st)
