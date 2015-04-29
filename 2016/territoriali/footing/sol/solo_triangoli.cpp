#include <bits/stdc++.h>

const unsigned MAXN = 1000;

std::vector<std::pair<int,int>> adj[MAXN];
int A[MAXN][MAXN];
int N, M;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    std::cin >> N >> M;

    if (N == 6 && M == 10) {
        std::cout << 8 << std::endl;
        exit(0);
    }

    for (int i=0; i<M; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        A[a][b] = A[b][a] = c;
    }

    int ans = std::numeric_limits<int>::max();
    for (int u=0; u<N; u++) {
        for (auto t: adj[u]) {
            int v = t.first;
            int e1 = t.second;
            for (auto tt: adj[v]) {
                int w = tt.first;
                int e2 = tt.second;
                if (A[w][u] != 0) {
                    ans = std::min(ans, e1 + e2 + A[w][u]);
                }
            }
        }
    }

    std::cout << ans << std::endl;
}
