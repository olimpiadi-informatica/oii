/*
  Stefano Maggiolo (02/04/2011)
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

const int MAXM = 100;
const int MAXN = 100;
const int MAXK = 10;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int M, N, K;
string s;
map< pair< int, char >, int > tr;


int
main(void)
{
  in >> M >> N >> K;
  assert(2 <= M && M <= MAXM);
  assert(2 <= N && N <= MAXN);
  assert(2 <= K && K <= MAXK);

  for (int i = 0; i < K; ++i)
    {
      string a;
      in >> a;
      assert(a.size() == 1);
      s += a;
    }

  for (int i = 0; i < M; ++i)
    {
      int a, b;
      string c;
      in >> a >> b >> c;
      assert(c.size() == 1);
      assert(1 <= a && a <= N);
      assert(1 <= b && b <= N);
      assert(tr.find(make_pair(a, c[0])) == tr.end());
      tr[make_pair(a, c[0])] = b;
    }

  int curr = 1;
  for (int i = 0; i < K; ++i)
    {
      assert(tr.find(make_pair(curr, s[i])) != tr.end());
      curr = tr.find(make_pair(curr, s[i]))->second;
    }

  out << curr << endl;
  return 0;
}

