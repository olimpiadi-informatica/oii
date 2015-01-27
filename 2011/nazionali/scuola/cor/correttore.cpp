/*
  Stefano Maggiolo
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void ex( const char *msg, float res )
{
  if( msg ) {
    fprintf( stderr, "%s ", msg );
  }
  printf( "%f\n", res );
  exit( 0 );
}

void
check_fine_file(ifstream &fout)
{
  int x;
  fout >> x;
  if (!!fout)
    {
      ex("Output malformato", 0.0f);
      exit(0);
    }
}

const int MAXN = 2100;

int N, P;

int e[MAXN]; // e[x] == 1 <=> eroe x e` stato usato nella riga
int c[MAXN]; // c[x] == 1 <=> cattivo x e` stato usato nella riga
int C[MAXN][MAXN]; //C[x][y] == 1 <=> x ha combattuto con y

void
correggi1(int N, ifstream &fout)
{
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
        {
          e[j] = c[j] = 0;
        }
      for (int j = 0; j < N; j++)
        {
          int x, y;
          fout >> x;
          if (!fout)
            {
              ex("Output malformato", 0.0f);
              exit(0);
            }
          fout >> y;
          if (!fout)
            {
              ex("Output malformato", 0.0f);
              exit(0);
            }
          if (x < 1 || x > N || y < 1 || y > N || e[x-1] != 0 || c[y-1] != 0)
            {
              ex("Output semanticamente errato", 0.0f);
              exit(0);
            }
          e[x-1] = 1;
          c[y-1] = 1;

          if (C[x-1][y-1] == 1)
            {
              ex("Output errato", 0.0f);
              exit(0);
            }
          C[x-1][y-1] = 1;
        }
    }
  // Dato che il numero e` giusto e non ci sono duplicati, non c'e`
  // bisogno di controllare che tutti abbiano combattuto con tutti.
  check_fine_file(fout);
  ex("Output corretto", 1.0f);
}

void
correggi2(int N, ifstream &fout)
{
  for (int i = 0; i < N-1; i++)
    {
      for (int j = 0; j < N; j++)
        {
          e[j] = 0;
        }
      for (int j = 0; j < N/2; j++)
        {
          int x, y;
          fout >> x;
          if (!fout)
            {
              ex("Output malformato", 0.0f);
              exit(0);
            }
          fout >> y;
          if (!fout)
            {
              ex("Output malformato", 0.0f);
              exit(0);
            }
          if (x < 1 || x > N || y < 1 || y > N || e[x-1] != 0 || e[y-1] != 0 || x == y)
            {
              ex("Output semanticamente errato", 0.0f);
              exit(0);
            }
          e[x-1] = 1;
          c[y-1] = 1;

          if (C[x-1][y-1] == 1)
            {
              ex("Output errato", 0.0f);
              exit(0);
            }
          C[x-1][y-1] = C[y-1][x-1] = 1;
        }
    }
  // Dato che il numero e` giusto e non ci sono duplicati, non c'e`
  // bisogno di controllare che tutti abbiano combattuto con tutti.
  check_fine_file(fout);
  ex("Output corretto", 1.0f);
}

int main( int argc, char *argv[] )
{
  if( argc < 4 ) {
    cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << endl;
    return 1;
  }

  ifstream fin(argv[1]);
  ifstream fcor(argv[2]);
  ifstream fout(argv[3]);

  if( !fin ) {
    cerr << "Impossibile aprire il file di input " << argv[1] << "." << endl;
    return 1;
  }
  if( !fout ) {
    ex( "Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0 );
  }

  fin >> N;
  fin >> P;

  if (P == 1)
    correggi1(N, fout);
  else if (P == 2)
    correggi2(N, fout);
  else
    {
      cerr << "Valore di P " << P << " non corretto.";
      return 1;
    }

  return 0;
}

