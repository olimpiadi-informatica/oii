/*
  Autore      Giorgio Audrito

  Descrizione Soluzione lineare che legge i sorpassi dall'ultimo, ogni vettura sorpassata
              e' "eliminata" dalla gara (non puo' aver vinto), e vede chi rimane.
*/

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

#define MAX_N 1024
#define MAX_M 1024

int Inizio[MAX_N];
int Sorpassi[MAX_M][2];
int Candidati[MAX_N];
int N, M;

int
main(void)
{
  int i;

  in >> N >> M;
  for (i=0; i<N; i++) {
    in >> Inizio[i];
    Candidati[i+1] = 1;
  }
  for (i=0; i<M; i++) {
    in >> Sorpassi[i][0] >> Sorpassi[i][1];
  }
  for (i=M-1; i>=0; i--)
    if ( Candidati[Sorpassi[i][0]] ) {
      Candidati[Sorpassi[i][1]] = 0;
    }
  for (i=0; i<N; i++) if ( Candidati[Inizio[i]] ) break;
  out << Inizio[i] << endl;
  return 0;
}
