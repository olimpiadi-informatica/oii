/*
  Autore

  Descrizione
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <set>
//#include <cstdio>

using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N, S, C;

struct back_edge {
  int negdelta, src_state, src_char;
  back_edge(int d, int s, int c) {
    negdelta = d;
    src_state = s;
    src_char = c;
  }
};

vector<list<back_edge> > inverse_transition;
vector<int> characters;

vector<vector<bool> > visited;
list< pair<int, int> > pool;
int total_zero_visited = 0;

int main(void)
{
  /*
    #ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
  */
  in >> N >> S >> C;
  inverse_transition.resize(S);

  for(int i=0;i<S*C; i++) {
    int cur_s, cur_c, next_s, delta;
    in >> cur_s >> cur_c >> next_s >> delta;
    inverse_transition[next_s].push_back(back_edge(-delta, cur_s, cur_c));
  }

  characters.resize(N);
  visited.resize(N);
  for(int i=0; i<N; i++) {
    in >> characters[i];
    visited[i].resize(S, false);
  }

  for(int i=0;i<S; i++) {
    pool.push_back(make_pair(0,i));
  }

  while(!pool.empty()) {
    pair<int, int> current = pool.front();
    pool.pop_front();
    int cur_n = current.first, cur_s = current.second;
    if(!visited[cur_n][cur_s]) {
        visited[cur_n][cur_s] = true;
        if(cur_s == 0)
          total_zero_visited++;
        for(list<back_edge>::iterator it=inverse_transition[cur_s].begin();
          it != inverse_transition[cur_s].end(); it++) {
          int prev_c = it->src_char;
          int delta = it->negdelta;
          int prev_n = cur_n + delta;
          int prev_s = it->src_state;
          if(prev_n >= 0 && prev_n < N
            && characters[prev_n] == prev_c && !visited[prev_n][prev_s]) {
            pool.push_back(make_pair(prev_n, prev_s));
          }
        }
    }
  }

  out << total_zero_visited << endl;
  for(int i=0; i<N; i++) {
    if(visited[i][0])
      out << i << endl;
  }
  return 0;
}

