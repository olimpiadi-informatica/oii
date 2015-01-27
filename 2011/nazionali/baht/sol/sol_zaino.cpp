/*
  Giorgio Audrito
  Matteo Boscariol

  Soluzione subottima.
  Per ogni macchina <P, mantiene un vettore representable() delle somme possibili
  (analogamente allo zaino). Una volta compilato con tutte le monete, esamina
  tutte le somme e trova la minima non possibile.
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXP = 1000;
const int MAXN = 10000;
const int MAXV = 1 << 20;
const int MAXSUM = ((unsigned int)1 << 31) - 1;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int P, N, sol;
int valori[MAXN];
vector<bool> representable(1);

int main(void)
{
  in >> P;
  assert(1 <= P && P <= MAXP);
  for (int p = 0; p < P; p++)
    {
      in >> N;
      representable.resize(1);
      representable[0]=true;
      assert(1 <= N && N <= MAXN);

      for (int n = 0; n < N; n++)
        {
          in >> valori[n];
          assert(1 <= valori[n] && valori[n] <= MAXV);

          for (int value = representable.size() - 1; value >= 0; value--)
	    if( representable[value] )
	      {
		if( value+valori[n]>=representable.size() ) representable.resize(value+valori[n]+1,false);
		representable[value + valori[n]]=true;
	      }
        }

      for (sol=1; sol < representable.size() && representable[sol]==true;  sol++);
      out << sol << endl;
    }
  return 0;
}
