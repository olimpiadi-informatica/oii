/*
  Autore: Stefano Maggiolo

  Too tired for documentation
*/

#include <cassert>
#include <cstdio>
#include <vector>
#include <list>
#include <map>
#include <utility>

using namespace std;

const int MAXN = 100000;
const int MAXM = 1000000;

list<int> G[MAXN];

map< pair<int, int>, int > vis;

int N, M, A, B;
int NN;
list<int> path;

int degs[MAXN];
int ordegs[MAXN];

void
dfs(int start, list<int>::iterator pos)
{
  list<int>::iterator found = G[start].end();
  for (list<int>::iterator i = G[start].begin();
       i != G[start].end();
       ++i)
    if (!vis[make_pair(start, *i)])
      {
	found = i;
	if (*i == B)
	  continue;
        vis[make_pair(start, *i)] = 1;
        vis[make_pair(*i, start)] = 1;
        path.insert(pos, *i);
        NN++;
        degs[start]++;
        degs[*i]++;
        dfs(*i, pos);
        return;
      }
  // If we didnt found any other edge, but we have one to b, we use
  // it.
  if (found == G[start].end())
    return;

  vis[make_pair(start, *found)] = 1;
  vis[make_pair(*found, start)] = 1;
  path.insert(pos, *found);
  NN++;
  degs[start]++;
  degs[*found]++;
  dfs(*found, pos);
}

void
stampa()
{
  for (list<int>::iterator i = path.begin();
       i != path.end();
       ++i)
    printf("%d ", (*i)+1);
  printf("\n");
}

int main(){
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d %d %d %d", &N, &M, &A, &B);
  A--;
  B--;
  assert(1 <= N && N <= MAXN);
  assert(1 <= M && M <= MAXM);
  assert(0 <= A && A < MAXN);
  assert(0 <= B && B < MAXN);
  assert(A != B);

  for (int i = 0; i < M; i++)
    {
      int a, b;
      scanf("%d %d", &a, &b);
      a--;
      b--;
      assert(0 <= a && a < MAXN);
      assert(0 <= b && b < MAXN);
      G[a].push_back(b);
      G[b].push_back(a);
      vis[make_pair(a, b)] = 0;
      vis[make_pair(b, a)] = 0;
      ordegs[a]++;
      ordegs[b]++;
    }

  path.insert(path.begin(), A);
  NN = 1;
  dfs(A, path.end());
  // Here we have a beautiful path A -> B


  int pre = -1;
  for (list<int>::iterator s = path.begin();
       s != path.end();
       ++s)
    {
      if (pre == -1)
        pre = *s;
      else
        {
          printf("%d %d\n", pre+1, (*s)+1);
          pre = *s;
        }
    }
  return 0;
}
