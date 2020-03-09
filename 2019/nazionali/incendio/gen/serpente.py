#!/usr/bin/env python3

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "incendio".

Parametri:
* N (dimensione griglia)
* M (numero di incendi)
* T (numero subtask)
* S (seed)

Constraint:
* 1 <= N <= %d
* 1 <= M <= %d
""" % (MAXN, MAXM)


#
# Funzioni di stampa modulari per file binari o in chiaro
#
BINARY = False

def bwrite(x, l):
    if isinstance(x, str):
        if len(x) == l:
            stdout.buffer.write(x.encode('ascii'))
        else:
            stdout.buffer.write(len(x).to_bytes(4, 'little'))
            stdout.buffer.write(x.encode('ascii'))
    else:
        stdout.buffer.write(x.to_bytes(l, 'little'))

def print_nums(*args, byte_len=4):
    if isinstance(byte_len, int):
        byte_len = [byte_len for _ in range(len(args))]
    if BINARY:
        for i in range(len(args)):
            bwrite(args[i], byte_len[i])
    else:
        print(' '.join(map(str, args)))

def print_vectors(*args, byte_len=4, interleaved=True):
    if isinstance(byte_len, int):
        byte_len = [byte_len for _ in range(len(args))]
    if BINARY:
        for i in range(len(args)):
            for x in args[i]:
                bwrite(x, byte_len[i])
    elif interleaved:
        for i in range(len(args[0])):
            print(' '.join(str(x[i]) for x in args))
    else:
        for i in range(len(args)):
            print(' '.join(map(str, args[i])))
#
# Fine
#

def print_tabs(s, v):
    print(s + ' ' + '\t'.join(map(str, v)))

def regsample(a, b, n):
    r = (b - a - n) // (n + 1)
    r = max(randint(0, r) for _ in range(3))
    l = sorted(sample(range(a, b - (n+1)*r), n))
    return [l[i]+r*(i+1) for i in range(n)]

def run(N, M, T):
    assert M >= 9 and N >= 9
    assert M <= N * (N-1) // 4
    
    # distance between rows
    H = min(randint(max(2*N//M+1, 2), min(N//3, N*(N-1)//M//2)) for _ in range(3))
    # number of rows
    R = max(randint(max(2, 2*M//N), min(N//H - 1, H*M//N)) for _ in range(2))

    # center position of rows
    rows = sorted(randint(0, N - H * (R+1)) for _ in range(R))
    rows = [0] + [rows[i] + (i+1) * H for i in range(R)] + [N]
    # width of rows
    width = [randint(0, min(rows[i+1]-rows[i], rows[i+2]-rows[i+1])-H) for i in range(R)]
    # extreme points of rows
    length = [[randint(H, N//2),N] if i%2 else [0, randint(N//2, N-H)] for i in range(R)]
    rows = rows[1:-1]
    # number of fires in rows
    nums = [0] + regsample(0, M, R-1) + [M]
    nums = [nums[i+1]-nums[i] for i in range(R)]
    for i in range(R):
        if nums[i] > length[i][1]-length[i][0]:
#            print("overflow")
            return run(N, M, T)
    fires = sum([[(x, randint(rows[i]-width[i], rows[i]+width[i])) for x in regsample(length[i][0], length[i][1], nums[i])] for i in range(R)], [])
    shuffle(fires)
#    print("H, R:", H, R)
#    print_tabs("rows: ", rows)
#    print_tabs("width:", width)
#    print_tabs("lenX: ", [i[0] for i in length])
#    print_tabs("lenY: ", [i[1] for i in length])
#    print_tabs("nums: ", nums)
#    print_tabs("fireX:", [i[0] for i in fires])
#    print_tabs("fireY:", [i[1] for i in fires])

    print_nums(N, M)
    for fire in fires:
        print_nums(fire[0], fire[1])


if __name__ == "__main__":
    if len(argv) != 5:
        print(usage)
        exit(1)

    N, M, T, S = map(int, argv[1:])

    assert (1 <= N <= MAXN)
    assert (1 <= M <= MAXM)
    assert (1 <= M <= (N*N-2))
    seed(S)
    run(N, M, T)
