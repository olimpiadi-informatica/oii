/*
  Stefano Maggiolo (02/04/2011)
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 1000;
const int MAXDISL = 100;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif


int N;
map< int, int > freq;


int
main(void)
{
  int sol = -1;
  int sol_val = 0;
  in >> N;
  assert(2 <= N && N <= MAXN);
  freq[5000] = 1;
  for (int i = 0, curr = 5000; i < N; ++i)
    {
      int a;
      in >> a;
      assert(-MAXDISL <= a && a <= MAXDISL);
      curr += a;
      if (freq.find(curr) == freq.end())
        freq[curr] = 1;
      else
        ++freq[curr];
      if (freq[curr] > sol_val)
        {
          sol_val = freq[curr];
          sol = curr;
        }
    }
  out << sol << endl;
  return 0;
}

