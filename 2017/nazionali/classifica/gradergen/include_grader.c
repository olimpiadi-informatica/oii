void make_calls(int* Q, char types[], int params[], int answers[]) {
    int cnt = 0;
	for (int i = 0; i < *Q; i++) {
		if (types[i] == 's') {
			supera(params[i]);
		}
		else if (types[i] == 'x') {
			squalifica(params[i]);
		}
		else if (types[i] == 'p') {
			answers[cnt++] = partecipante(params[i]);
		}
	}
    *Q = cnt;
}
