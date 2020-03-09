#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit, stderr
from random import randint, seed, shuffle, choice
usage = """Generatore di "antivirus".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""

DEBUG = False
cases = 0

def start_case(N1234, M):
    global cases
    print()
    print(" ".join(map(str, N1234)))
    print(M)
    cases += 1

def random_string(N, chars):
    # type: (int) -> List[str]
    return [choice(chars) for _ in range(N)]

def rimuovi_soluzioni(strings, M, virus, pos_virus, tiebreaker):
    sets = [set(), set(), set(), set()]
    for i, s in enumerate(["".join(s) for s in strings]):
        for j in range(len(s)-M+1):
            sets[i].add(s[j:j+M])
    common = sets[0] & sets[1] & sets[2] & sets[3] - {virus}
    for c in common:
        i = randint(0, 3)
        try:
            j = ("".join(strings[i])).index(c)
        # è possibile che togliendo una sottostringa comune, anche altre se ne vadano
        except:
            continue
        k = randint(0, M-1)
        if pos_virus[i] <= j+k <= pos_virus[i]+M-1:
            if j > pos_virus[i]:
                j = randint(pos_virus[i]+M-k, j+M-1-k)
            else:
                j = randint(j-k, pos_virus[i]-1-k)
        strings[i][j+k] = tiebreaker
    if common:
        rimuovi_soluzioni(strings, M, virus, pos_virus, choice(CHARS))

def casuale(N1234, M, chars=CHARS):
    # genera 4 stringhe casuali, aggiunge il virus e toglie le cose comuni
    assert(all(M <= N for N in N1234))
    assert(len(chars) >= 2)

    start_case(N1234, M)

    strings = []
    for N in N1234:
        strings.append(random_string(N, chars))

    virus = random_string(M, chars)
    pos_virus = list()
    for s in strings:
        i = randint(0, len(s)-M)
        s[i:i+M] = virus
        pos_virus.append(i)

    rimuovi_soluzioni(strings, M, "".join(virus), pos_virus, choice(CHARS))

    for s in strings:
        print("".join(s))
    if DEBUG:
        print("[DEBUG] virus:", "".join(virus), file=stderr)

if __name__ == "__main__":
    if len(argv) < 3:
        print(usage)
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    print(T)

    # a mano
    casuale([6, 8, 7, 10], 2, chars="dbpq")
    casuale([10, 15, 10, 10], 6, chars=CHARS)

    chars = ["ab"] * 1 + ["bdpq"] * 1 + ["db"] * 3 + ["pq"] * 3 + [CHARS] * 2
    shuffle(chars)
    
    # non a mano
    for chs in chars:
        N = [randint(50, 100) for _ in range(4)]
        casuale(N, randint(5, 20), chars=chs)

    assert cases == T
