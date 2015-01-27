
/*
 * Soluzione di Giovanni per fuga
 *
 * Classica DFS con ricerca dei cicli di lunghezza >= 3; viene memorizzata la
 * distanza dalla radice in modo da sapere subito la lunghezza del ciclo e poter
 * scrivere la soluzione mentre si interrompe la ricorsione.
 */


#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_NODE_NUM = 100000;
const int MAX_EDGE_NUM = 200000;

int nodeNum, edgeNum;
vector< vector< int > > graph;
vector< int > depth;

int find_cycle(int n, int d = 1) {

	if (depth[n] > 0) return -1;		// Nodo già visitato
	depth[n] = d;

	for (int i = 0; i < graph[n].size(); i++) {
		int res = find_cycle(graph[n][i], d+1);
		int dist = depth[n] - depth[graph[n][i]] + 1;
		if (res == -1 && dist >= 3) {
			printf("%d\n%d", dist, n+1);	// Ciclo chiuso, comincio ad enumerare la soluzione interrompendo la ricorsione
			return graph[n][i];
		} else if (res >= 0) {
			printf(" %d", n+1);
			if (res == n) return -3;	// Soluzione trovata ed enumerata
			return res;
		} else if (res == -3) {
			return -3;					// Esecuzione terminata, interrompe la ricorsione
		}
	}

	return -2;		// Ramo senza soluzioni

}

int main() {

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	scanf("%d %d", &nodeNum, &edgeNum);
	graph.resize(nodeNum);
	depth.resize(nodeNum);
	for (int i = 0; i < edgeNum; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (c == 0) continue;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 0; i < nodeNum; i++) {
		if (find_cycle(i) == -3) break;
	}
	printf("\n");

	return 0;

}

