// Costruzione di lep
for (int i = 0; i < N; i++) {
	lep[i] = i;
	for (int j = i; j > i - H[i] && j >= 0; j--)
		lep[i] = min(lep[i], lep[j]);
}