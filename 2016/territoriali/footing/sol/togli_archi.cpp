#include <vector>
#include <iostream>
#include <limits>
#include <queue>

const unsigned INFINITO = std::numeric_limits<unsigned>::max();
typedef unsigned vertice_t;

struct arco_t {
    vertice_t coda, testa; // I due estremi collegati
    unsigned peso;         // Il peso dell'arco
};

std::vector<arco_t> archi;                // Lista degli archi
std::vector<std::vector<arco_t>> vicini;  // Liste di adiacenza
unsigned N, M;

struct info_t {
    vertice_t ultimo;  // Il nodo finale del cammino
    unsigned peso;     // Il peso (cumulativo) del cammino

    bool operator< (const info_t& o) const {
        return peso > o.peso;
    }
};

unsigned percorso_minimo(vertice_t partenza, vertice_t arrivo) {
    std::vector<unsigned> distanza(N, INFINITO);
    std::priority_queue<info_t> coda;
    coda.push({partenza, 0});

    while (!coda.empty()) {
        // Cerca nella coda il cammino che conviene "continuare"
        vertice_t u = coda.top().ultimo;
        unsigned w = coda.top().peso;
        coda.pop();

        if (distanza[u] == INFINITO) {
            // Non ho mai visto il nodo u
            distanza[u] = w;
            // Visita i vicini
            for (const arco_t& arco: vicini[u]) {
                if (arco.coda == partenza && arco.testa == arrivo) {
                    // Salta l'arco tolto
                    continue;
                }
                coda.push({arco.testa, w + arco.peso});
            }
        }
    }

    return distanza[arrivo];
}

int main() {
    // Input e output da/su file
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    std::cin >> N >> M;
    vicini.resize(N);

    for (int i = 0; i < M; ++i) {
        vertice_t u, v;
        unsigned w;
        std::cin >> u >> v >> w;

        // Per comodità riportiamo i nomi dei vertici ad essere 0-based
        --u;
        --v;

        // Popola le liste di adiacenza
        vicini[u].push_back({u, v, w}); // arco u -> v di peso w
        vicini[v].push_back({v, u, w}); // arco u <- v di peso w

        // Popola la lista degli archi
        archi.push_back({u, v, w});
    }

    // Prova per ogni arco
    unsigned risposta = INFINITO;
    for (const arco_t& arco: archi) {
        // Calcola la distanza tra u e v togliendo l'arco tra essi.
        unsigned pm = percorso_minimo(arco.coda, arco.testa);

        // Se da u ho effettivamente raggiunto v
        if (pm != INFINITO)
            risposta = std::min(risposta, arco.peso + pm);
    }

    std::cout << risposta << std::endl;
}
