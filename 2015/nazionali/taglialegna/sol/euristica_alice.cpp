#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <vector>

using namespace std;

const int MAXN = 502;
const int INF = numeric_limits<int>::max();
int *h;

typedef pair<int, int> ii;

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
int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i

void Abbatti(int, int);

return_t risolvi(int l, int r) { // calcola la soluzione dell'intervallo [l, r)
	//cout << l << " " << r << " risolvi(l, r)\n";
	assert(l < r);

	if (memo[l][r].trees != INF)
		return memo[l][r];

	return_t ans;
	
	// Trovo (gli) alberi che massimizzano il numero di alberi che buttano giù
	vector<ii> candidati;
	int best; // quanti ne abbatte quello che ne abbatte di più
	
	for (int i=l; i<r; i++) {
		if (candidati.empty()) {
			best = max(i-lep[i], rep[i]-i);
			if (i-lep[i] > rep[i]-i)
				candidati.push_back(make_pair(i, 0));
			else if (i-lep[i] < rep[i]-i)
				candidati.push_back(make_pair(i, 1));
			else {
				candidati.push_back(make_pair(i, 0));
				candidati.push_back(make_pair(i, 1));
			}
		}
		else {
			if (best == i-lep[i])
				candidati.push_back(make_pair(i, 0));
			else if (best < i-lep[i]) {
				candidati.clear();
				best = i-lep[i];
				candidati.push_back(make_pair(i, 0));
			}
			
			if (best == rep[i]-i)
				candidati.push_back(make_pair(i, 1));
			else if (best < rep[i]-i) {
				candidati.clear();
				best = rep[i]-i;
				candidati.push_back(make_pair(i, 1));
			}
		}			
	}
	
	/*for (int i=0; i<(int)candidati.size(); i++)
		cout << candidati[i].first << " " << candidati[i].second << endl;
	cout << endl;*/
	
	for (int i=0; i<(int)candidati.size(); i++) {
		return_t caso(1, candidati[i].first, candidati[i].second);

		// Abbatti l'albero i a sinistra
		if (candidati[i].second == 0) {
			int j = lep[candidati[i].first];
		
			if (j > l) {
				//cout << "cucu 1\n";
				caso.trees += risolvi(l, j).trees;
			}
			if (candidati[i].first + 1 < r) {
				//cout << "cucu 2\n";
				caso.trees += risolvi(candidati[i].first + 1, r).trees;
			}
		}
		
		// Abbatti l'albero i a destra
		else {
			int j = rep[candidati[i].first];

			if (candidati[i].first > l) {
				//cout << "cucu 3\n";
				caso.trees += risolvi(l, candidati[i].first).trees;
			}
			if (j < r - 1) {
				//cout << "cucu 4\n";
				caso.trees += risolvi(j + 1, r).trees;
			}
		}

		ans = min(ans, caso);
	}

	return memo[l][r] = ans;

}

void ricostruisci(int l, int r) {
	assert(l < r);

	int i = memo[l][r].first_tree;
	bool dir = memo[l][r].direction;
	//cout << l << " " << r << " l e r\n";

	Abbatti(i, dir);

	if (dir == false) { // sinistra
		int j = lep[i];
		
		if (j > l)
			ricostruisci(l, j);
		if (i + 1 < r)
			ricostruisci(i + 1, r);
	}
	else {
		int j = rep[i];

		if (i > l)
			ricostruisci(l, i);
		if (j < r - 1)
			ricostruisci(j + 1, r);
	}
}

void Pianifica(int N, int H[]) {
	h = H;

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

	risolvi(0, N);
	
	//cout << memo[0][N].trees << " " << memo[0][N].first_tree << endl;

	ricostruisci(0, N);
}
