/**
 * Descrizione: Greedy che usa lo stesso irrigatore per due semi solo se
 * l'estensione dell'intervallo costa meno dell'aggiunta di un nuovo irrigatore.
 * Autore: Edoardo Morassutto
 * Complessità: O(N)
 */
#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

void posiziona(int D, int T);

void budget(int B);

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P) {
  std::sort(X.begin(), X.end());
  std::vector<int> W(N), T(N);

  int k = 0;
  int start = 0;
  int end = 0;
  for (int i = 1; i < N; i++) {
    int new_end = i;
    ll prev_cost = (X[end] - X[start] + 10) / 2 + 5;
    ll new_cost = (X[new_end] - X[start] + 10) / 2 + 5;
    // estendere l'intervallo costa meno di aggiungere un irrigatore
    if (new_cost <= prev_cost + C + 10) {
      end = new_end;
      // estendere l'intervallo costa di più
    } else {
      W[k] = (X[start] + X[end]) / 2;
      T[k] = (X[end] - X[start] + 10) / 2 + 5;
      start = i;
      end = i;
      k++;
    }
  }
  W[k] = (X[start] + X[end]) / 2;
  T[k] = (X[end] - X[start] + 10) / 2 + 5;
  k++;


    int out = 0;
    for(int i=0; i<k; i++) {
      out += C + T[i];
      posiziona(W[i], T[i]);
    }
    budget(out);
}
