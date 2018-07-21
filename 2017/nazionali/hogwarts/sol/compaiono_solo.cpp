/** Soluzione per archi che compaiono e basta (lineare) **/

#include <queue>
using namespace std;

const int INF = 1000000000;

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    
    vector < pair <int, int> > archi[N]; // indice e vertice d'arrivo di tutti gli archi uscenti da ogni nodo
    for (int i = 0; i < M; i++) {
        archi[A[i]].push_back(make_pair(i, B[i]));
        archi[B[i]].push_back(make_pair(i, A[i]));
    }
    
    int dist[N]; // array in cui salverò le distanze dei nodi dal nodo 0
    for (int i = 0; i < N; i++) dist[i] = INF;
    
    priority_queue < pair <int, int> > bfs; // priority_queue della bfs
    bool fatto[N]; // array che salva se ho già visitato i nodi durante la bfs
    for (int i = 0; i < N; i++) fatto[i] = false;
    
    bfs.push(make_pair(0, 0));
    dist[0] = 0;
    
    while (!bfs.empty()) {
        int at = bfs.top().second;
        bfs.pop();
        // visito il nuovo nodo at, se già non l'ho fatto
        if (!fatto[at]) {
            // scorro tutti gli archi uscenti da at e vedo se posso migliorare il loro valore
            for (auto arco : archi[at]) {
                int scala = arco.first;
                int amico = arco.second;
                // posso utilizzare la scala solo se c'è ancora
                //~ if (dist[at] < fine[scala]) {
                    if (max(dist[at], inizio[scala])+1 < dist[amico]) {
                        dist[amico] = max(dist[at], inizio[scala])+1;
                        bfs.push(make_pair(-dist[amico], amico));
                    }
                //~ }
            }
            fatto[at] = true;
        }
    }
    return (dist[N-1] == INF)? -1 : dist[N-1];
}
