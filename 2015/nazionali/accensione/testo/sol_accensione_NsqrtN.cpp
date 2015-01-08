void Accendi(int N, int acceso[], int pulsante[]) {
	for (int i = N; i >= 1; i--) {
		// Se il computer i è spento allora premiqmo il pulsante i,
		// e cambiamo lo stato dei computer di conseguenza
		if (!acceso[i]) {
			pulsante[i] = 1;

			// Cerchiamo tutti i j che dividono i, ma solo
			// fino a j <= sqrt(i)
			for (int j = 1; j * j <= i; j++) {

				// Se j è un divisore di i, allora anche i/j è un divisore di i
				if (i % j == 0) {
					// Cambia lo stato del computer j
					acceso[j] ^= 1;

					// Cambia lo stato del computer i/j, ma solo se questo non
					// coincide con j. Questo è per evitare ad esempio il caso
					// i = 4, j = 2, in cui altrimenti lo stato del computer 2
					// verrebbe cambiato due volte invece di una sola
					if (j * j != i)
						acceso[i/j] ^= 1;
				}
			}
		}
	}
}