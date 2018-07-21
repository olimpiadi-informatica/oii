/*
 * Soluzione di classifica.
 * 
 * Autore: Giada Franz
 * 
 * Descrizione: Risolvi il caso con gli archi fissi con una bfs.
 */

#include <queue>
#include <vector>
using namespace std;

const int MAXN = 1000000;
const int INF = 1000000000;

vector <int> grafo[MAXN+1];
int dist[MAXN+1];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i = 0; i < M; i++) {
        grafo[A[i]].push_back(B[i]);
        grafo[B[i]].push_back(A[i]);
    }
    for (int i = 0; i < N; i++) dist[i] = INF;
    
    queue <int> bfs;
    dist[0] = 0;
    bfs.push(0);
    
    while (!bfs.empty()) {
        int v = bfs.front();
        bfs.pop();
        for (int u : grafo[v]) {
            if (dist[u] > dist[v]+1) {
                dist[u] = dist[v]+1;
                bfs.push(u);
            }
        }
    }
    return (dist[N-1] == INF)? -1 : dist[N-1];
}

