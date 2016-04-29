/**
 * 0-1 BFS sul grafo
 */

#include <cstdio>
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define MAXN 100

std::vector<std::pair<int, int>> adj[MAXN];

int shortest_path(int vertices) {
    std::deque<std::pair<int, int>> q;
    std::vector<int> dist(vertices, std::numeric_limits<int>::max());

    int start = 0;             // partenza
    int stop  = vertices - 1;  // arrivo

    q.push_front({start, 0});

    while (!q.empty()) {
        auto tmp = q.front();
        q.pop_front();

        int u = tmp.first;
        int w = tmp.second;

        if (dist[u] > w) {
            dist[u] = w;
            for (auto v : adj[u]) {
                if (dist[v.first] > dist[u] + v.second) {
                    if (v.second == 0) {
                        q.push_front({v.first, dist[u] + v.second});
                    } else {
                        q.push_back({v.first, dist[u] + v.second});
                    }
                }
            }
        }
    }

    return dist[stop];
}

int main() {
    FILE *fr, *fw;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    int N, A, B;
    assert(3 == fscanf(fr, "%d%d%d", &N, &A, &B));

    for(int i = 0; i < A + B; i++) {
        int a, b;
        assert(2 == fscanf(fr, "%d%d", &a, &b));
        a--;
        b--;

        int weight = (i >= A) ? 1 : 0;
        adj[a].push_back({b, weight});
        adj[b].push_back({a, weight});
    }

    fprintf(fw, "%d\n", shortest_path(N));
    fclose(fr);
    fclose(fw);
    return 0;
}
