// migliore(i) ritorna l'albero j appartenente alla catena di abbattitori di i per cui
// è minima la quantità risolvi(j + 1).numero_tagli
int migliore(int i) {
	int risposta = i;

	// Se i ammette un abbattitore, confrontiamo l'albero i, col migliore albero della catena
	// di abbattitori dell'abbattitore di i
	if (abbattitore[i] != INF) {
		// j contiene il migliore albero della catena di abbattitori dell'abbattitore di i
		int j = migliore(abbattitore[i]);

		// Confrontiamo l'albero j con l'albero i
		if (risolvi(j + 1).numero_tagli < risolvi(i + 1).numero_tagli)
			risposta = j;
	}

	return risposta;
}
