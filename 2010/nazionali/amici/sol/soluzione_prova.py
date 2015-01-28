#!/usr/bin/python

import sys

MAXN = 1000000
MAXT = 100000000

linea = sys.stdin.readline()
N, K, T = [int(x) for x in linea.split()]
linea = sys.stdin.readline()
perm = [int(x) for x in linea.split()]
linea = sys.stdin.readline()
amici = [int(x) for x in linea.split()]

assert (2 <= N and N <= MAXN)
assert (2 <= K and K <= N-1)
assert (0 <= T and T <= MAXT)

perm = [perm[i]-1 for i in xrange(N)]
amici = [amici[i]-1 for i in xrange(K)]

permraised = [-1] * N
used = [False] * N
revcicli = [-1] * N
indice = [-1] * N
cicli = []
for i in xrange(N):
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

s = [permraised[i] for i in amici]
s.sort()

if s[0] == 0 and s[-1] != N-1: print 1
elif s[0] > 0: print s[0]+1
else:
    for i in xrange(1, K):
        if s[i-1] != s[i]-1:
            print s[i]+1
            sys.exit(0)

assert(True)
