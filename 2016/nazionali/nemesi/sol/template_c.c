void nuovo_gruppo();

void aggiungi(int bambino);

void smista(int N, int nemico[]) {
	int i;
	for (i = 0; i < N; i++) {
		nuovo_gruppo();
		aggiungi(i);
	}
    return;
}

