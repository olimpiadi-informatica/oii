/** Soluzione che simula tutto tenendosi soltanto l'array degli id in ordine **/
/** Alla funzione partecipante dai la posizione e lei ti dice l'id del tizio in quella posizione **/

#include <iostream>
#include <cassert>
#include <algorithm>

#define MAXN 1000002

using namespace std;

int N;
int posizioni[MAXN];
bool squalificato[MAXN];

void inizia(int N, int* ids) {
	::N = N;
	for (int i=0; i<N; i++) posizioni[i] = ids[i];
}

void squalifica(int id) {
	squalificato[id] = true;
	
	int i=0; 
	while (posizioni[i] != id) i++;
	for (i; i<N-1; i++) posizioni[i] = posizioni[i+1];
	N--;
}

void supera(int id) {
	int i=0;
	
	while (posizioni[i] != id) i++;
	swap(posizioni[i], posizioni[i-1]);
}

int partecipante(int id) {
	assert(id <= N);
	return posizioni[id-1]; 
}

