#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <cassert>

using namespace std;

void Abbatti(int, int);

const int MAXN = 2000000;
int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i
int memo[MAXN];
int first_tree[MAXN];
bool direzione[MAXN];
int n_candidati;
int candidati[MAXN];
int min_candidati[MAXN];

void Pianifica(int N, int H[]) {
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

	int j, test;
	for (int i = 0; i < N; i++) {
		// Primo caso: butto i a sinistra
		j = lep[i] - 1;

		test = 1;
		if (j >= 0)
			test += memo[j];
		
		memo[i] = test;
		first_tree[i] = i;
		direzione[i] = false;

		// Secondo caso: abbatto a destra un albero che abbatte i nella caduta
		while (n_candidati && rep[*(candidati + n_candidati - 1)] < i)
			--n_candidati;

		if (n_candidati) {
			j = min_candidati[n_candidati - 1] - 1;

			test = 1;
			if (j >= 0)
				test += memo[j];

			if (test < memo[i]) {
				memo[i] = test;
				first_tree[i] = j + 1;
				direzione[i] = true;
			}
		}

		j = i;
		if (n_candidati) {
			if (
				min_candidati[n_candidati - 1] == 0 ||
				memo[min_candidati[n_candidati - 1] - 1] < memo[i - 1]
			) {
				j = min_candidati[n_candidati - 1];
			}
		}

		++n_candidati;
		candidati[n_candidati - 1] = i;
		min_candidati[n_candidati - 1] = j;
	}

	// Ricostruisci la soluzione
	int i = N - 1;
	while (i >= 0) {
		Abbatti(first_tree[i], direzione[i]);
		
		if (direzione[i] == false) // A sinistra
			i = lep[i] - 1;
		else
			i = first_tree[i] - 1;
	}
}
