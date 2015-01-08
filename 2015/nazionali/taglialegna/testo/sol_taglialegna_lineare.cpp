#include <limits>

const int MAXN = 2000001;
const int INF = std::numeric_limits<int>::max();

enum direzione_t {SINISTRA, DESTRA};
struct info_t {
	int numero_tagli = INF;
	int primo_albero;
	direzione_t direzione;
};

int lep[MAXN];  // Fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // Fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i

info_t memo[MAXN];
int abbattitore[MAXN];
int migliore[MAXN];

void Abbatti(int, int);
void Pianifica(int N, int H[]) {
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

	memo[N].numero_tagli = 0;
	for (int i = N - 1; i >= 0; i--) {
		// Calcola migliore[i]
		migliore[i] = i;
		if (abbattitore[i] != INF) {
			int j = migliore[abbattitore[i]];
			if (memo[j + 1].numero_tagli < memo[i + 1].numero_tagli)
				migliore[i] = j;
		}
				
		// Primo caso: abbatti i a destra
		memo[i].numero_tagli = 1 + memo[rep[i] + 1].numero_tagli;
		memo[i].primo_albero = i;
		memo[i].direzione = DESTRA;
		
		// Secondo caso: abbatti a sinistra un albero alla destra di i che, nella caduta, abbatta anche i
		if (memo[migliore[i] + 1].numero_tagli + 1 < memo[i].numero_tagli) {
			memo[i].numero_tagli = memo[migliore[i] + 1].numero_tagli + 1;
			memo[i].primo_albero = migliore[i];
			memo[i].direzione = SINISTRA;
		}
	}

	// Ricostruiamo la soluzione
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