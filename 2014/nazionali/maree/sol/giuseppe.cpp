#include <vector>
#include <stdint.h>
#include <cstddef>
#include <queue>
#include <iostream>

typedef uint32_t node_t;
typedef uint32_t dist_t;
typedef std::vector<node_t> adj_list_t;
typedef std::vector<adj_list_t> graph_t;

static const dist_t not_visited = dist_t(-1);

void bfs(graph_t const& g, dist_t max_time, node_t source, std::vector<dist_t>& distances)
{
  distances.assign(g.size(), not_visited);

  std::queue<node_t> Q;
  Q.push(source);
  distances[source] = 0;

  while (!Q.empty()) {
    node_t cur = Q.front();
    Q.pop();

    adj_list_t const& nbrs = g[cur];
    for (size_t i = 0; i < nbrs.size(); ++i) {
      node_t next = nbrs[i];
      if (distances[next] == not_visited && distances[cur] < max_time) {
        distances[next] = distances[cur] + 1;
        Q.push(next);
      }
    }
  }
}

int solve(int n, int m, int t, int S[], int E[])
{
  graph_t g(n);
  for (size_t i = 0; i < m; ++i) {
    g[S[i]].push_back(E[i]);
  }

  std::vector<dist_t> d, dc;
  bfs(g, t, 0, d);

  dist_t best = d[n - 1];
  if (best != not_visited) return best;

  bfs(g, n, n - 1, dc);

  for (node_t cur = 0; cur < n; ++cur) {
    if (d[cur] != not_visited && dc[cur] != not_visited) {
      best = std::min(best, dist_t(t) + dc[cur]);
    }
  }

  if (best != not_visited) return best;

  return -1;
}
