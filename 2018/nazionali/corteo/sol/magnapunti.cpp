// chiama questa funzione per spostare un corteo (non la devi implementare!)
// chi = 1..2
// dove = 0..N-1
#include <vector>
#include <queue>

using namespace std;

void sposta(int chi, int dove);

int D[6000];
vector<int> L[6000];

int idx = 1;
int calcola(int s, int d) {
	idx++;

	queue<pair<int, int> > q;
	q.push(make_pair(s, 0));

	while (q.size()) {
		pair<int, int> n = q.front(); q.pop();

		if (n.first == d)
			return n.second;

		for (int nn : L[n.first]) {
			if (D[nn] == idx) continue;
			D[nn] = idx;
			q.push(make_pair(nn, n.second+1));
		}
	}

}




int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]) {

	for (int i = 0; i < M; i++) {
		L[A[i]].push_back(B[i]);
		L[B[i]].push_back(A[i]);
	}

	int d1 = calcola(P1, P2);
	int d2 = calcola(D1, D2);

	return min(d1, d2);
}

