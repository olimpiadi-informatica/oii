/*
  Correttore di "disuguaglianze"
*/

#include <fstream>
#include <string>
#include <set>

#define STAMPA_DEBUG 1  // stampa informazioni aggiuntive oltre a 1 o 0
#define TRY_REVERSED 1  // accetta soluzioni che confondono ">" e "<"

const int MAXN = 100000;

int numeri[MAXN];

void ex(const int res, const char* const msg) {
  printf("%d\n", res);
#if STAMPA_DEBUG
  fputs(msg, stderr);
#endif
  exit(0);
}

int get_errori(std::string segni, int numeri[], int N) {
  int errori = 0;
  for (int i=0; i<N-1; i++) {
    switch (segni[i]) {
    case '<':
      errori += (numeri[i] >= numeri[i+1]) ? 1 : 0;
      break;
    case '>':
      errori += (numeri[i] <= numeri[i+1]) ? 1 : 0;
      break;
    default:
      fprintf(stderr, "C'e' qualcosa che non va: l'input non e' valido.\n");
      exit(1);
    }
  }
  return errori;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s <input> <output> <test_output>\n", argv[0]);
    exit(1);
  }

  std::ifstream input(argv[1]);  // Il file di input
  std::ifstream test(argv[3]);   // L'output prodotto dal contestant

  if (!input.is_open() || !test.is_open()) {
    fprintf(stderr, "Impossibile aprire alcuni file per la correzione.\n");
    exit(1);
  }

  int N;
  std::string segni;
  input >> N >> segni;

  std::set<int> numeri_usati;
  for (int i=0; i<N; i++) {
    if (test >> numeri[i]) {
      if (numeri[i] < 1 || numeri[i] > N) {
        ex(0, "Il programma ha stampato un valore non compreso in [1, N].\n");
      }
      if (numeri_usati.count(numeri[i])) {
        ex(0, "Il programma ha stampato due volte uno stesso numero.\n");
      }
      numeri_usati.insert(numeri[i]);
    } else {
      ex(0, "Il programma non ha stampato N interi come richiesto.\n");
    }
  }

  // Qui si controlla che lo stream "test" sia finito (ma noi siamo buoni e lasciamo correre)

  int errori = get_errori(segni, numeri, N);
#if TRY_REVERSED
  for (int i=0; i<N-1; i++) {
    segni[i] = (segni[i] == '<') ? '>' : '<';
  }
  errori = std::min(errori, get_errori(segni, numeri, N));
#endif

  if (errori == 0) {
    ex(1, "La soluzione rispetta tutte le disuguaglianze.\n");
  } else {
    ex(0, "La soluzione non rispetta tutte le disuguaglianze.\n");
  }
}
