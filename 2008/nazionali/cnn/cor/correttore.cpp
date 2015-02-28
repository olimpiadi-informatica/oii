/* Correttore per CNN -- Alessio Orlandi
 * N.B. Vista l'ampia confusione che si fa,
 * il solutore prova a correggere sia la versione
 * data che la versione scambiando R con C.
 * Nel caso si voglia disabilitare questo comportamento
 * compilare con -DNO_FLIP
 */
using namespace std;

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

const int USE_X = 0;
const int USE_Y = 1;

const int MaxN = 10000;
const int MaxM = 1000;
int N, M, W;
int x[MaxN], y[MaxN];
int str[MaxN],ours[MaxN];


void ex(const char *msg, float res );

std::string trim(std::string& s,const std::string& drop = " \r\n\t")
{
 std::string r=s.erase(s.find_last_not_of(drop)+1);
 return r.erase(0,r.find_first_not_of(drop));
}


int test(int *mystr)
{
  int posX = 1, posY = 1, cost = 0;
  for(int i = 0; i < N; i++ )
    if ( mystr[i] == USE_X )
    {  cost += abs(posX - x[i]); posX = x[i]; }
    else
    {  cost += abs(posY - y[i]); posY = y[i]; }
  return cost;
}


int main( int argc, char *argv[] )
{
  if( argc < 4 ) {
    cerr << "Usage: " << argv[0] << " <input> <output with expected weight> <test output>" << endl;
    return 1;
  }

  ifstream fin(argv[1]);
  ifstream fw(argv[2]);
  ifstream fout(argv[3]);
  string s;


   if( !fin ) {
    cerr << "Impossibile aprire il file di input " << argv[1] << "." << endl;
    return 1;
   }
  if( !fout ) {
    ex( "Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0 );
   }
  if ( !fw ) { ex("Impossibile aprire l'output del solutore.", 0.0); }

  fin >> N >> M;
  for(int i = 0; i < N; i++ )
  {
    fin >> x[i] >> y[i];
    if ( !fw ) ex("Errore nel file di output del solutore!", 0.0);
    fw >> s;
    char c = trim(s)[0];
    ours[i] = (c == 'R' ? USE_X : USE_Y );
  }


  for(int i = 0; i < N; i++ )
  {
    if ( fout.eof() ) ex("File da controllare troppo corto.", 0.0);
    fout >> s;
    char c = trim(s)[0];

    if ( c == 'C' || c == 'c' )
       str[i] = USE_Y;
    else if ( c == 'R' ||  c == 'r' )
       str[i] = USE_X;
    else
       ex("Carattere fuori standard", 0.0);
  }

  W = test(ours);

  int hisWeight = test(str);
  if ( hisWeight == W ) ex( "Risposta corretta.", 1.0 );
  if ( hisWeight < W ) {
     cerr << "His weight: " << hisWeight << " vs ours: " << W << endl;
     ex("ERRORE NEL CORRETTORE!", 0.0);
  }

#ifndef NO_FLIP
  for(int i = 0; i < N; i++ )
     str[i] = (str[i] == USE_X ? USE_Y : USE_X );

  hisWeight = test(str);
  if ( hisWeight == W ) ex( "Risposta corretta (invertita)", 1.0 );
  if ( hisWeight < W ) ex("ERRORE NEL CORRETTORE!", 0.0);
#endif


  ex("Risposta errata.", 0.0);
}


void ex( const char *msg, float res )
{
  if( msg ) {
    fprintf( stderr, "[\x1b[1m\x1b[31m%s\x1b[m] ", msg );
  }
  printf( "%f\n", res );
  exit( 0 );
}
