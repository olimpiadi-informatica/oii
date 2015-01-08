#include <iostream>

using namespace std;

void Abbatti(int, int);

const int MAXN = 2000005;
int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i

void f(int l, int r) {
	if (l >= r)
		return;

	int max_left = l, max_right = l;

	for (int i = l; i < r; i++)
		if (i - lep[i] > max_left - lep[max_left])
			max_left = i;
	for (int i = l; i < r; i++)
		if (rep[i] - i > rep[max_right] - max_right)
			max_right = i;

	if (max_left - lep[max_left] > rep[max_right] - max_right) {
		Abbatti(max_left, 0);
		f(l, lep[max_left]);
		f(max_left + 1, r);
	} else {
		Abbatti(max_right, 1);
		f(l, max_right);
		f(rep[max_right] + 1, r);
	}
}

void Pianifica(int N, int *H) {
	lep[0] = 0;
	for (int i = 1; i < N; i++) {
		int j = i-1;
		while (j >= 0 && i - j < H[i])
			j = lep[j] - 1;
		lep[i] = j + 1;
	}

	rep[N-1] = N-1;
	for (int i = N-2; i >= 0; i--) {
		int j = i + 1;
		while (j < N && j - i < H[i])
			j = rep[j] + 1;
		rep[i] = j - 1;
	}

	f(0, N);
}