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


vector< vector< pair<int, int> > > transition;
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
  transition.resize(S);
  for(vector< vector< pair<int, int> > >::iterator it = transition.begin(); 
    it!= transition.end(); it++) {
    it->resize(C);
  }

  for(int i=0;i<S*C; i++) {
    int cur_s, cur_c, next_s, delta;
    in >> cur_s >> cur_c >> next_s >> delta;
    transition[cur_s][cur_c] = make_pair(next_s, delta);
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
        for(int prev_s = 0; prev_s < S; prev_s++)
          for(int prev_c = 0; prev_c < C; prev_c++) {
            int dest_s = transition[prev_s][prev_c].first;
            int delta = transition[prev_s][prev_c].second;
            int prev_n = cur_n - delta;
            if(prev_n >= 0 && prev_n < N && dest_s == cur_s
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

