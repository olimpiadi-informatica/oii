typedef enum {
	SOPRA = 0,
	DESTRA = 1,
	SOTTO = 2,
	SINISTRA = 3
} parete_t; // lato

typedef struct {
	parete_t lato;
	int posizione;
} foro_t; // posizione

void inizia(int N, int M) {
	// metti qui il codice per inizializzare quello che ti serve
}

void aggiungi(int r, int c, char diagonale) {
	// aggiungi uno specchio
}

foro_t calcola(foro_t ingresso) {
	// calcola il punto di uscita del raggio
	foro_t uscita;
	uscita.lato = SOPRA;
	uscita.posizione = ingresso.posizione + 1;
	return uscita;
}
