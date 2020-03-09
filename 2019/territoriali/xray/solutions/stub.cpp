#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

const int MAXN = 1000000;

int compute(int N, int vect[MAXN + 1]) {
  // Inserisci qui la tua soluzione

  // Ritorna 42 come soluzione
  return 42;
}

// Questa funzione legge l'input di un tescase,
// lo scrive nella variabile N e nel vettore vec
// poi chiama la funzione compute e scrive la risposta da essa calcolata
void solve(int t) {
  int N;
  cin >> N;

  assert(N >= 1);
  assert(N <= MAXN);

  // Questa e' il vettore che contiene i dosaggi delle radiazioni
  // Con indici nell'intervallo 1..N
  int vec[MAXN + 2] = {0};
  for (int i = 1; i <= N; i++) {
    cin >> vec[i];
  }

  cout << "Case #" << t << ": " << compute(N, vec) << endl;
}

int main() {
  // Decommenta queste righe per leggere e scrivere da file
  // ifstream in("input.txt");
  // cin.rdbuf(in.rdbuf());
  // ofstream out("output.txt");
  // cout.rdbuf(out.rdbuf());

  // T e' il numero dei casi di test
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) { // Per ogni caso di test t..
    solve(t);
  }
}
