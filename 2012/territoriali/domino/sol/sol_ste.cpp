/*
  Stefano Maggiolo (02/04/2011)
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int MAXN = 10;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N;
vector< pair< int, int > > tessere;

int
conta(int prec)
{
  int i = 1;

  while (true)
    {
      if (i == N)
        break;
      else if (prec == tessere[i].first)
        {
          prec = tessere[i].second;
          ++i;
        }
      else if (prec == tessere[i].second)
        {
          prec = tessere[i].first;
          ++i;
        }
      else
        break;

    }
  return i;
}

int
main(void)
{
  in >> N;
  assert(2 <= N && N <= MAXN);
  for (int i = 0; i < N; i++)
    {
      int a, b;
      in >> a >> b;
      assert(0 <= a && a <= 6);
      assert(0 <= b && b <= 6);
      tessere.push_back(make_pair(a, b));
    }

  int sol = 1;

  sort(tessere.begin(), tessere.end());
  while (next_permutation(tessere.begin(), tessere.end()))
    {
      sol = max(sol, conta(tessere[0].first));
      sol = max(sol, conta(tessere[0].second));
    }

  out << sol << endl;
  return 0;
}

