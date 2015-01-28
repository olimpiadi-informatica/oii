#!/usr/bin/python2

MAXN = 1000000
MAXT = 100000000

usage="""Generatore per "amici".

Parametri:
* N (numero di ospiti)
* K (numero degli amici)
* T (numero squilli di tromba)
* S (seed)

Constraint:
* 2 <= N < %d
* 2 <= K <= N-1
* 0 <= T < %d
""" % (MAXN, MAXT)

from sys import argv, exit
from numpy.random import seed, permutation, randint

if len(argv) != 5:
    print usage
    exit(1)
else:
    N, K, T, S = [int(x) for x in argv[1:]]
    
    seed(S)

    assert (2 <= N and N <= MAXN)
    assert (2 <= K and K <= N-1)
    assert (0 <= T and T <= MAXT)
    
    print N, K, T

    # Supponiamo all'inizio i K amici nelle posizioni P...P+K,
    # fissiamo una permutazione M a caso, e calcoliamo M^T; le
    # posizioni occupate dagli amici saranno le posizioni iniziali, la
    # permutazione sara` M^{-1}
    
    perm = list(permutation(N))
    permraised = [-1] * N
    perminv = [-1] * N
    P = randint(0, N)
    used = [False] * N
    revcicli = [-1] * N
    indice = [-1] * N
    cicli = []
    for i in xrange(N):
        perminv[perm[i]] = i
        if not used[i]:
            nuovo = [i]
            revcicli[i] = len(cicli)
            used[i] = True
            indice[i] = 0

            tmp = 1
            x = perm[i]
            while x != i:
                nuovo.append(x)
                revcicli[x] = len(cicli)
                used[x] = True
                indice[x] = tmp

                tmp += 1
                x = perm[x]

            permraised[i] = nuovo[T%len(nuovo)]
            cicli.append(nuovo)
        else:
            c = cicli[revcicli[i]]
            permraised[i] = c[(indice[i] + T) % len(c)]

    for i in xrange(N):
        print perminv[i]+1,
    print

    # Li outputto ordinati anche se nel testo non e` esplicito
    amici = [permraised[(P+i)%N]+1 for i in xrange(K)]
    amici.sort()
    for x in amici:
        print x,
    print
