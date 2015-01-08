#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>

using namespace std;

const int MAXN = 2000002;
const int INF = numeric_limits<int>::max();
int *h;
int N;

struct return_t {
	int trees, first_tree;
	bool direction; // false = sinistra, true = destra

	return_t(): trees(INF) {}
	return_t(int trees, int first_tree, bool direction): trees(trees), first_tree(first_tree), direction(direction) {}

	bool operator< (const return_t& o) const {
		return trees < o.trees;
	}
};

return_t memo[MAXN];
int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i

void Abbatti(int, int);

return_t risolvi(int l) { // calcola la soluzione dell'intervallo [l, N - 1]

	if (memo[l].trees != INF)
		return memo[l];

	return_t ans;

	// Primo caso: butto l a destra
	int j = rep[l] + 1;

	int test = 1;
	if (j < N)
		test += risolvi(j).trees;

	ans.trees = test;
	ans.first_tree = l;
	ans.direction = true;

	// Secondo caso: abbatto a sinistra un albero che abbatte l nella caduta

	j = -1;

	for (int i = l + 1; i < N; i++) {
		// controllo se l'albero i butta giu' l
		if (lep[i] <= l) {

			if (i < N - 1) {
				return_t x = risolvi(i + 1);

				if (x.trees + 1 < ans.trees) {
					ans.trees = x.trees + 1;
					ans.direction = false;
					ans.first_tree = i;
				}
			} else {
				ans.trees = 1;
				ans.direction = false;
				ans.first_tree = N - 1;
			}
		}
	}

	return memo[l] = ans;
}

void ricostruisci(int l) { // ritorna la soluzione su [l, N - 1]

	int i = memo[l].first_tree;
	bool dir = memo[l].direction;

	Abbatti(i, dir);

	if (dir == false) { // sinistra
		if (i < N - 1)
			ricostruisci(i + 1);
	} else { // destra
		if (rep[i] < N - 1)
			ricostruisci(rep[i] + 1);
	}
}

void Pianifica(int n, int H[]) {
	h = H;
	N = n;

	for (int i = 0; i < N; i++) {
		int accumula = h[i] - 1;
		for (lep[i] = i - 1; lep[i] >= 0 && accumula; lep[i]--)
			accumula = max(accumula - 1, h[lep[i]] - 1);
		++lep[i];

		accumula = h[i] - 1;
		for (rep[i] = i + 1; rep[i] < N && accumula; rep[i]++)
			accumula = max(accumula - 1, h[rep[i]] - 1);
		--rep[i];
	}

	risolvi(0);

	ricostruisci(0);
}
