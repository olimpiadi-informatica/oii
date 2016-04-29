#!/usr/bin/env python3

import sys
import random

from limiti import *

usage="""Generatore di "sentieri".

Parametri:
* N (num nodi)
* M (num archi)
* T (tipo)
* S (seed)

Tipo (T):
* 1  un albero formato da: cammino lungo (quasi tutti i nodi) e qualche arco inutile sui lati
* 2  alcune CC che formano un albero di CC

Constraint:
* 5 <= N <= %d
* 10 <= M <= %d
""" % (MAXN, MAXM)


def run(N, M, T):
    if T == 1:
        good = []
        bad  = []

        v = list(range(2, N))
        used = [1]
        for i in range(int(N * 0.7)):
            to = random.choice(v)

            if random.random() < 0.9:
                bad.append((used[-1], to))
            else:
                good.append((used[-1], to))

            v.remove(to)
            used.append(to)

        bad.append((used[-1], N))
        used.append(N)

        outer = set()  # nodi esterni al cammino
        while M - len(bad) - len(good) > 0:
            u = random.choice(v)
            w = random.choice(used)

            if u not in outer:
                outer.add(u)

                if random.random() < 0.9:
                    bad.append((u, w))
                else:
                    good.append((u, w))
    elif T == 2:
        v = list(range(2, N))
        cc = []
        ccs = N // 5
        for i in range(ccs):
            cc.append([])
            for j in range(4):
                x = random.choice(v)
                cc[-1].append(x)
                v.remove(x)
        while len(v) > 0:
            x = random.choice(v)
            random.choice(cc).append(x)
            v.remove(x)
        cc[0].append(1)
        cc[-1].append(N)

        bad = []
        good = []

        parents = [(0, 1)]
        for i in range(1, ccs):
            p = random.choice(parents)
            bad.append((random.choice(cc[i]), random.choice(cc[p[0]])))
            for j in range(p[1] + 1):
                parents.append((i, p[1] + 1))

        for c in cc:
            for i in range(len(c)):
                for j in range(i + 1, len(c)):
                    if random.random() < 0.9:
                        if random.random() < 0.5:
                            good.append((c[i], c[j]))
                        else:
                            bad.append((c[i], c[j]))

    if len(good) + len(bad) > M:
        raise Exception("Too few edges available, try: " + str(len(good) + len(bad)))

    print(N, len(good), len(bad))
    for e in good + bad:
        print(e[0], e[1])

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(usage)
        sys.exit(1)

    N, M, T, S = map(int, sys.argv[1:])

    assert 5 <= N <= MAXN
    assert 10 <= M <= MAXM
    assert T in (1, 2)

    random.seed(S)
    run(N, M, T)
