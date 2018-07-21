/**
 *  Soluzione di hogwarts. (Alice Cortinovis)
 *
 *  Descrizione: Soluzione quasi ottima, complessità O(Mlog M + Tmax)
 *  Cosa fa:
 *   1) ordino gli archi per tempo di comparsa, usando il solito sort del c++
 *   2) Ad ogni tempo t, mi tengo memorizzati i nodi raggiungibili; inoltre al tempo t vedo quali archi compaiono, e se sono percorribili
 *      e utili (cioè se esattamente uno dei due estremi è già raggiungibile) li aggiungo in "archi_usabili", se sono inutili
 *      (cioè entrambi gli estremi sono già raggiungibili) li butto via, se entrambi gli estremi sono momentaneamente irraggiungibili
 *      li salvo da un'altra parte (in "G"). Per ogni elemento di archi_usabili che sia ancora utilizzabile (cioè che non sia scomparso nel frattempo)
 *      segno che il nuovo nodo è raggiungibile; alla fine aggiungo ad archi_usabili gli archi che partono dai nodi appena aggiunti, prendendoli da "G".
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cassert>
#include <climits>

#define MAXN 1000000
#define MAXM 2000000
#define MAXT 5000000

using namespace std;

typedef pair<int, int> ii;

int N, M, MaxT;
int *A, *B, *T1, *T2;
int app[MAXM];
vector<ii> G[MAXN]; // first indica l'arrivo, second indica il tempo di scomparsa (se sono qui vuol dire che siamo dopo la loro comparsa)

int sol[MAXN];
bool raggiungibili[MAXN];
queue<ii> archi_usabili; // first indica l'arrivo, second indica il tempo di scomparsa
queue<int> nuovi_nodi; // forse c'è da fare qualcosa di più sofisticato per non aggiungere troppe volte lo stesso nodo.
					   // O forse no perché tanto li aggiungo al più M volte quindi non esplode niente

bool archi_sort_function(int x, int y) {
	if (T1[x] != T1[y]) return (T1[x] < T1[y]);
	if (T2[x] != T2[y]) return (T2[x] < T2[y]);
	if (A[x] != A[y]) return (A[x] < A[y]);
	if (B[x] != B[y]) return (B[x] < B[y]);
	
	assert(false);
	return false;
}

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
	::N = N;
	::M = M;
	::A = A;
	::B = B;
	::T1 = inizio;
	::T2 = fine;
	
	// Ordino gli archi per entrata (per ora in O(M log M), dopo lo riscrivo bene...)
	for (int i=0; i<M; i++) app[i] = i;
	sort(app, app+M, archi_sort_function);
	
	// Inizializzazione
	for (int i=0; i<M; i++) MaxT = max(MaxT, fine[i]);
	for (int i=1; i<N; i++) sol[i] = INT_MAX;
	nuovi_nodi.push(0);
	int index = 0; // è il contatore che scorre sugli archi
	
	for (int t = 0; t <= MaxT; t++) {		
		// Aggiungo i nuovi nodi
		while (!nuovi_nodi.empty()) {
			int nodo = nuovi_nodi.front();
			nuovi_nodi.pop();
			
			if (raggiungibili[nodo]) {
				assert(sol[nodo] == t);
				continue;
			}
			
			sol[nodo] = t;
			raggiungibili[nodo] = true;
			
			// Aggiungo gli archi che partono dal nuovo nodo, se sono ancora presenti
			// (non ho bisogno di cancellarli da G perché non li guarderò mai più in G)
			for (int i = (int)G[nodo].size()-1; i >= 0; i--)
				if (G[nodo][i].second >= t+1)
					archi_usabili.push(G[nodo][i]);
		}
					
		// Aggiungo a G o ad archi_usabili i nodi che compaiono al tempo t
		while (index < M && T1[app[index]] == t) {
			if (!raggiungibili[A[app[index]]] && !raggiungibili[B[app[index]]]) {
				G[A[app[index]]].push_back(make_pair(B[app[index]], T2[app[index]]));
				G[B[app[index]]].push_back(make_pair(A[app[index]], T2[app[index]]));
			}
			
			else if (raggiungibili[A[app[index]]] && !raggiungibili[B[app[index]]])
				archi_usabili.push(make_pair(B[app[index]], T2[app[index]]));
				
			else if (raggiungibili[B[app[index]]] && !raggiungibili[A[app[index]]])
				archi_usabili.push(make_pair(A[app[index]], T2[app[index]]));
			
			index++;
		}
			
		// Guardo che nuovi nodi posso raggiungere con archi_usabili
		while (!archi_usabili.empty()) {
			int arrivo = archi_usabili.front().first;
			int fine = archi_usabili.front().second;
			archi_usabili.pop();
			
			if (fine <= t) continue; // l'arco è diventato inutilizzabile
			if (raggiungibili[arrivo]) continue; // l'arco è diventato inutile
			
			nuovi_nodi.push(arrivo);
			// Esco dalla funzione se ho trovato la risposta
			if (arrivo == N-1) return (t+1);
		}
	}	
	
	return -1;
}
