/*
  Stefano Maggiolo, 24/03/2012
*/

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

const int MAXN = 30;
const int MAXM = 100;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N, M;
int pos[MAXN+10];

int
main(void)
{
  in >> N >> M;
  assert(1 <= N && N <= MAXN);
  assert(1 <= M && M <= MAXM);
  for (int i = 0; i < N; i++)
    {
      int tmp;
      in >> tmp;
      assert(1 <= tmp && tmp <= N);
      pos[tmp-1] = i+1;
    }
  for (int i = 0; i < N; i++)
    assert(pos[i] != 0);
  for (int i = 0; i < M; i++)
    {
      int tmp1, tmp2;
      in >> tmp1 >> tmp2;
      assert(1 <= tmp1 && tmp1 <= N);
      assert(1 <= tmp2 && tmp2 <= N);
      assert(pos[tmp1-1] == pos[tmp2-1]+1);
      --pos[tmp1-1];
      ++pos[tmp2-1];
    }
  for (int i = 0; i < N; i++)
    if (pos[i] == 1)
      {
        out << (i+1) << endl;
        return 0;
      }
  assert(false);
  return 0;
}

