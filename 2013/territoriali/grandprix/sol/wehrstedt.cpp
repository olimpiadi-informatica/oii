/*
  Luca Wehrstedt

  Manteniamo due array (la permutazione "macchine-posizioni" e la sua inversa)
  e li teniamo aggiornati durante il corso della gara.
*/
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

const int MAXN = 30;

int n;
int m;

// Nota: usiamo indici che partono da 1

int pos[MAXN+1];  // pos[i] e' la posizione della macchina i
int car[MAXN+1];  // car[i] e' la macchina in posizione i

int main ()
{
    in >> n >> m;

    int a, b;

    for (int i = 1; i <= n; i += 1)
    {
        in >> a;
        car[i] = a;
        pos[a] = i;
    }

    for (int i = 0; i < m; i += 1)
    {
        in >> a >> b;
        swap(car[pos[a]], car[pos[b]]);
        swap(pos[a], pos[b]);
    }

    out << car[1] << endl;
}
