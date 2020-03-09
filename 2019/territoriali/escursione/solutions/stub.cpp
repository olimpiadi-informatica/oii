#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAXH = 100;
const int MAXW = 100;

int compute(int H, int W, int A[MAXH + 1][MAXW + 1]) {
  // Inserisci qui la tua soluzione

  // Ritorna 42 come soluzione
  return 42;
}

// Questa funzione legge l'input di un tescase,
// lo scrive sulla matrice A
// poi chiama la funzione compute e scrive la risposta da essa calcolata
void solve(int t) {
  int H, W;
  cin >> H >> W;

  assert(H >= 1 && W >= 1);
  assert(H <= MAXH && W <= MAXW);

  // Questa e' la matrice che contiene la mappa
  // Ha indici nell'intervallo 1..H e 1..W
  int A[MAXH + 1][MAXW + 1] = {0};

  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      cin >> A[i][j];
    }
  }

  cout << "Case #" << t << ": " << compute(H, W, A) << endl;
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
