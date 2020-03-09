/**
 *  Soluzione test di collimatore
 *
 *  Costo di questa soluzione: quadratica.
 *
 *  Descrizione: utilizzare l'intervallo totale (quello da estrema sinistra ad
estrema destre) fino all'altezza del minimo valore (questo costa 1 se il minimo
e` maggiore di 0, e costa 0 altrimenti). Poi il problema si spezza dove il
livello dell'acqua ha raggiunto il minimo. Posso pertanto procedere
ricorsivamente. Alle chiamate ricorsive passo gli estremi del sottointervallo ed
il livello gia` raggiunto dall'acqua.
 *
 */

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000;

int ric(int left, int right, int water, int vec[MAXN + 2]) {
  if (right < left)
    return 0;
  int my_cost = 0;
  int pos_min = left;
  for (int i = left + 1; i <= right; i++)
    if (vec[i] < vec[pos_min])
      pos_min = i;
  assert(vec[pos_min] >= water);
  if (vec[pos_min] > water) {
    my_cost = vec[pos_min] - water;
    water = vec[pos_min];
  }
  my_cost += ric(left, pos_min - 1, water, vec);
  my_cost += ric(pos_min + 1, right, water, vec);
  return my_cost;
}

int compute(int N, int vec[MAXN + 2]) { return ric(1, N, 0, vec); }

void solve(int t) {
  int N;
  cin >> N;
  int vec[MAXN + 2];

  vec[0] = vec[N + 1] = 0;
  for (int i = 1; i <= N; i++) {
    cin >> vec[i];
  }

  cout << "Case #" << t << ": " << compute(N, vec) << endl;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    solve(t);
  }
}
