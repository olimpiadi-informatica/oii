/*
  Stefano Maggiolo, copiando il .py di Roberto Grossi.
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int M;
int N;
vector<int> ad[MAXN];
bool vis[MAXN];
stack<int> q;

void
dfs(int start, int parent)
{
  q.push(start);
  vis[start] = true;
  for (unsigned int i = 0; i < ad[start].size(); i++)
    {
      int next = ad[start][i];
      if (!vis[next])
        dfs(next, start);
      else if (next != parent)
        {
          vector<int> sol;
          int x = q.top();
          q.pop();
          sol.push_back(x);
          while (next != x)
            {
              x = q.top();
              q.pop();
              sol.push_back(x);
            }
          out << sol.size() << endl;
          for (unsigned int j = 0; j < sol.size(); j++)
            out << sol[j]+1 << " ";
          out << endl;
          exit(0);
        }
    }
  q.pop();
}

int
main(void)
{
  in >> N >> M;
  assert(1 <= M && M <= MAXM);
  assert(1 <= N && N <= MAXN);
  for (int m = 0; m < M; m++)
    {
      int i, j, c;
      in >> i >> j >> c;
      assert(1 <= i && i <= N);
      assert(1 <= j && j <= N);
      i--;
      j--;
      assert(c == 0 || c == 1);
      if (c == 0) continue;
      ad[i].push_back(j);
      ad[j].push_back(i);
    }
  for (int i = 0; i < N; i++)
    if (!vis[i])
      dfs(i, -1);
  // Esco appena trovo un ciclo, se sono qui non ne ho trovati e
  // questo e` proibito dal testo.
  assert(false);
  return 0;
}
