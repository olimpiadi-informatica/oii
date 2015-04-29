#include <bits/stdc++.h>

#define DEBUG 0

const unsigned MAXN = 1000;

std::vector<std::pair<int,int>> adj[MAXN];
int N, M;
int dist[MAXN];

int gstart;
int best;
void dfs(int u, int parent, int peso_parziale) {
    dist[u] = peso_parziale;
    for (auto p: adj[u]) {
        int v = p.first;
        int w = p.second;
        if (v == parent) {
            continue;
        }
        if (v == gstart) {
            best = std::min(best, peso_parziale + w);
        }
        if (dist[v] > peso_parziale + w) {
            dfs(v, u, peso_parziale + w);
        }
    }
}

int min_cycle(int start) {
    memset(dist, 63, sizeof dist);
    gstart = start;
    best = 2000000000;
    dfs(start, -1, 0);
    return best;
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
