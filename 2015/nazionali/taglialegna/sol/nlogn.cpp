#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
#include <stack>
#include <cassert>

using namespace std;

inline int lowbit(const int i) {
	return i & (-i);
}

void Abbatti(int, int);

const int INF = numeric_limits<int>::max();
const int MAXN = 2000005;
int N;

int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i

int memo[MAXN];
int first_tree[MAXN];
bool direzione[MAXN];

template<typename Comp>
struct fenwick_t {
	size_t n = MAXN;
	Comp comp;
	int tree[MAXN + 1];

	fenwick_t(Comp comp): comp(comp) {
		memset(tree, -1, sizeof tree);
	}

	int get_min(size_t i) {
		int ans = -1;
		for (++i; i; i -= lowbit(i)) {
			if (comp(tree[i], ans))
				ans = tree[i];
		}
		return ans;
	}

	void update(size_t i, int val) {
		for (++i; i <= n; i += lowbit(i))
			tree[i] = min(tree[i], val, comp);
	}
};
typedef fenwick_t<function<bool(int, int)> > ft_t;

// Costruisci il Fenwick tree
ft_t ft([](int a, int b) {
	if (a == -1 || b == N - 1)
		return false;
	if (b == -1 || a == N - 1)
		return true;
	return memo[a + 1] < memo[b + 1];
});

void Pianifica(int n, int H[]) {
	N = n;

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
	for (int i = N - 1; i >= 0; i--) {
		// Primo caso: butto i a destra
		j = rep[i] + 1;

		test = 1;
		if (j < N)
			test += memo[j];

		memo[i] = test;
		first_tree[i] = i;
		direzione[i] = true;

		// Secondo caso: abbatto a sinistra un albero che abbatte i nella caduta
		j = ft.get_min(i);

		if (j != -1) { // Esiste almeno un albero che distrugge i cadendo a sx
			++j;
			test = 1;
			if (j < N)
				test += memo[j];

			if (test < memo[i]) {
				memo[i] = test;
				first_tree[i] = j - 1;
				direzione[i] = false;
			}
		}

		ft.update(lep[i], i);
	}

	// Ricostruisci la soluzione
	int i = 0;
	while (i < N) {
		Abbatti(first_tree[i], direzione[i]);
		
		if (direzione[i] == true) // A destra
			i = rep[i] + 1;
		else
			i = first_tree[i] + 1;
	}
}
