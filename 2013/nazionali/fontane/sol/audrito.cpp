/*
  Autore       Giorgio Audrito

  Descrizione  Scandisco gli intervalli del percorso, e vado a cercare quali stazioni ci stanno sopra.
               Solitamente è NlogN, ma può sconfinare in N^2 se il percorso ripassa molte volte per le stesse stazioni.
               In tal caso, si potrebbe mantenere NlogN implementando una struttura minimum-range-query per ogni
               serie di stazioni allineate.
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 102400
#define MAXM 102400

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

pair<int,int> StazX[MAXM];
pair<int,int> StazY[MAXM];
int Percorso[MAXN+1][2];
int N, M;

void leggi()
{
  int x, y;

  for (int i=0; i<=N; i++)
    in >> Percorso[i][0] >> Percorso[i][1];
  for (int i=0; i<M; i++)
    {
      in >> x >> y;
      StazX[i].first  = StazY[i].second = x;
      StazX[i].second = StazY[i].first  = y;
    }
  sort( StazX, StazX + M );
  sort( StazY, StazY + M );
}

int seguipercorso()
{
  pair<int,int> *up, *lo;
  int T = 0, taniche = 0, pos;

  for (int i=0; i<N; i++)
    {
      if ( Percorso[i][0] == Percorso[i+1][0] )
        {
          up = upper_bound( StazX, StazX + M, make_pair( Percorso[i][0], max(Percorso[i][1], Percorso[i+1][1]) ) );
          lo = lower_bound( StazX, StazX + M, make_pair( Percorso[i][0], min(Percorso[i][1], Percorso[i+1][1]) ) );
          pos = Percorso[i][1];
          if ( Percorso[i][1] < Percorso[i+1][1] || lo >= up )
            {
              for (; lo<up; lo++) // queste sono le stazioni che incontro, nell'ordine
                {
                  taniche += abs(lo->second-pos);
                  pos = lo->second;
                  T = max(T, taniche);
                  taniche = 0;
                }
            }
          else
            {
              for (up--; up>=lo; up--) // queste sono le stazioni che incontro, nell'ordine
                {
                  taniche += abs(up->second-pos);
                  pos = up->second;
                  T = max(T, taniche);
                  taniche = 0;
                }
            }
          taniche += abs(Percorso[i+1][1]-pos);
        }
      else
        {
          up = upper_bound( StazY, StazY + M, make_pair( Percorso[i][1], max(Percorso[i][0], Percorso[i+1][0]) ) );
          lo = lower_bound( StazY, StazY + M, make_pair( Percorso[i][1], min(Percorso[i][0], Percorso[i+1][0]) ) );
          pos = Percorso[i][0];
          if ( Percorso[i][0] < Percorso[i+1][0] || lo >= up )
            {
              for (; lo<up; lo++) // queste sono le stazioni che incontro, nell'ordine
                {
                  taniche += abs(lo->second-pos);
                  pos = lo->second;
                  T = max(T, taniche);
                  taniche = 0;
                }
            }
          else
            {
              for (up--; up>=lo; up--) // queste sono le stazioni che incontro, nell'ordine
                {
                  taniche += abs(up->second-pos);
                  pos = up->second;
                  T = max(T, taniche);
                  taniche = 0;
                }
            }
          taniche += abs(Percorso[i+1][0]-pos);
        }
    }
  T = max(T, taniche);
  return (T > 100) ? T - 100 : 0;
}

int main(void)
{
  in >> N >> M;
  assert(0 <= N && N <= MAXN);
  assert(0 <= M && M <= MAXM);

  leggi();
  out << seguipercorso() << endl;

  return 0;
}
