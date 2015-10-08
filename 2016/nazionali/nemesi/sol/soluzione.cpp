/**
 *  Soluzione di nemesi
 *
 *  Autore: Luca Versari
 *
 *  Descrizione: O(N) con una DFS.
 */
#include <vector>
#include <stdio.h>

void nuovo_gruppo();

void aggiungi(int bambino);

std::vector<int> gruppi;
std::vector<std::vector<int>> graph;
std::vector<int> third_group;

bool dfs(int n, int g) {
    if (gruppi[n] != -1)
        return 1-gruppi[n] != g;
    gruppi[n] = g;
    bool ok = true;
    for (auto v: graph[n]) {
        ok &= dfs(v, 1-g);
    }
    if (!ok) {
        gruppi[n] = 2;
        third_group.push_back(n);
    }
    return true;
}

void smista(int N, int nemico[]) {
    graph.resize(N);
    gruppi.resize(N, -1);
    for (int i=0; i<N; i++) {
        graph[i].push_back(nemico[i]);
        graph[nemico[i]].push_back(i);
    }
    for (int i=0; i<N; i++)
        if (gruppi[i] == -1)
            dfs(i, 0);
    for (int j=0; j<2; j++) {
        nuovo_gruppo();
        for (int i=0; i<N; i++)
            if (gruppi[i] == j)
                aggiungi(i);
    }
    if (!third_group.empty())
        nuovo_gruppo();
    for (auto i: third_group)
        aggiungi(i);
}
