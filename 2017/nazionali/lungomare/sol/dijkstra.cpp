/*
 *  Dijkstra su grafo completo O(N^2).
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: calcola il grafo completo delle distanze tra spiagge e fa un dijkstra
 *  modificato per prendere il max anziché la somma.
 */

#include <algorithm>
#include <vector>
#include <iostream>

#define MAXN 5240

using namespace std;
typedef long long int ll;


ll Matrix[MAXN][MAXN]; // l'inizio è N mentre la fine è N+1
ll Dist[MAXN];
bool Visited[MAXN];


ll percorri(int N, ll L, ll D[], ll P[]) {
    // matrice di adiacenza
    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            Matrix[i][j] = Matrix[j][i] = P[i]+P[j]+D[j]-D[i];
        }
        Matrix[N][i] = Matrix[i][N] = P[i]+D[i];
        Matrix[N+1][i] = Matrix[i][N+1] = P[i]+L-D[i];
        Visited[i] = false;
        Dist[i] = L;
    }
    Matrix[N][N+1] = Matrix[N+1][N] = L;
    // dijkstra
    Visited[N] = Visited[N+1] = false;
    Dist[N] = 0;
    Dist[N+1] = L;
    while (true) {
        int v, imin = -1;
        ll dmin = L;
        for (v=0; v<N+1; v++) if (not Visited[v] and Dist[v] < dmin)  {
            imin = v;
            dmin = Dist[v];
        }
        if (imin < 0) break;
        v = imin;
        Visited[v] = true;
        for (int i=0; i<N+2; i++) if (i != v and not Visited[i]) {
            Dist[i] = min(Dist[i], max(Dist[v],Matrix[v][i]));
        }
    }
    return Dist[N+1];
}
