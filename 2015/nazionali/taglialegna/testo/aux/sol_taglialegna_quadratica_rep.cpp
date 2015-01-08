// Costruzione di rep
for (int i = N - 1; i >= 0; i--) {
	rep[i] = i;
	for (int j = i; j < i + H[i] && j < N; j++)
		rep[i] = max(rep[i], rep[j]);
}