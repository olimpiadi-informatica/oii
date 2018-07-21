/** 
 * Soluzione di hogwarts per archi che possono solo scomparire.
 * Faccio una BFS normale tranne che prima di usare un arco controllo se c'è ancora.
 * (Alice)
 * 
 **/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

#define MAXN 1000001
#define MAXM 2000001
#define MAXT 5000005

using namespace std;

queue<int> nodi;
vector<pair<int, int> > Grafo[MAXN];
int distanze[MAXN];
bool raggiunto[MAXN];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i=0; i<M; i++) {
        Grafo[A[i]].push_back(make_pair(B[i], fine[i]));
        Grafo[B[i]].push_back(make_pair(A[i], fine[i]));
    }
    
    
    //for (int i=1; i<N; i++) distanze[i] = INT_MAX;
    nodi.push(0);
    while (!nodi.empty()) {
        int x = nodi.front();
        nodi.pop();
        int t = distanze[x];
        
        for (int i=0; i<(int)Grafo[x].size(); i++)
            if (t < Grafo[x][i].second) {
                if (raggiunto[Grafo[x][i].first]) continue;
                raggiunto[Grafo[x][i].first] = true;
                distanze[Grafo[x][i].first] = t+1;
                nodi.push(Grafo[x][i].first);
            }
    }
    
    if (raggiunto[N-1]) return distanze[N-1];
    else return -1;
}

