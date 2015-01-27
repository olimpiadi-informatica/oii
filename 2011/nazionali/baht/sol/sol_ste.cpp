/*
  Stefano Maggiolo, copiando il .py di Roberto Grossi.

  Sia V[0, ... N-1] la lista *ordinata* dei valori delle monete. Sia V_i = V[0, ..., i-1] il prefisso lungo i. Sia M_i il minimo valore non generabile con le monete in V_i. Allora:
  - la soluzione e` uguale a M_N;
  - M_i <= M_{i+1};
  - se V[0] != 1, allora M_N = 1, quindi assumiamo V[0] = 1;
  - M_i = M_{i+1} (cioè aggiungere un valore non aiuta) se e solo se M_i < V[i+1]: infatti, se non riuscivo a costruire M_i con V_i, e il nuovo valore è maggiore di M_i, di certo non riuscirò a usarlo per migliorare; viceversa, se il nuovo valore è minore o uguale di M_i, con V_i potevo costruire M_i - V_i (che è compreso tra 0 e M_i-1), quindi con V_{i+1} posso costruire M_i. 

  Giovanni: concordo con la soluzione di Stefano. In pratica, l'osservazione è che,
  scandendo la lista _ordinata_ delle monete, finché il minimo resto non restituibile
  può ancora crescere allora l'insieme dei resti restituibili è "connesso" (ossia è un
  intervallo del tipo [0, k]). Dunque è possibile tenere traccia di tale insieme
  memorizzando unicamente il numero k (che nel programma è la variabile sol).
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>

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

int P;
int N;
int SUM;
int valori[MAXN];

int
main(void)
{
  in >> P;
  assert(1 <= P && P <= MAXP);
  for (int p = 0; p < P; p++)
    {
      in >> N;
      SUM = 0;
      assert(1 <= N && N <= MAXN);
      for (int n = 0; n < N; n++)
        {
          in >> valori[n];
          assert(1 <= valori[n] && valori[n] <= MAXV);
          SUM += valori[n];
        }
      assert(1 <= SUM && SUM <= MAXSUM);
      sort(valori, valori+N);
      int sol = 0;
      for (int n = 0; n < N && sol + 1 >= valori[n]; n++)
             sol += valori[n];
      out << sol+1 << endl;
    }
  return 0;
}
