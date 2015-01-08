const int INF = numeric_limits<int>::max();
enum direzione_t {SINISTRA, DESTRA};

// Struttura info_t. I significati dei vari membri sono spiegati poco più sotto.
struct info_t {
	int numero_tagli = INF;
	int primo_albero;
	direzione_t direzione;
};

// risolvi(i) ritorna un oggetto info_t, che contiene
//   - numero_tagli: il minimo numero di tagli da effettuare per abbattere tutti gli alberi da
//                   i a N-1 inclusi.
//   - primo_albero: l'indice del primo albero da tagliare
//   - direzione:    la direzione della caduta del primo albero
info_t risolvi(int i) {
	info_t risposta;

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

	return risposta;
}