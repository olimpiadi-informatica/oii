#!/usr/bin/env python
# Roberto

import sys

MaxN = 100000
MaxM = 200000

N = M = 0
adj = [[]]
seen = []
isprt = False
endpoint = -1
parent = []
result = []

def dfs( u ):
    global N, M, adj, seen, parent, result, isprt, endpoint

    seen[u] = True
    for v in adj[u]:
        if not seen[v]:
            parent[v] = u
            if dfs( v ):
                if isprt:
                    result += [u+1] 
                if u == endpoint:
                    isprt = False
                return True
        elif v != parent[u]:
            isprt = True
            endpoint = v
            result += [u+1] 
            return True
    return False        


def mdfs():
    global N, M, adj, seen, parent, result

    parent = [-1 for u in range(N)]
    seen = [False for u in range(N)]
    for u in range(N):
         if not seen[u] and dfs( u ):
             # found cycle: print it
             out = sys.stdout
             out.write('%d\n' % len(result))
             for u in result:
                 out.write('%d ' % u)
             out.write('\n')
             return True
    return False


def run():
    global N, M, adj
    # read input
    cin = sys.stdin
    linea = cin.readline()
    prima = [int(x) for x in linea.split()]
    N, M = prima[0], prima[1]
    
    # check input params
    assert (3 <= N <= MaxN)
    assert (N < M <= MaxM)

    # build the graph induced by the green edges
    adj = [[] for i in range(N)]
    for i in range(M):
        linea = cin.readline()
        tripla = [int(x) for x in linea.split()]
        if (tripla[2]): #green edges
            adj[tripla[0]-1] += [tripla[1]-1]
            adj[tripla[1]-1] += [tripla[0]-1]
    M = sum([len(x) for x in adj])/2

    #start computation
    return 0 if mdfs() else 1


# main
if __name__ == '__main__':
    sys.exit(run())
