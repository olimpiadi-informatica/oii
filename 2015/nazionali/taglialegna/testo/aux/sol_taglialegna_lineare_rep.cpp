// Costruiamo rep in tempo lineare
for (int i = N - 1; i >= 0; i--) {
	rep[i] = i;
	while (rep[i] + 1 < N && rep[i] + 1 < i + H[i])
		rep[i] = rep[rep[i] + 1];
}