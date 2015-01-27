/*
  Stefano Maggiolo
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <set>

using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;

set<pair<int, int> > edges;

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

int N, M, K;

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

  fin >> N >> M;
  assert(1 <= M && M <= MAXM);
  assert(1 <= N && N <= MAXN);
  for (int m = 0; m < M; m++)
    {
      int i, j, c;
      fin >> i >> j >> c;
      assert(1 <= i && i <= N);
      assert(1 <= j && j <= N);
      assert(c == 0 || c == 1);
      if (c == 1)
        {
          edges.insert(make_pair(i, j));
          edges.insert(make_pair(j, i));
        }
    }

  fout >> K;
  if (!fout)
    ex("Output malformato.", 0.0f);
  int x, prec, first;
  fout >> x;
  if (!fout)
    ex("Output malformato.", 0.0f);
  prec = first = x;
  for (int i = 1; i < K; i++)
    {
      set<pair<int, int> >::iterator j;
      fout >> x;
      if (!fout)
        ex("Output malformato.", 0.0f);
      if (edges.find(make_pair(x, prec)) == edges.end())
        ex("Risposta errata.", 0.0f);
      prec = x;
    }
  if (edges.find(make_pair(x, first)) == edges.end())
    ex("Risposta errata.", 0.0f);
  check_fine_file(fout);
  ex("Risposta corretta.", 1.0f);
  return 0;
}

