/*
 * Autore: William Di Luigi <williamdiluigi@gmail.com>
 * Esegue una ricerca in profondita' per controllare quante attrazioni
 * sono raggiungibili partendo dal nodo 0.
 * La ricerca viene eseguita quattro volte, rispettivamente:
 *     0) Sul grafo dei mezzi gratis
 *     1) Sul grafo dei mezzi gratis / autobus
 *     2) Sul grafo dei mezzi gratis / traghetti
 *     3) Sul grafo dei mezzi gratis / autobus / traghetti
 * Ogni ricerca ci dice quante attrazioni raggiungo.
 */

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define MAXN 1010

int N, A, M[3];
vector<int> attrazioni;
vector< pair<int,int> > archi[3];

bool visto[MAXN];
vector<int> adj[MAXN];

void dfs(int node) {
	visto[node] = true;
	for (vector<int>::iterator it=adj[node].begin(); it!=adj[node].end(); it++)
		if (!visto[*it])
			dfs(*it);
}

// Prova a raggiungere le attrazioni usando i mezzi descritti in "mask"
int solve(int mask) {
	// "Svuota" il grafo
	for (int i=0; i<MAXN; i++)
		adj[i].clear();
	// Crea il nuovo grafo
	for (int i=0; i<3; i++) if (mask & (1 << i)) {
		// Uso il mezzo i, quindi aggiungo tutti i suoi collegamenti
		for (int j=0; j<M[i]; j++) {
			int u = archi[i][j].first, v = archi[i][j].second;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}
	// Conta le attrazioni raggiungibili
	fill(visto, visto+N, false);
	dfs(0);
	int ret = 0;
	for (int i=0; i<A; i++) {
		if (visto[attrazioni[i]]) {
			ret ++;
		}
	}
	return ret;
}

int main()
{
	fin >> N >> A >> M[0] >> M[1] >> M[2];
	attrazioni.resize(A);
	for (int i=0; i<A; i++) {
		fin >> attrazioni[i];
	}
	for (int i=0; i<3; i++) {
		for (int j=0; j<M[i]; j++) {
			int u, v;
			fin >> u >> v;
			archi[i].push_back(make_pair(u, v));
		}
	}
	// Quante attrazioni raggiungo usando solo mezzi gratis
	fout << solve(1) << "\n";
	// Quante attrazioni raggiungo combinando mezzi gratis e BUS
	fout << solve(2 | 1) << "\n";
	// Quante attrazioni raggiungo combinando mezzi gratis e TRAGHETTO
	fout << solve(4 | 1) << "\n";
	// Quante attrazioni raggiungo combinando mezzi gratis, BUS e TRAGHETTO
	fout << solve(4 | 2 | 1) << "\n";
	return 0;
}
