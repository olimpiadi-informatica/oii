#!/usr/bin/env pypy

from __future__ import print_function

from limiti import *
from sys import argv, exit, stderr
import os
from random import random, randint, choice, sample, shuffle, seed
from math import log

usage="""Generatore di "caduta".

Parametri:
* N (numero di tessere del domino)
* S (seed)

Constraint:
* 1 <= N <= %d
""" % (MAXN)

class Block:
    def __init__(self, h, alte, critiche, maxH):
        self.h = h
        self.alte = alte
        self.critiche = critiche
        self.maxH = maxH
        assert(len(alte) == len(critiche))

    def __add__(self, other):
        return Block(self.h + other.h, self.alte + other.alte, self.critiche + other.critiche, None)

    def altezzealte(self):
        return [ self.h[i] for i in self.alte ]

    def altezzecrit(self):
        return [ self.critiche[i] - self.alte[i] + 1 for i in xrange(len(self.alte))]

altezze = []


def gen_random(a, b):
        assert(a <= b)
        return int((b - a + 2) ** random() + a - 1)

def sample_dist(N, H, K):
    assert(N >= H * (K-1) + 1)
    v = [randint(0, N - 1 - H * (K-1)) for _ in xrange(K)]
    v.sort()
    for i in xrange(K):
        v[i] += i*H
    return v


def build_block(N, H, K=None, compatto=True, maxH=None):

    #print("N: ", N, "H: ", H, "K: ", K, "Comp:", compatto, file=stderr)

    if K is None:
        K = randint(1, (2*N) / (H + 3) - 2)
    assert(K == 0 or 3 <= H <= MAXA/2)
    assert(K == 0 or N > (H+3)*(K+1)/2)

    altezze = [0 for i in xrange(N)]

    pos_alte = sample_dist(max(N-H, 0), H, K/2)

    proibite = sum([[i-1, i, i+1] for i in pos_alte], [])
    if len(proibite) and proibite[0] == -1:
        proibite = proibite[1:]
    proibite.append(N)

    altre = sample_dist(max(N-H-len(proibite), 0), H, (K+1)/2)

    k = 0
    for i in range(len(altre)):
        while altre[i]+k >= proibite[k]:
            k += 1
        altre[i] += k

    pos_alte += altre
    pos_alte.sort()
    pos_alte.append(N-1)
    pos_alte.append(N)

    assert(K==0 or pos_alte[1] > pos_alte[0] + 1)
    for i in xrange(2, K):
        assert(pos_alte[i] > pos_alte[i-1] + 1)
        assert(pos_alte[i] >= pos_alte[i-2] + H)
    assert(K==0 or N-pos_alte[-3] >= H)

    pos_critiche = [0 for i in xrange(K)]

    covered = 0

    if maxH is None:
        if len(pos_alte) >= 3:
            maxH = H + N - pos_alte[-3] - 2 #Cambiato da -1 a -2
        else:
            maxH = MAXA

    for i in xrange(len(pos_alte) - 2):
        # if max(H, covered - pos_alte[i] + 2) > min(pos_alte[i+2] - pos_alte[i], maxH, MAXA):
        #     print("\n\nERRORE: ",len(altezze), len(pos_alte), i, file=stderr)
        #     print(H, covered - pos_alte[i] + 2, pos_alte[i+2] - pos_alte[i], maxH, covered, file=stderr)
        #     print("alte:",pos_alte, file=stderr)
        #     print("altz:",[altezze[_] for _ in pos_alte if _<N], file=stderr)
        #     print("crit:",pos_critiche, file=stderr)

        altezze[pos_alte[i]] = gen_random(max(H, covered - pos_alte[i] + 2), min(pos_alte[i+2] - pos_alte[i], maxH, MAXA))

        nuovo_covered = pos_alte[i] + altezze[pos_alte[i]] - 1

        assert(nuovo_covered < pos_alte[i+2])

        pos_critiche[i] = gen_random(max(covered+1,pos_alte[i]+2), min(nuovo_covered, pos_alte[i+1]))
        covered = nuovo_covered

    covered = 0
    critica = 0

    # print("alte:",pos_alte, file=stderr)
    # print("altz:",[altezze[_] for _ in pos_alte if _<N], file=stderr)
    # print("crit:",pos_critiche, file=stderr)

    pos_critiche.append(N)

    for i in range(N):

        if pos_critiche[critica] <= i:
            critica += 1

        if altezze[i] == 0:
            altezze[i] = gen_random(1 + (compatto and covered <= i < N-1), min(pos_critiche[critica] - i, H-1, MAXA))
            covered = max(covered, i + altezze[i] - 1)
        else:
            covered = pos_critiche[critica]

    #print("POSA:", pos_alte[:-2])
    #print("POSC:", pos_critiche[:-1])

    #for x in pos_critiche[:-1]:
    #    print("PC:",x)
    #    altezze[x] = 0

    return Block(altezze, pos_alte[:-2], pos_critiche[:-1], maxH)


def preserving_swap(H, S, prima, dopo, allow):
    altezze = prima.altezzealte() + dopo.altezzealte()
    critiche = prima.altezzecrit() + dopo.altezzecrit()
    if not allow:
        altezze.append(1)
        critiche.append(0)

    allowed = [min(H-1, i+1) for i in xrange(S)]

    K = len(altezze)
    stillok = []
    for i in xrange(K):
        if allowed[altezze[i] - H] >= critiche[i]:
            stillok.append((altezze[i], -critiche[i], i))
    stillok.sort()
    # print("K:", K, file=stderr)
    # print("STILLOK_START:", stillok, file=stderr)

    if len(stillok) == 0:
        return -1, allowed

    C = choice(stillok)[2] if allow else K-1
    mincrit = min([ -sok[1] for sok in stillok ])

    # print("C_INIT:", C, file=stderr)
    # print("CritMin:", mincrit, file=stderr)

    for sok in stillok:
        _, _, i = sok

        if altezze[i] > altezze[C]:
            if critiche[i] > mincrit:
                #if not allow:
                #print(i, altezze[i], altezze[i] - H, len(allowed), len(critiche), file=stderr)
                #print(allowed[altezze[i] - H])
                #print(min(allowed[altezze[i] - H], critiche[i] - 1))
                allowed[altezze[i] - H] = min(allowed[altezze[i] - H], critiche[i] - 1)
            else:
                altezze[i] = randint(max(mincrit,H), altezze[C])
                mod = prima if i < len(prima.alte) else dopo
                idx = i if i < len(prima.alte) else i-len(prima.alte)
                mod.h[mod.alte[idx]] = altezze[i]


    for i in reversed(xrange(S-1)):
        allowed[i] = min(allowed[i], allowed[i+1])

    #allowed.reverse()#DEBUG
    #print("Allow:", (allowed), file=stderr)
    #allowed.reverse()#DEBUG

    if not allow:
        return -1, allowed

    stillok = []
    for i in xrange(K):
        if allowed[altezze[i] - H] >= critiche[i]:
            stillok.append((altezze[i], -critiche[i], i))
    stillok.sort()

    #print("STILLOK_END:", stillok, file=stderr)

    assert(len(stillok))

    C = stillok[-1][2]
    h = allowed[altezze[C] - H]
    for ok in stillok:
        if ok[0] == stillok[-1][0] and ok[1] < stillok[-1][1]:
            h = min(h, -ok[1] - 1)

    #print(critiche, C, critiche[C], h, file=stderr)
    allowed[altezze[C] - H] = randint(critiche[C], h)

    for i in xrange(K):
        if altezze[i] < altezze[C]:
            allowed[altezze[i] - H] = min(allowed[altezze[i] - H], critiche[i] - 1)

    for i in reversed(xrange(S-1)):
        allowed[i] = min(allowed[i], allowed[i+1])

    return altezze[C] - H, allowed


def gen_tanti_candidati(N, T):
    #print(T, file=stderr, end='\n')
    if T == "ok":
        return build_block(N, N, 0, True).h
    if T == "random":
        K = gen_random(2, 4)
        P = sample(xrange(N), K-1)
        P += [0, N]
        P.sort()
        h = []
        for i in xrange(K):
            h += build_block(P[i + 1] - P[i], N, 0, True).h
        return h

    assert(N >= 30)
    H = randint(5, min(MAXA/3, N/10+2))
    P = randint(3*H/2+5,N-5*H/2-3)

    #print("Costruzione blocco prima", file=stderr)
    prima = build_block(P, H)
    #print("Costruzione blocco mezzo", file=stderr)
    mezzo = build_block(H-2, H, 0, False)
    #print("Costruzione blocco dopo", file=stderr)
    dopo  = build_block(N-P-H+2, H, maxH=prima.maxH)

    if T == "alticritici":
        return prima.h + mezzo.h + dopo.h #["P"] + prima.h + ["M"] + mezzo.h + ["D"] + dopo.h #DEBUG #

    C, allowed = preserving_swap(H, P - prima.alte[-1] - 1, prima, dopo, T == "rimpiazzok")

    a = prima.alte[-1]
    covered = a + prima.h[a] - 1
    #print("Unico possibile:", C, file=stderr)
    for i in xrange(len(allowed)):
        j = a + i + 1
        if len(allowed) - i - 1 == C:
            prima.h[j] = allowed[-i-1]
            #print("set pos:", j, "to", allowed[-i-1], file=stderr)
        else:
            mx = allowed[-i-1]
            if j < prima.critiche[-1]:
                mx = min(mx, prima.critiche[-1] - j)

            prima.h[j] = gen_random(1 if covered > j or j == P-1 else 2, mx)
            assert(j + allowed[-i-1] <= P)
        covered = max(covered, j + prima.h[j] - 1)

    return prima.h + mezzo.h + dopo.h # ["P"] + prima.h + ["M"] + mezzo.h + ["D"] + dopo.h #DEBUG #


def cairo(N):
    assert N >= 500

    NN = N/10

    # randint is inclusive
    P = randint(1, NN/3 - 3)
    Q = randint(P+1, NN/3 - 2)
    R = randint(P+Q+1, 2*NN/3 - 4)
    H = randint(R+1, 2*NN/3 - 3)
    G = randint(P+1, Q)

    assert 1 <= P < G <= Q < R < H
    assert P < R-Q

    N1 = H+G

    assert N1 <= NN

    altezze3 = [1] * N1

    altezze3[0] = H
    for i in range(1,P):
        altezze3[i] = randint(1,min(P-i, H/2))
    for i in range(P,Q):
        altezze3[i] = randint(min(2, Q-i+1),min(Q-i+1, H/2, G))
    for i in range(Q,R):
        altezze3[i] = randint(1,min(R-i, H/2, G))
    for i in range(R,H):
        altezze3[i] = randint(1,min(H-i, H/2, G))
    for i in range(H,N1-1):
        altezze3[i] = randint(1,min(H/2, N1-i-1))

    A = randint(1,5) * H
    altezze1 = [2] * A
    for i in range(0,A-H,H/2):
        altezze1[i] = H
        for j in range(i+1,i+H/2):
            altezze1[j] = randint(1,min(i+H/2-j, H/2, G))

    altezze = altezze1 + altezze3

    altezze0 = [2] * (N-len(altezze))
    altezze = altezze0 + altezze

    assert len(altezze) == N
    return altezze

def run(N, T):
    print(N)

    #["ok", "random", "alticritici", "rimpiazzok", "altro", "avantipoco", "uguali"]
    if T == "avantipoco":
        h = cairo(N)
    elif T == "uguali":
        H = 1 if random() > 0.5 else randint(2, MAXA)
        h = [H] * N
    else:
        h = gen_tanti_candidati(N, T)

    print(" ".join(map(str, h)))

if __name__ == "__main__":
    if len(argv) != 4:
        print(usage)
        exit(1)

    N, S = map(int, argv[1::2])
    T = argv[2]

    assert (2 <= N <= MAXN)

    seed(S)
    run(N, T)
