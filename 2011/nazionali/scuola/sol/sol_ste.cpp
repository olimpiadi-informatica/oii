/*
  Stefano Maggiolo

  Per la prima prova, devo selezionare N permutazioni di N elementi
  che mi diano il risultato; la cosa piu` facile e` usare le
  permutazioni cicliche.

  Per la seconda prova, l'idea e` di far combattere i primi N/2 con i
  secondi N/2 in tutte le possibilita` usando ancora le permutazioni
  cicliche; dopodoche' posso fare la ricorsione avendo cura di
  appiccicare i combattimenti dei primi N/2 tra loro con quelli dei
  secondi N/2 tra loro. Potrei quindi salvare l'output della prima
  ricorsione in una matrice, ma invece preferisco evitare la
  ricorsione e incasinarmi con gli indici.
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 2100;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N, P, n;

void
risolvi1()
{
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
        {
          out << (j+1) << " " << (((i+j) % N) + 1) << " ";
        }
      out << endl;
    }
}

void
risolvi2()
{
  if (N == 2)
    {
      out << "1 2" << endl;
    }
  else
    {
      for (int m = 0; m < n; m++)
        {
          int scost = pow(2, m);
          int pezzi = N/scost/2;
          for (int i = 0; i < scost; i++)
            {
              for (int p = 0; p < pezzi; p++)
                {
                  int start = 2*scost*p;
                  for (int j = 0; j < scost; j++)
                    {
                      out << (start+j+1) << " " << (((i+j) % scost) + scost+start+1) << " ";
                    }
                }
              out << endl;
            }
        }
    }
}

int
main(void)
{
  in >> N >> P;
  assert(2 <= N && N <= MAXN);
  assert(P == 1 || P == 2);
  if (P == 1)
    risolvi1();
  else if (P == 2)
    {
      for (n = 1; pow(2, n) < N; n++);
      assert(pow(2, n) == N);
      risolvi2();
    }
  return 0;
}

