/*
  Stefano Maggiolo
*/

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

const int MAXN = 1<<30;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N;

int
main(void)
{
  int sol = 0;
  in >> N;
  assert(1 <= N && N <= MAXN);
  for (int i = 0; i <= 30; i++)
    sol += !!((1<<i) & N);
  out << sol << endl;
  return 0;
}

