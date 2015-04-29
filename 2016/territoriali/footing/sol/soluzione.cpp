#include <bits/stdc++.h>

#define DEBUG 0

const unsigned MAXN = 1000;

std::vector<std::pair<int,int>> adj[MAXN];
int N, M;

struct info_t {
    int endpoint;
    int weigth;
    int parent;

    bool operator < (const info_t& other) const {
        return weigth > other.weigth;
    }
};

int min_cycle(int start) {
    std::vector<int> dist(N, std::numeric_limits<int>::max());
    std::priority_queue<info_t> q;
    q.push({start, 0, -1});

    while (!q.empty()) {
        // Cerca nella coda il cammino che conviene "continuare"
        auto t = q.top();
        q.pop();

        int u = t.endpoint;
        int w = t.weigth;
        int p = t.parent;

        if (dist[u] == std::numeric_limits<int>::max()) {
            // Non ho mai visto il nodo
            dist[u] = w;
        } else {
            // Ho chiuso un ciclo (ed e' il piu' corto quindi return)
            return dist[u] + w;
        }

        // Visita i vicini (facendo attenzione a non tornare sul padre)
        for (auto t: adj[u]) {
            if (t.first != p) {
                q.push({t.first, w + t.second, u});
            }
        }
    }

    // Dal nodo "start" non sono visibili cicli
    return std::numeric_limits<int>::max();
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    std::cin >> N >> M;

    for (int i=0; i<M; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int ans = min_cycle(0);
#if DEBUG
    std::cout << min_cycle(0) << std::endl;
#endif
    for (int i=1; i<N; i++) {
        ans = std::min(ans, min_cycle(i));
#if DEBUG
        std::cout << min_cycle(i) << std::endl;
#endif
    }

    std::cout << ans << std::endl;
}
