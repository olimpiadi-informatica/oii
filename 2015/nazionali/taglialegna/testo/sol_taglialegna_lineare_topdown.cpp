#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <cassert>

#define MAXN 2000001

using namespace std;

void Abbatti(int, int);

int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i

const int INF = numeric_limits<int>::max();

enum direzione_t {SINISTRA, DESTRA};

// Struttura info_t. I significati dei vari membri sono spiegati poco più sotto.
struct info_t {
	int numero_tagli = INF;
	int primo_albero;
	direzione_t direzione;
};

int N;
info_t memo[MAXN];  // Array della memoizzazione
bool calcolato[MAXN]; // calcolato[i] vale true se abbiamo già calcolato il valore di risolvi(i)
                      // altrimenti vale false
int abbattitore[MAXN];
int best[MAXN];

info_t risolvi(int);
int migliore(int i) {
	if (best[i] != -1)
		return best[i];

	// migliore[i] può solo essere i o migliore[abbattitore[i]]
	int risposta = i;

	if (abbattitore[i] != INF) {
		int j = migliore(abbattitore[i]);
	 	if (risolvi(j + 1).numero_tagli < risolvi(i + 1).numero_tagli)
			risposta = j;
	}

	return best[i] = risposta;
}

// risolvi(i) ritorna un oggetto info_t, che contiene
//   - numero_tagli: il minimo numero di tagli da effettuare per abbattere tutti gli alberi da
//                   i a N-1 inclusi.
//   - primo_albero: l'indice del primo albero da tagliare
//   - direzione:    la direzione della caduta del primo albero
info_t risolvi(int i) {
	info_t risposta;

	// Se abbiamo già calcolato la risposta, non c'è bisogno di ripetere tutto il lavoro
	if (calcolato[i])
		return memo[i];

	if (i == N) {
		// Se non ci sono alberi da tagliare, numero_tagli = 0
		risposta.numero_tagli = 0;
	} else {
		// Primo caso: abbatti i a destra
		risposta.numero_tagli = risolvi(rep[i] + 1).numero_tagli + 1;
		risposta.primo_albero = i;
		risposta.direzione = DESTRA;

		// Secondo caso: abbatti a sinistra migliore[i]
		int j = migliore(i);
		if (risolvi(j + 1).numero_tagli + 1 < risposta.numero_tagli) {
			risposta.numero_tagli = risolvi(j + 1).numero_tagli + 1;
			risposta.primo_albero = j;
			risposta.direzione = SINISTRA;
		}
	}

	// Ora che abbiamo calcolato la risposta per il dato i, memorizziamola in memo e aggiorniamo calcolato[i]
	calcolato[i] = true;
	memo[i] = risposta;

	return risposta;
}

void Pianifica(int N, int H[]) {
	::N = N;
	fill(best, best + N, -1);

	// Costruiamo rep in tempo lineare
	for (int i = N - 1; i >= 0; i--) {
		rep[i] = i;
		while (rep[i] + 1 < N && rep[i] + 1 < i + H[i])
			rep[i] = rep[rep[i] + 1];
	}

	// Costruiamo lep e abbattitore in tempo lineare
	for (int i = 0; i < N; i++) {
		lep[i] = i, abbattitore[i] = INF;
		while (lep[i] - 1 >= 0 && lep[i] - 1 > i - H[i]) {
			abbattitore[lep[i] - 1] = i;
			lep[i] = lep[lep[i] - 1];
		}
	}

	for (int i = N - 1; i >= 0; i--)
		risolvi(i);

	// Ricostruisco la soluzione
	int i = 0;
	while (i < N)  {
		int primo_albero = memo[i].primo_albero;
		direzione_t direzione = memo[i].direzione;

		Abbatti(primo_albero, direzione);
		
		if (direzione == SINISTRA)
			i = primo_albero + 1;
		else
			i = rep[i] + 1;
	}
}

/*void Abbatti(int a, int b) {
	cerr << a << " " << b << endl;
}

int h[] = {2, 3, 2, 1, 4, 2, 1};
int main() {
	Pianifica(7, h);

	return 0;
}*/