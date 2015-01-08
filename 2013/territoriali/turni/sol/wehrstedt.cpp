/*
  Luca Wehrstedt

  L'idea e' di considerare tutte le guardie che sono disponibili il primo
  giorno. Tra di esse scegliamo quella che copre l'intervallo piu' lungo
  (i.e. di lunghezza massima). Supponiamo che il suo ultimo giorno sia l.
  Consideriamo tutte le guardie che sono disponibili il giorno l+1.
  Scegliamo quella che copre l'intervallo piu' lungo. Supponiamo che il
  suo ultimo giorno sia m. Procediamo cosi' fino a coprire tutti i giorni.
*/
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int n;
int k;

vector< pair<int,int> > turni;

void leggi ()
{
    in >> k >> n;

    pair<int,int> p;
    for (int i = 0; i < n; i += 1)
    {
        in >> p.first >> p.second;
        turni.push_back(p);
    }
}

void elabora ()
{
    sort(turni.begin(), turni.end());

    int result = 0;
    int cur_day = 0;
    int max_day = -1;

    for (int i = 0; i < n; i += 1)
    {
        if (turni[i].first > cur_day)
        {
            cur_day = max_day + 1;
            result += 1;
        }
        max_day = max(max_day, turni[i].second);
    }

    if (cur_day < k)
    {
        result += 1;
    }

    out << result << endl;
}

int main ()
{
    leggi();
    elabora();
}
