// Costruiamo lep e abbattitore in tempo lineare
for (int i = 0; i < N; i++) {
	lep[i] = i, abbattitore[i] = INF;
	while (lep[i] - 1 >= 0 && lep[i] - 1 > i - H[i]) {
		abbattitore[lep[i] - 1] = i;
		lep[i] = lep[lep[i] - 1];
	}
}