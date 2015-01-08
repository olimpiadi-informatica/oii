/*
  Stefano Maggiolo, 24/03/2012

  Assunzione: impossibile stampa -1
*/

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

const int MAXN = 50;
const int MAXK = 50;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N, K;
int start[MAXN+10];
int _end[MAXN+10];
int u[MAXN+10];
int End;

void next(int Start)
{
  int bi = -1;
  for (int i = 0; i < N; i++)
    if (!u[i] && start[i] <= Start && (bi == -1 || _end[i] > _end[bi]))
      bi = i;
  if (bi == -1)
    End = -1;
  else
    {
      End = _end[bi];
      u[bi] = 1;
    }
}

int
main(void)
{
  in >> K >> N;
  assert(1 <= K && K <= MAXK);
  assert(1 <= N && N <= MAXN);
  for (int i = 0; i < N; i++)
    {
      in >> start[i] >> _end[i];
      assert(0 <= start[i] && start[i] <= _end[i] && _end[i] < K);
    }
  End = -1;
  int res = 0;
  do
    {
      next(End+1);
      ++res;
    } while (End < K-1 && End != -1);
  if (End == -1)
    res = -1;
  out << res << endl;
  return 0;
}
