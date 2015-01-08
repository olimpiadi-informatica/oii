#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int const MAXN = 1000;

int n; // Lunghezza nastro
int s; // Numero di stati
int c; // Numero di caratteri distinti

pair<int,int> transizione[MAXN][MAXN]; // (stato, carattere) -> (stato, spostamento)

int nastro[MAXN];

pair<int,int> grafo[MAXN][MAXN]; 	// (posizione, stato) -> (posizione, stato)
int termina[MAXN][MAXN]; 			// 1 = termina; -1 = non termina; 0 = non si sa ancora.
bool visitato[MAXN][MAXN]; 			// 1 = visitato; 0 = non visitato.

void read() {
	scanf("%d %d %d",&n,&s,&c);
	
	for (int i=0; i<s*c; ++i) {
		int x,y,z,t;
		scanf("%d %d %d %d",&x,&y,&z,&t);
		
		transizione[x][y] = pair<int,int> ( z, t );
	}
	
	for (int i=0; i<n; ++i) {
		scanf("%d",nastro+i);
	}
}

int decidi (int pos, int stato) {
	if ( visitato[pos][stato] ) {
		if ( termina[pos][stato] == 1 ) return 1;
		if ( termina[pos][stato] == -1 ) return -1;
		
		termina[pos][stato] = -1;
		return -1;
	}
	
	visitato[pos][stato] = 1;
	
	if ( pos == 0 ) {
		termina[pos][stato] = 1;
		return 1;
	}
	
	int res = decidi ( grafo[pos][stato].first, grafo[pos][stato].second );
	termina[pos][stato] = res;
	return res;
}

vector<int> soluzioni;

void solve() {
	
	for (int i=0; i<n; i++) {
		for (int j=0; j<s; ++j) {
			// posizione i, stato j
			pair<int,int> nuovo = transizione[j][ nastro[i] ]; // (nuovo stato, spostamento)
			grafo[i][j] = pair<int,int> ( i + nuovo.second, nuovo.first );
		}
	}
	
	for (int i=0; i<n; ++i) {
		if ( decidi(i,0) == 1 ) soluzioni.push_back(i);
	}
	
}

void write() {
	printf("%d\n", soluzioni.size());
	for (int k=0; k<soluzioni.size(); ++k) {
		printf("%d\n",soluzioni[k]);
	}
}

int main() {
	read();
	solve();
	write();
	
	return 0;
}
