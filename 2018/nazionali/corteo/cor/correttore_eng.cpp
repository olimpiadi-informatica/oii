#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

void ex(const char *msg, float res) {
	fprintf(stderr, "%s ", msg);
	printf("%f\n", res);
	exit(0);
}

const int MAXN = 10000;

typedef std::pair<int,int> ii;

// dist[a][b] = distanza tra a e b nel grafo
int dist[MAXN][MAXN];
// conn[a][b] = 1 sse a e b sono direttamente connessi
bool conn[MAXN][MAXN];
// liste di adiacenza
std::vector<int> adj[MAXN];

int N, M, S[3], D[3];
// spostamenti fatti dal contestant
std::vector<ii> spostamenti;
int a, b, res;

void calcola_dist() {
	// calcola le distanze tra tutte le coppie di noti con N bfs
	std::queue<int> q;
	for (int s = 0; s < N; s++) {
		for (int i = 0; i < N; i++)
			dist[s][i] = 10000000;
		q.push(s);
		dist[s][s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : adj[u]) {
				if (dist[s][v] > dist[s][u]+1) {
					dist[s][v] = dist[s][u]+1;
					q.push(v);
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << std::endl;
		return 1;
	}

	// file di input
	std::ifstream fin(argv[1]);
	// output corretto
	std::ifstream fres(argv[2]);
	// output del contestant
	std::ifstream fout(argv[3]);

	if (!fres)
		ex("Can't open jury's output file.", 0.0);
	if (!fout)
		ex("Can't open contestant's output file.", 0.0);

	// leggo il file di input
	fin >> N >> M >> S[1] >> D[1] >> S[2] >> D[2];

	// leggo file di output del contestant
	while (a >= 0) {
		// a: comando  b: parametro
		// a=1 sposta A
		// a=2 sposta B
		// a=-1 risultato
		std::string line;
		std::getline(fout, line);
		std::stringstream ss(line);

		if (line.find(" ") != std::string::npos) {
			ss >> a >> b;
		} else {
			a = -1;
			ss >> b;
		}

		if (a == 1 || a == 2) {
			if (b < 0 || b >= N)
				ex("Malformed output", 0.0);
			spostamenti.emplace_back(a, b);
		} else if (a == -1)
			res = b;
		else
			ex("Malformed output", 0.0);
	}

	// leggo l'output della soluzione

	// numero di operazioni della soluzione
	int sol_op = 0;
	// risultato della soluzione
	int sol_res = -1;

 	while (1) {
		std::string line;
		std::getline(fres, line);
		std::stringstream ss(line);

		if (line.find(" ") != std::string::npos) {
			ss >> a >> b;
		} else {
			a = -1;
			ss >> b;
		}

		// ignoro tutti gli spostamenti
		if (a == -1)
			break;
		else
			sol_op++;
	}

	sol_res = b;

	if (res == sol_res)
		ex("Output is correct", 1.0);
	else if (spostamenti.size() == 0)
		ex("Wrong answer and schedule non provided", 0.0);


	// leggo il grafo in input
	for (int i = 0; i < M; i++) {
		fin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		conn[a][b] = true;
		conn[b][a] = true;
	}
	calcola_dist();

	// distanza minima tra i due cortei
	int distanza = dist[S[1]][S[2]];
	// posizione dei due cortei
	int pos[3] = {-1, S[1], S[2]};

	for (auto cmd : spostamenti) {
		// chi si muove, 1..2
		int chi = cmd.first;
		// dove si muove, 0..N-1
		int dove = cmd.second;

		// posizione attuale del corteo che si muove
		int da = pos[chi];
		// controllo che l'arco da usare esista
		if (!conn[da][dove])
			ex("A move was made on a non-existent edge", 0.0);
		// sposto il corteo
		pos[chi] = dove;

		// calcolo la nuova distanza minima considerando quella dopo lo spostamento
		distanza = std::min(distanza, dist[pos[1]][pos[2]]);
	}
	// controllo di essere arrivato a destinazione
	if (pos[1] != D[1] || pos[2] != D[2])
		ex("The destinations weren't reached", 0.0);

	if (distanza > sol_res)
		ex("Contact the admins", 0);
	if (distanza == sol_res)
		ex("Output is correct", 1);

	ex("Suboptimal schedule", 0.5f * distanza / sol_res);
}
