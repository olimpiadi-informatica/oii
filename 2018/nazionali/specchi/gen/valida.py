#!/usr/bin/env python3

from limiti import *

import sys
import os

def usage():
    print("Usage: %s file_input.txt" % os.path.basename(sys.argv[0]), file=sys.stderr)
    exit(1)

pos = 0

def read_int(f):
    global pos
    pos += 4
    return int.from_bytes(f[pos-4:pos], byteorder='little')

def read_char(f):
    global pos
    pos += 1
    return f[pos-1:pos].decode('ascii')

def run(f, st):
    N = read_int(f)
    M = read_int(f)
    Q = read_int(f)
    assert(1 <= N <= MAXN)
    assert(1 <= M <= MAXN)
    assert(1 <= Q <= MAXQ)

    if st >= 0:
        print(N, M, Q, file=sys.stderr)
        print(ST[st], file=sys.stderr)
        assert(N <= ST[st][0])
        assert(M <= ST[st][0])
        assert(Q <= ST[st][1])
        query_alla_fine = ST[st][2]
    else:
        query_alla_fine = False

    assert(4+4+4+(1+4+4)*Q == len(f))
    permetti_update = True
    for i in range(Q):
        op = read_char(f)
        a = read_int(f)
        b = read_int(f)
        assert(op in ["?", "/", "\\"])
        if op == "?":
            assert(0 <= a <= 3)
            if a == 0 or a == 2: assert(0 <= b <= M-1)
            if a == 1 or a == 3: assert(0 <= b <= N-1)
            if query_alla_fine:
                permetti_update = False
        else:
            assert(0 <= a <= N-1)
            assert(0 <= b <= M-1)
            assert(permetti_update)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
    st = -1
    if len(sys.argv) >= 3:
        st = int(sys.argv[2])

    with open(sys.argv[1], "rb") as f:
        run(f.read(), st)
