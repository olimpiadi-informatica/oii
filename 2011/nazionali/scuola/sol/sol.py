#!/usr/bin/env python
# Roberto

import sys

MinN = 2
MaxN = 2100

def BipartiteGraphRounds(A,B):
    seq = []
    assert len(A) == len(B) 
    n = len(A)
    for r in xrange(n):
        roundx = [] 
        for i in xrange(n):
            roundx += [A[i], B[(i+r) % n]]
        seq += [roundx]
    return seq

def CompleteGraphRounds(A):
    n = len(A)
    if n == 2:
        return [A]
    else:
        A1 = [A[i] for i in xrange(n/2)]
        A2 = [A[i] for i in xrange(n/2,n)]
        seq = BipartiteGraphRounds(A1,A2)
        seq1 = CompleteGraphRounds(A1)
        seq2 = CompleteGraphRounds(A2)
        for i in xrange(len(seq1)):
            seq += [seq1[i]+seq2[i]]
        return seq

def run():
    # read input
    cin = sys.stdin
    linea = cin.readline()
    prima = [int(x) for x in linea.split()]
    N, P = prima[0], prima[1]
    
    # check input params
    assert MinN <= N <= MaxN
    assert P == 1 or P == 2

    # build the rounds
    vertexset = [i+1 for i in xrange(N)]
    if P == 1:
        result = BipartiteGraphRounds(vertexset,vertexset)
    else:
        power = MinN
        while power < N:
            power = power*2
        assert power == N 
        result = CompleteGraphRounds(vertexset)

    # print output
    out = sys.stdout
    for i in xrange(len(result)):
        m = len(result[i])-1
        for j in xrange(m):
            out.write('%d ' % result[i][j])
        out.write('%d\n' % result[i][m])


# main
if __name__ == '__main__':
    sys.exit(run())

