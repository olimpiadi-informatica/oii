#!/usr/bin/env pypy3

from limiti import *
from sys import argv, exit, stderr, stdout
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "lungomare".

Parametri:
* N (numero)
* L (lunghezza totale del lungomare)
* P (lunghezza massima di una passerella)
* U (tipo generazione, 0: tutto uguale, 1: passerelle uguali, 2: random, 3: da soluzione)
* S (seed)

Constraints:
* 1 <= N <= %d
* 1 <= L <= %d
* 1 <= P <= %d
""" % (MAXN, MAXL, MAXL)

#
# Funzioni di stampa modulari per file binari o in chiaro
#
BINARY = True

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


def run(N, L, P, U):
    print_nums(N, L, byte_len=8)
    # tutto uguale (servono P molto vicini a L/2 per dare caso un solo da prendere)
    if U == 0:
        a = max(randint(1, (L-2)//(N-1)), randint(1, (L-2)//(N-1)))
        b = randint(1, L-1-(N-1)*a)
        print_vectors([a*i + b for i in range(N)], [P for i in range(N)], byte_len=8, interleaved=False)
    # passerelle uguali
    if U == 1:
        assert(L > 2*N)
        prima, dopo = sorted([randint(0,N-1),randint(0,N-1)])
        diff = max(randint(1, (L-N-1)//(prima+N-1-dopo)), randint(1, (L-N-1)//(prima+N-1-dopo)))
        D = sorted(sample(range(1,L-1-(prima+N-1-dopo)*diff), N))
        for i in range(N):
            D[i] += (min(i,prima) + max(i-dopo,0))*diff
        print_vectors(D, [P for i in range(N)], byte_len=8, interleaved=False)
    # random
    if U == 2:
        D = sorted(sample(range(1,L), N))
        print_vectors(D, [randint(1,P) for i in range(N)], byte_len=8, interleaved=False)
    # da soluzione
    if U == 3:
        C = max(randint((L-1)//(N+1)+3, L), randint((L-1)//(N+1)+3, L));
        while True:
            try:
                Dsol = [0]
                Psol = [0]
                while Dsol[-1] < L:
                    Dsol.append(randint(1, C-1-Psol[-1])+Dsol[-1])
                    Psol.append(C-Psol[-1]-Dsol[-1]+Dsol[-2])
                assert(len(Dsol) < 0.75*N)
                break
            except:
                pass
        Dadd = sample(range(1,L-len(Dsol)+2), N-len(Dsol)+2)
        Padd = [0 for _ in range(len(Dadd))]
        j = 1
        for i in range(len(Dadd)):
            while Dsol[j] <= Dadd[i]+j-1:
                j += 1
            Dadd[i] += j-1
            Padd[i] = C-(Dadd[i]-Dsol[j-1]+Psol[j-1])
            Padd[i] = max(Padd[i], C-(Dsol[j]-Dadd[i]+Psol[j]))
            Padd[i] = randint(min(Padd[i],P),P)
        Dsol = Dsol[1:-1]
        Psol = Psol[1:-1]
        l = [(Dsol[i], Psol[i]) for i in range(len(Dsol))] + [(Dadd[i], Padd[i]) for i in range(len(Dadd))]
        l.sort()
        D = [x[0] for x in l]
        P = [x[1] for x in l]
        print_vectors(D, P, byte_len=8, interleaved=False)


if __name__ == "__main__":
    if len(argv) == 2:
        f = open(argv[1], 'r').readlines()
        for r in f:
            for x in r.strip().split():
                print_nums(int(x), byte_len=8)
        exit(0)
    
    if len(argv) != 6:
        print(usage)
        exit(1)

    N, L, P, U, S = map(int, argv[1:])
    
    assert (1 <= N <= MAXN)
    assert (N < L <= MAXL)
    assert (1 <= P <= MAXL)
    assert (0 <= U <= 4)
    seed(S)
    run(N, L, P, U)
