#include <iostream>
#include <vector>
#include <stack>
#include <string>

typedef unsigned vertice_t;

std::vector<std::vector<vertice_t>> vicini;
std::stack<vertice_t> ordinamento;
std::vector<bool> visto;

// Trova ricorsivamente un ordinamento topologico del DAG
void ordinamento_topologico(vertice_t u) {
    if (!visto[u]) {
        visto[u] = true;
        for (const vertice_t& v: vicini[u])
            ordinamento_topologico(v);
        ordinamento.push(u);
    }
}

int main() {
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

    unsigned N;
    std::string s;

    std::cin >> N >> s;
    vicini.resize(N);

    // Costruisci il grafo delle precedenze
    for (vertice_t i = 0; i < N - 1; ++i) {
        if (s[i] == '<')
            vicini[i].push_back(i + 1);
        else
            vicini[i + 1].push_back(i);
    }

    // Inizializza il vector globale "visto" con N valori false,
    // poi calcola un ordinamento topologico del grafo
    visto.resize(N, false);
    for (vertice_t i = 0; i < N; i++) {
        if (!visto[i])
            ordinamento_topologico(i);
    }

    // Assegna i numeri alle celle della griglia
    unsigned valore = 1;
    std::vector<unsigned> soluzione(N);
    while (!ordinamento.empty()) {
        // Estrai il prossimo nodo nell'ordinamento
        vertice_t cella = ordinamento.top();
        ordinamento.pop();

        // Assegna il valore
        soluzione[cella] = valore;
        ++valore;
    }

    for (vertice_t i = 0; i < N; i++)
        std::cout << soluzione[i] << " ";

    std::cout << std::endl;
}
