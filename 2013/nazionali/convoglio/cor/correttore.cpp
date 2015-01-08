/*
  Autore
 */

// Assume file di input e file di output non malformati.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>

using namespace std;

ifstream *fin;
ifstream *fcor;
ifstream *fout;

void ex(const char *msg, float res)
{
  if(msg) {
    fprintf(stderr, "%s ", msg);
  }
  printf("%f\n", res);
  exit(0);
}

template <class T>
T safe_read(const T &lowerBound, const T &upperBound)
{
  // Legge in maniera sicura un tipo ordinato e controlla che stia in
  // [lowerBound, upperBound]
  T x;
  if (lowerBound > upperBound)
    {
      cerr << "safe_read chiamato con parametri errati: " << lowerBound << " " << upperBound << "\n";
      return 1;
    }
  *fout >> x;

  if (fout->fail())
    ex("Output malformato", 0.0f);
  if (x < lowerBound || x > upperBound)
    ex("Output invalido", 0.0f);
  return x;
}

void
check_fine_file()
{
  string x;

  if (fout->eof())
    return;

  *fout >> x;
  if (x != "" || !fout->eof())
    ex("Output malformato", 0.0f);
}

int N,M;
int cor_first_value;
int out_first_value;

vector<set<int> > edges;
vector<int> initial_match;
vector<int> alt_match;
vector<int> inv_alt_match;
bool distinct_match = false;

int main(int argc, char *argv[])
{
  if(argc < 4)
    {
      cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << endl;
      return 1;
    }

  fin = new ifstream(argv[1]);
  fcor = new ifstream(argv[2]);
  fout = new ifstream(argv[3]);

  if(fin->fail())
    {
      cerr << "Impossibile aprire il file di input " << argv[1] << "." << endl;
      return 1;
    }
  if(fcor->fail())
    {
      cerr << "Impossibile aprire il file di output corretto " << argv[2] << "." << endl;
      return 1;
    }
  if(fout->fail())
    ex("Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0);

  *fin >> N >> M;

  initial_match.resize(N);
  edges.resize(N);
  for(int i=0; i<M; i++) {
    int src, dst;
    *fin >> src >> dst;
    edges[src].insert(dst);
    if(i<N)
      initial_match[src] = dst;
  }

  *fcor >> cor_first_value;
  out_first_value = safe_read(-1, N-1);

  if(out_first_value == -1) {
    check_fine_file();
    if(cor_first_value != -1)
      ex("Nessun matching restituito.", 0.0f);
    else
      ex("Corretto.", 1.0f);
  }

  alt_match.resize(N, -1);
  inv_alt_match.resize(N, -1);
  for(int i=0;i<N;i++) {
    int src, dst;
    if(i==0)
      src = out_first_value;
    else
      src = safe_read(0, N-1);
    dst = safe_read(0, N-1);
    alt_match[src] = dst;
    inv_alt_match[dst] = src;
  }
  check_fine_file();

  for(int i=0;i<N;i++) {
    if(alt_match[i] == -1 || inv_alt_match[i] == -1)
      ex("Il matching non è biunivoco.", 0.0f);
    if(edges[i].find(alt_match[i]) == edges[i].end())
      ex("Mancano degli archi.", 0.0f);
    if(alt_match[i] != initial_match[i])
      distinct_match = true;
  }

  if(distinct_match){
    if(cor_first_value != -1)
       ex("Corretto.", 1.0f);
    else
       ex("Picchia Matteo.", 1.0f);
  }
  else
    ex("Il matching è lo stesso.", 0.0f);

  return 0;
}
