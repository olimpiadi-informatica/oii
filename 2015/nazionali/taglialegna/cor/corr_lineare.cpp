#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 2000005;

int N, T, Tcor;
int H[MAXN], rep[MAXN], lep[MAXN], nxt[MAXN], prv[MAXN];

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
  for (int i=0; i<N; i++)
    fin >> H[i];

  int idx, dir;
  while (fcor >> idx >> dir)
    Tcor++;

  lep[0] = 0;
  for (int i = 1; i < N; i++) {
    int j = i-1;
    while (j >= 0 && i - j < H[i])
      j = lep[j] - 1;
    lep[i] = j + 1;
  }

  rep[N-1] = N-1;
  for (int i = N-2; i >= 0; i--) {
    int j = i + 1;
    while (j < N && j - i < H[i])
      j = rep[j] + 1;
    rep[i] = j - 1;
  }

  for (int i=0; i<N; i++)
    nxt[i] = -1;

  //cerr << "LEP:" << endl;
  //for (int i=0; i<N; i++)
  //cerr << lep[i] << "\t";
  //cerr << endl;

  int x, y;
  while (fout >> idx >> dir) {
    T++;
    if (dir < 0 or dir > 1 or idx < 0 or idx >= N)
      ex("Soluzione malformata", 0.0);
    if (nxt[idx] > -1)
      ex("Soluzione errata: abbattimento di albero già caduto", 0.0);
    if (dir == 0) {
      y = lep[idx];
      for (x=idx; x>=lep[idx];) {
	nxt[x] = idx;
	prv[x] = y;
	x--;
	while (nxt[x] > -1 and x >= 0) {
	  y = y < prv[x] ? y : prv[x];
	  x = prv[x] - 1;
	}
      }
      prv[idx] = y;
    }
    else {
      y = rep[idx];
      for (x=idx; x<=rep[idx];) {
	prv[x] = idx;
	nxt[x] = y;
	x++;
	while (nxt[x] > -1 and x < N) {
	  y = y > nxt[x] ? y : nxt[x];
	  x = nxt[x] + 1;
	}
      }
      nxt[idx] = y;
    }
  }

  for (int i=0; i<N; i++)
    if (nxt[i] == -1)
      ex("Soluzione errata: rimasti alberi non caduti", 0.0);

  if (Tcor < T)
    ex("Soluzione subottima", 0.0);

  if (Tcor > T)
    ex("Soluzione prematurata come se fosse antani", 0.0);
	
  ex("Soluzione corretta", 1.0);
	
  return 0;
}
