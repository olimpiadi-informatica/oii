#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>

using namespace std;

const int MAXN = 502;
const int INF = numeric_limits<int>::max();
int *h;

struct return_t {
	int trees, first_tree;
	bool direction; // false = sinistra, true = destra

	return_t(): trees(INF) {}
	return_t(int trees, int first_tree, bool direction): trees(trees), first_tree(first_tree), direction(direction) {}

	bool operator< (const return_t& o) const {
		return trees < o.trees;
	}
};

return_t memo[MAXN][MAXN];

void Abbatti(int, int);

return_t risolvi(int l, int r) { // calcola la soluzione dell'intervallo [l, r)
	assert(l < r);

	if (memo[l][r].trees != INF)
		return memo[l][r];

	return_t ans;

	for (int i = l; i < r; i++) {
		return_t left_case(1, i, false);
		return_t right_case(1, i, true);

		// Abbatti l'albero i a sinistra
		int accumula = h[i] - 1, j;
		for (j = i-1; j >= l && accumula; j--)
			accumula = max(accumula - 1, h[j] - 1);
		
		if (j >= l)
			left_case.trees += risolvi(l, j + 1).trees;
		if (i + 1 < r)
			left_case.trees += risolvi(i + 1, r).trees;
		
		// Abbatti l'albero i a destra
		accumula = h[i] - 1;
		for (j = i+1; j < r && accumula; j++)
			accumula = max(accumula - 1, h[j] - 1);
		
		if (i > l)
			right_case.trees += risolvi(l, i).trees;
		if (j < r)
			right_case.trees += risolvi(j, r).trees;

		ans = min(ans, left_case);
		ans = min(ans, right_case);
	}

	return memo[l][r] = ans;

}

void ricostruisci(int l, int r) {
	assert(l < r);

	int i = memo[l][r].first_tree;
	bool dir = memo[l][r].direction;

	Abbatti(i, dir);

	if (dir == false) { // sinistra
		int accumula = h[i] - 1, j;
		for (j = i-1; j >= l && accumula; j--)
			accumula = max(accumula - 1, h[j] - 1);
		
		if (j >= l)
			ricostruisci(l, j + 1);
		if (i + 1 < r)
			ricostruisci(i + 1, r);
	}
	else {
		int accumula = h[i] - 1, j;
		for (j = i+1; j < r && accumula; j++)
			accumula = max(accumula - 1, h[j] - 1);
		
		if (i > l)
			ricostruisci(l, i);
		if (j < r)
			ricostruisci(j, r);
	}
}

void Pianifica(int N, int H[]) {
	h = H;

	risolvi(0, N);

	ricostruisci(0, N);
}
