#!/usr/bin/env python3

import limiti

import sys
import os


def usage():
    print("Usage: %s file_input.txt [subtask_number]" %
          os.path.basename(sys.argv[0]), file=sys.stderr)
    exit(1)


# per testare la correttezza dell'input, usate assert()
def run(f, st):
    N, M = map(int, f[0].split())

    limiti_st = limiti.subtasks[st]

    MIN_N = limiti_st.get('MIN_N', limiti.MIN_N)
    MAX_N = limiti_st.get('MAX_N', limiti.MAX_N)
    MIN_M = limiti_st.get('MIN_M', limiti.MIN_M)
    MAX_M = limiti_st.get('MAX_M', limiti.MAX_M)
    MIN_C = limiti_st.get('MIN_C', limiti.MIN_C)
    MAX_C = limiti_st.get('MAX_C', limiti.MAX_C)
    MIN_H = limiti_st.get('MIN_H', limiti.MIN_H)
    MAX_H = limiti_st.get('MAX_H', limiti.MAX_H)
    line = limiti_st.get('line', False)
    dag = limiti_st.get('dag', False)

    assert MIN_N <= N <= MAX_N
    assert MIN_M <= M <= MAX_M

    if line:
        assert M == N - 1

    H = list(map(int, f[1].split()))
    assert len(H) == N

    for h in H:
        assert MIN_H <= h <= MAX_H

    constraints = f[2:]

    assert len(constraints) == M

    e = set()
    for constr in constraints:
        a, b, c = map(int, constr.split())
        assert 0 <= a < N
        assert 0 <= b < N

        if line:
            assert b == a + 1
        if dag:
            assert b > a

        assert MIN_C <= c <= MAX_C

        assert a != b
        assert (a, b) not in e
        e.add((a, b))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    run(f, st)
