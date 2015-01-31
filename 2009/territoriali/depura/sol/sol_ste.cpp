/*
 Stefano Maggiolo

 Soluzione che funziona in caso di assenza di grafi e univocita` di regole.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <cstdlib>

using namespace std;

const int MAXN = 1000;

int K,R;
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif

typedef map< int, vector<int> > REGOLE;
typedef map< int, bool > SOSTANZE;

SOSTANZE inserito;
REGOLE regola;

int
quanti_ne_servono_per(int u)
{
  // Entrato qui so gia` che u non e` gia` inserito.
  REGOLE::iterator U = regola.find(u);
  if (U == regola.end())
    {
      // Se non c'e` la regola, non puo` essere inserito.
      out << -1 << endl;
      exit(0);
    }
  else
    {
      // Altrimenti sommo quanti ne servono ai figli piu` uno.
      int somma = 1;
      for (vector<int>::iterator i = U->second.begin(); i != U->second.end(); ++i)
        // Mi occupo qui dei casi in qui *i e` gia` inserito.
        if (inserito.find(*i) == inserito.end())
          // Qui non mi preoccupo delle sostanze che non possono essere
          // inserite dato che se esco subito appena ne trovo una.
          somma += quanti_ne_servono_per(*i);
      inserito[u] = true;
      return somma;
    }
}

int
main(void)
{
  
  in >> K >> R;
  // Leggo le sostanze gia` presenti
  for (int i = 0; i < K; i++)
    {
      int u;
      in >> u;
      if (u == 1)
        {
          // Se P gia` presente, esco subito.
          out << 1;
          exit(0);
        }
      inserito[u] = true;
    }
  // Leggo le regole.
  for (int i = 0; i < R; i++)
    {
      int u, n;
      vector<int> tmp;
      in >> u >> n;
      for (int j = 0; j < n; j++)
        {
          int x;
          in >> x;
          tmp.push_back(x);
        }
      regola[u] = tmp;
    }
  // Computo...
  out << quanti_ne_servono_per(1) << endl;
  
  return 0;
}
