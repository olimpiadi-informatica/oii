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
list<int> good_cells;

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
  for(int i=0; i<N; i++) {
    in >> characters[i];
  }

  for(int start_n = 0; start_n < N; start_n++) {
    // out << "Starting from " << start_n << endl;
    int cur_n=start_n, cur_s=0;
    set<pair<int, int> > visited;
    while(cur_n != 0) {
      if(visited.find(make_pair(cur_n, cur_s)) != visited.end())
        break;
      visited.insert(make_pair(cur_n, cur_s));
      int next_s, delta;
      int c = characters[cur_n];
      next_s = transition[cur_s][c].first;
      delta = transition[cur_s][c].second;
      assert(0 <= cur_n + delta);
      assert(cur_n + delta < N);
      // out << cur_n << " " << cur_s << " -> " << cur_n + delta << " " << cur_s << endl;
      cur_n += delta;
      cur_s = next_s;
    }
    if(cur_n == 0)
      good_cells.push_back(start_n);
  }

  out << good_cells.size() << endl;
  for(list<int>::iterator it = good_cells.begin(); it != good_cells.end();
    it++) {
    out << *it << endl;
  }
  return 0;
}

