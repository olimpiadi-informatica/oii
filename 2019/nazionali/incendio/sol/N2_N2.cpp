/*
 *  Soluzione di incendio.
 *
 *  Autore: Massimo Cairo
 *
 *  Descrizione: Calcola quando ogni cella va a fuoco (BFS). Poi fa una visita "greedy".
 *
 *  Tempo: O(N²)
 *  Spazio: O(N²)
 */

#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <cstdio>

using std::vector;
using std::queue;
using std::deque;
using std::pair;

int N;

vector<vector<int>> fire_time;
vector<vector<int>> reachable_up_to;

bool debug = false;

int alzati(int N, int M, int X[], int Y[])
{
  ::N = N;

  queue<int> Q[2];

  fire_time.resize(N);
  reachable_up_to.resize(N);
  for(int x = 0; x < N; x++) {
    fire_time[x].resize(N);
    reachable_up_to[x].resize(N);
    for(int y = 0; y < N; y++) {
      fire_time[x][y] = N+1;
      reachable_up_to[x][y] = -1;
    }
  }

  for(int i = 0; i < M; i++) {
    fire_time[X[i]][Y[i]] = 0;

    Q[0].push(X[i]);
    Q[1].push(Y[i]);
  }

  while(!Q[0].empty()) {
    int p[2];
    for(int d = 0; d < 2; d++) {
      p[d] = Q[d].front();
      Q[d].pop();
    }

    int t = fire_time[p[0]][p[1]];

    for(int d = 0; d < 2; d++) {
      for(int h = -1; h <= +1; h+=2) {
        if(p[d]+h < 0) continue;
        if(p[d]+h >= N) continue;

        int pp[2];
        pp[d] = p[d]+h;
        pp[!d] = p[!d];

        int &tt = fire_time[pp[0]][pp[1]];
        if(tt <= t+1) continue;

        tt = t+1;
        for(int dd = 0; dd < 2; dd++) {
          Q[dd].push(pp[dd]);
        }
      }
    }
  }

  if(debug) {
    fprintf(stderr, "Fire time:\n");
    for(int x = 0; x < N; x++) {
      for(int y = 0; y < N; y++) {
        fprintf(stderr, "%2d", fire_time[x][y]);
      }
      fprintf(stderr, "\n");
    }
  }

  reachable_up_to[0][0] = fire_time[0][0];

  deque<int> D[2];

  D[0].push_front(0);
  D[1].push_front(0);

  while(!D[0].empty()) {
    int p[2];
    for(int d = 0; d < 2; d++) {
      p[d] = D[d].front();
      D[d].pop_front();
    }

    int r = reachable_up_to[p[0]][p[1]];
    for(int d = 0; d < 2; d++) {
      for(int h = -1; h <= +1; h+=2) {
        int pp[2];
        pp[d] = p[d]+h;
        pp[!d] = p[!d];

        if(pp[d] < 0) continue;
        if(pp[d] >= N) continue;
        
        int ft = fire_time[pp[0]][pp[1]];
        int& rr = reachable_up_to[pp[0]][pp[1]];

        if(rr != -1) continue;

        if(ft >= r) {
          rr = r;
          for(int dd = 0; dd < 2; dd++) {
            D[dd].push_front(pp[dd]);
          }
        } else {
          rr = ft;
          for(int dd = 0; dd < 2; dd++) {
            D[dd].push_back(pp[dd]);
          }
        }
      }
    }
  }

  if(debug) {
    fprintf(stderr, "Reachable up to:\n");
    for(int x = 0; x < N; x++) {
      for(int y = 0; y < N; y++) {
        fprintf(stderr, "%2d", reachable_up_to[x][y]);
      }
      fprintf(stderr, "\n");
    }
  }

  return reachable_up_to[N-1][N-1] - 1;
}

