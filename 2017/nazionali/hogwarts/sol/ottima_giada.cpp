/*
 *  Soluzione di hogwarts.
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Soluzione ottima con bfs che scorre i tempi
 * 
 */

#include <vector>
#include <iostream>

using namespace std;

const int INF = 1000000000;
const int MAXT = 5000000;
const int MAXN = 1000000;

vector < pair <int, int> > archi[MAXN+1];

vector <int> raggiunti[MAXT+1];
bool fatto[MAXN+1];
int dist[MAXN+1];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    
    for (int i = 0; i < M; i++) {
        archi[A[i]].push_back(make_pair(i, B[i]));
        archi[B[i]].push_back(make_pair(i, A[i]));
    }
    
    for (int i = 0; i < N; i++) {
        fatto[i] = false;
        dist[i] = INF;
    }
    
    raggiunti[0].push_back(0);
    dist[0] = 0;
    
    for (int t = 0; t <= MAXT; t++) {
        for (int v : raggiunti[t]) {
            if (!fatto[v]) {
                for (auto arco : archi[v]) {
                    int scala = arco.first;
                    int amico = arco.second;
                    int tempo = max(dist[v], inizio[scala])+1;
                    if (!fatto[amico] and dist[v] < fine[scala] and tempo < dist[amico]) {
                        dist[amico] = tempo;
                        raggiunti[tempo].push_back(amico);
                    }
                }
                fatto[v] = true;
            }
        }
    }
    return (dist[N-1] == INF)? -1 : dist[N-1];
}
