#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

const int MAXN = 100000;
// Per nostra convenienza definiamo infinito un valore che non possa essere confuso
// con nessuna distanza né velocità associate ad un nodo
const int INF = std::numeric_limits<int>::max();

// adj[i] contiene tutti tutti i vicini del nodo i
std::vector<int> adj[MAXN + 1];
int distanza_da_W[MAXN + 1], distanza_da_L[MAXN + 1];

// Esegue una visita in ampiezza a partire dal nodo sorgente. Scrive le distanza ottenute nel
// vettore puntato da distanza
void BFS(int sorgente, int distanza[]) {
    std::fill(distanza, distanza + MAXN + 1, INF);
    distanza[sorgente] = 0;

    std::queue<int> Q;
    Q.push(sorgente);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        for (const int w: adj[v]) {
            if (distanza[w] == INF) {
                distanza[w] = distanza[v] + 1;
                Q.push(w);
            }
        }
    }
}

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int, int) {
    // Costruiamo i vettori di adiacenza di tutti i nodi
    for (int i = 0; i < M; i++) {
        adj[arco_da[i]].push_back(arco_a[i]);
        adj[arco_a[i]].push_back(arco_da[i]);
    }

    // Eseguiamo le visite in ampiezza
    BFS(W, distanza_da_W);
    BFS(L, distanza_da_L);
    int d = distanza_da_W[L];

    // Infine iteriamo sugli archi
    int risposta = INF;
    for (int i = 0; i < M; i++) {
        int u = arco_da[i], v = arco_a[i];

        if (distanza_da_W[u] + distanza_da_L[v] + 1 == d ||
            distanza_da_W[v] + distanza_da_L[u] + 1 == d)
        {
            risposta = std::min(risposta, capacita[i]);
        }
    }

    return risposta;
}
