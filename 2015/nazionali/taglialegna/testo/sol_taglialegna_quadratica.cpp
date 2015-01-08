#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <cassert>

#define MAXN 2000001

using namespace std;

void Abbatti(int, int);

int lep[MAXN];  // Fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // Fissato i, rep[i] contiene l'indice dell'albero più a destra
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

		// Secondo caso: abbatti a sinistra un albero alla destra di i che, nella caduta, abbatta anche i
		for (int j = i; j < N; j++) {
			if (lep[j] <= i) { // Controlla che l'albero j abbatta i cadendo a sinistra
				// Valuta se tagliando l'albero j troviamo una soluzione migliore di quella che conosciamo
				if (risolvi(j + 1).numero_tagli + 1 < risposta.numero_tagli) {
					risposta.numero_tagli = risolvi(j + 1).numero_tagli + 1;
					risposta.primo_albero = j;
					risposta.direzione = SINISTRA;
				}
			}
		}
	}

	// Ora che abbiamo calcolato la risposta per il dato i, memorizziamola in memo e aggiorniamo calcolato[i]
	calcolato[i] = true;
	memo[i] = risposta;

	return risposta;
}

// ricostruisci_tagli(i) si occupa di tagliare, attraverso opportune chiamate alla funzione Abbatti, il
// minimo numero di alberi affinchè tutti gli alberi da i a N-1 inclusi risultino abbattuti alla fine del
// processo. Riusa internamente le informazioni calcolate dalla funzione risolvi illustrata poco prima
void ricostruisci_tagli(int i) {
	if (i == N)
		return;

	int primo_albero = risolvi(i).primo_albero;
	direzione_t direzione = risolvi(i).direzione;

	Abbatti(primo_albero, direzione);

	if (direzione == SINISTRA)
		ricostruisci_tagli(primo_albero + 1);
	else
		ricostruisci_tagli(rep[i] + 1);
}

void Pianifica(int N, int H[]) {
	::N = N;

	// Costruzione di lep
	for (int i = 0; i < N; i++) {
		lep[i] = i;
		for (int j = i; j > i - H[i] && j >= 0; j--)
			lep[i] = min(lep[i], lep[j]);
	}

	// Costruzione di rep
	for (int i = N - 1; i >= 0; i--) {
		rep[i] = i;
		for (int j = i; j < i + H[i] && j < N; j++)
			rep[i] = max(rep[i], rep[j]);
	}

	// Forza il calcolo di risolvi(i) per ogni i senza eccedere i limiti dello stack
	for (int i = N - 1; i >= 0; i--)
		risolvi(i);

	ricostruisci_tagli(0);
}

