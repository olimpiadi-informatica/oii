/*
 Stefano Maggiolo

 Soluzione banale, N*K. Dovrebbe funzionare comunque in tutti i casi.
*/

#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100000;

int N, K, valori[MAXN+1];
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif

int
main(void)
{
  int massimo = 0;
  
  in >> K >> N;

  for (int i = 0; i < N; i++)
    {
      in >> valori[i];
      for (int j = max(i - K, 0); j < i; j++)
        if (massimo < valori[i] - valori[j])
          massimo = valori[i] - valori[j];
    }
  out << massimo << endl;
  return 0;
}
