/*
  Stefano Maggiolo, 24/03/2012

  Dijkstra 20uplicando i nodi
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 30;
const int MAXM = 100;
const int MR = 20;
const int INF = 2000000000;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N, M, C, K;
int aria[MAXN+10];
vector<pair<int, int> > adj[MAXN+10];
int dist[MAXN+10][MR+1];// dist[i][x] = Distanza minima da start a i,
// non respirando da al più x metri.
int vis[MAXN+10][MR+1];
int q[MAXN+10];

int
main(void)
{
  in >> N >> M >> C >> K;
  assert(2 <= N && N <= MAXN);
  assert(2 <= M && M <= MAXM);
  assert(1 <= C && C <= N);
  assert(0 <= K && K <= N);
  for (int i = 0; i < K; i++)
    {
      int tmp;
      in >> tmp;
      assert(1 <= tmp && tmp <= N && aria[tmp-1] == 0);
      aria[tmp-1] = 1;
    }
  for (int i = 0; i < M; i++)
    {
      int tmp1, tmp2, v;
      in >> tmp1 >> tmp2 >> v;
      assert(1 <= tmp1 && tmp1 <= N);
      assert(1 <= tmp2 && tmp2 <= N);
      assert(tmp1 != tmp2);
      // Limiti per v?
      if (v <= MR)
        {
          adj[tmp1-1].push_back(make_pair(tmp2-1, v));
          adj[tmp2-1].push_back(make_pair(tmp1-1, v));
        }
    }
  for (int i = 0; i < N; i++)
    for(int x = 0; x <= MR; x++)
      dist[i][x] = INF;
  for(int x = 0; x <= MR; x++)
    dist[0][x] = 0;

  // (dist, (i, x))
  priority_queue< pair<int, pair<int, int> > > q;
  q.push(make_pair(-0, make_pair(0, 0)));

  while (!q.empty())
    {
      pair<int, pair<int, int> > ttt = q.top();
      int d, i, x;
      d = -ttt.first;
      i = ttt.second.first;
      x = ttt.second.second;
      q.pop();
      if (vis[i][x])
        continue;
      vis[i][x] = 1;

      for (int k = 0; k < adj[i].size(); k++)
        {
          int j, v;
          j = adj[i][k].first;
          v = adj[i][k].second;
          if (v + x > MR)
            continue;
          int start = v + x;
          int end = MR;
          if (aria[j])
            end = start = 0;

          int newd = dist[i][x] + v;

          for (int l = start; l <= end; l++)
            if (dist[j][l] > newd)
              {
                dist[j][l] = newd;
                q.push(make_pair(-newd, make_pair(j, l)));
              }
        }
    }
  int result = dist[C-1][0];
  if (result == INF) result = -1;
  out << result << endl;
  return 0;
}

