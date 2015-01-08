#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 20000;

int N, T, Tcor;
int H[MAXN], C[MAXN];

void ex(const char *msg, float res) {
  cerr << msg << endl;
  cout << res << endl;
  
  exit(0);
}

int main(int argc, char *argv[]) {
  if (argc < 4)
    return 1;
		
  ifstream fin(argv[1]);  // input
  ifstream fcor(argv[2]); // output corretto
  ifstream fout(argv[3]); // da controllare

  fin >> N;
  if (N >= MAXN)
    ex("Non ho voglia di correggere questa roba", 0.5);
  for (int i=0; i<N; i++)
    fin >> H[i];

  int idx, dir;
  while (fcor >> idx >> dir)
    Tcor++;

  int x, y;
  while (fout >> idx >> dir) {
    T++;
    if (dir < 0 or dir > 1 or idx < 0 or idx >= N)
      ex("Soluzione malformata", 0.0);
    if (C[idx] == 1)
      ex("Soluzione errata: abbattimento di albero già caduto", 0.0);
    if (dir == 0) dir = -1;
    y = idx+dir*H[idx];
    for (x=idx; dir*x<dir*y and x>=0 and x<N; x+=dir) {
      if (C[x] == 0) y = dir*y > dir*x+H[x] ? y : x+dir*H[x];
      C[x] = 1;
    }
  }

  for (int i=0; i<N; i++)
    if (C[i] == 0)
      ex("Soluzione errata: rimasti alberi non caduti", 0.0);

  if (Tcor < T)
    ex("Soluzione subottima", 0.0);

  if (Tcor > T)
    ex("Soluzione prematurata come se fosse antani", 0.0);
	
  ex("Soluzione corretta", 1.0);
	
  return 0;
}
