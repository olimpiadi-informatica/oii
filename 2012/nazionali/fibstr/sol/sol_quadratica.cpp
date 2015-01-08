/*
Giovanni Mascellani <mascellani@poisson.phc.unipi.it>

Soluzione per fibstr

Quadratica naive: ad ogni posizione cerca di costruire una stringa di
Fibonacci più lunga possibile che parte da quella posizione.

Per quanto questa soluzione sia naive, in effetti sembra molto più
veloce della dinamica di Giove su tutti gli input provati (anche di dieci
volte o di più). Probabilmente si può dare una stima sul numero di
stringhe di Fibonacci che sono sottostringhe di un'altra stringa di
Fibonacci che permetta di ammortizzare un ordine di grandezza, per cui
questa soluzione diventi lineare. Però non saprei elaborarla ora.

Probabilmente questa soluzione guadagna anche velocità beneficiando del
fatto che il confronto tra stringhe viene fatto con strcmp, che è
verosimilmente piuttosto ottimizzato. Inoltre utilizza molto meno
codice della soluzione di Giove.

*/

#ifdef EVAL
#define NDEBUG
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

using namespace std;

const int MAX_LEN = 1000000+1;

int len;
char str[MAX_LEN];


int main() {

#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d ", &len);
  gets(str);
  assert(strlen(str) == len);

  if (len == 1) {
    printf("1 1\n");
    return 0;
  }

  int best = 2, start = 0, stop = 2;
  for (int i = 0; i < len-1; i++) {
    // Controlla che i due simboli di partenza non siano uguali
    if (str[i] == str[i+1]) continue;
    int j = 2;
    int prev_j = 1;
    while ((i+j+prev_j <= len) && (strncmp(str+i, str+i+j, prev_j) == 0)) {
      int tmp = prev_j;
      prev_j = j;
      j += tmp;
    }
    if (j > best) {
      best = j;
      start = i;
      stop = i+j;
    }
  }

  printf("%d %d\n", start+1, stop);

  return 0;

}
