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

	for (int l = N - 1; l >= 0; l--) {
		// Primo caso: butto l a destra
		int j = rep[l] + 1;

		int test = 1;
		if (j < N)
			test += memo[j].trees;

		memo[l].trees = test;
		memo[l].first_tree = l;
		memo[l].direction = true;

		// Secondo caso: abbatto a sinistra un albero che abbatte l nella caduta
		for (int i = l + 1; i < N; i++) {
			// controllo se l'albero i butta giu' l
			if (lep[i] <= l) {
				if (i < N - 1) {
					return_t x = memo[i + 1];

					if (x.trees + 1 < memo[l].trees) {
						memo[l].trees = x.trees + 1;
						memo[l].direction = false;
						memo[l].first_tree = i;
					}
				} else {
					memo[l].trees = 1;
					memo[l].direction = false;
					memo[l].first_tree = N - 1;
				}
			}
		}
	}

	int i = 0;
	while (i < N) {
		bool dir = memo[i].direction;
		int j = memo[i].first_tree;

		Abbatti(j, dir);

		if (dir == true)
			i = rep[i] + 1;
		else
			i = j + 1;
	}
}
