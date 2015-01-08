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

		// Secondo caso: abbatti a sinistra migliore[i]
		int j = migliore(i);
		if (risolvi(j + 1).numero_tagli + 1 < risposta.numero_tagli) {
			risposta.numero_tagli = risolvi(j + 1).numero_tagli + 1;
			risposta.primo_albero = j;
			risposta.direzione = SINISTRA;
		}
	}

	return risposta;
}