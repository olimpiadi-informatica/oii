#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

const int MAXN = 100000;
// Per nostra convenienza definiamo infinito un valore che non possa essere confuso
// con nessuna distanza né velocità associate ad un nodo
const int INF = std::numeric_limits<int>::max();

// adj[i] contiene tutti gli archi che ammettono i come primo estremo. Ogni arco è rappresentato
// da una struttura arco_t che memorizza il secondo estremo e la capacità dell'arco
struct arco_t {
    int estremo, capacita;

    arco_t(int estremo, int capacita): estremo(estremo), capacita(capacita) {}
};

std::vector<arco_t> adj[MAXN + 1];
int distanza[MAXN + 1], velocita[MAXN + 1];

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int, int) {
    // Costruiamo i vettori di adiacenza di tutti i nodi
    for (int i = 0; i < M; i++) {
        adj[arco_da[i]].emplace_back(arco_a[i], capacita[i]);
        adj[arco_a[i]].emplace_back(arco_da[i], capacita[i]);
    }

    // Passo 1: inizializziamo a INF gli array distanza e velocità, ad eccezione di
    // distanza[W], che invece vale 0
    std::fill(distanza, distanza + N + 1, INF);
    std::fill(velocita, velocita + N + 1, INF);
    distanza[W] = 0;

    // Passo 2: Processa i nodi in ordine di distanza da W
    std::queue<int> Q;
    Q.push(W);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        // Iteriamo su tutti i vicini w del nodo v
        for (const auto& arco: adj[v]) {
            int w = arco.estremo;
            int c = arco.capacita;

            if (distanza[w] > distanza[v]) {
                // Se è la prima volta che incontriamo il nodo w, mettiamolo nella coda
                // dei nodi da processare
                if (distanza[w] == INF)
                    Q.push(w);

                // Aggiorna distanza e velocità del nodo w.
                distanza[w] = distanza[v] + 1;
                if (velocita[w] > std::min(velocita[v], c))
                    velocita[w] = std::min(velocita[v], c);
            }
        }
    }

    return velocita[L];
}
