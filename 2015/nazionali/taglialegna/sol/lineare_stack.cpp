#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <cassert>

using namespace std;

void Abbatti(int, int);

void dbg(vector<int>& v) {
	for (int i = 0; i < (int)v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

typedef pair<int, int> ii;

struct memo_t {
	int trees, first_tree;
	bool direction; // false = sinistra, true = destra

	memo_t() {}
	memo_t(int trees, int first_tree, bool direction): trees(trees), first_tree(first_tree), direction(direction) {}

	bool operator< (const memo_t& o) const {
		return trees < o.trees;
	}
};

void Pianifica(int N, int H[]) {
	vector<int> lep(N); // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
						// distrutto dall'abbattimento di i
	vector<int> rep(N); // fissato i, rep[i] contiene l'indice dell'albero più a destra
						// distrutto dall'abbattimento di i

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

	vector<memo_t> memo(N);
	stack<ii> S;

	int j;
	for (int i = 0; i < N; i++) {
		// Primo caso: butto i a sinistra
		j = lep[i] - 1;
		if (j >= 0)
			memo[i] = memo_t(1 + memo[j].trees, i, false);
		else
			memo[i] = memo_t(1, i, false);

		// Secondo caso: abbatto a destra un albero che abbatte i nella caduta
		while (!S.empty() && rep[S.top().first] < i)
			S.pop();
		if (!S.empty()) {
			j = S.top().second - 1;

			if (j >= 0)
				memo[i] = min(memo[i], memo_t(1 + memo[j].trees, j + 1, true));
			else
				memo[i] = min(memo[i], memo_t(1, j + 1, true));
		}

		j = i;
		if (!S.empty())
			if (S.top().second == 0 || memo[S.top().second - 1].trees < memo[i - 1].trees)
				j = S.top().second;

		S.push(ii(i, j));
	}

	// Ricostruisci la soluzione
	int i = N - 1;
	while (i >= 0) {
		Abbatti(memo[i].first_tree, memo[i].direction);
		
		if (memo[i].direction == false) // A sinistra
			i = lep[i] - 1;
		else
			i = memo[i].first_tree - 1;
	}
}
