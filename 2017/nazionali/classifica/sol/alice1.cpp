/** 
 * Sorpasso in O(1)
 * Squalifica in O(N)
 * Risposta in O(N)
 **/

#include <iostream>
#include <cassert>
#include <algorithm>

#define MAXN 1000005

using namespace std;

int N;
int posizioni[MAXN]; // posizioni[i] contiene l'id dell'i-esimo in classifica
int inverso[MAXN];
bool squalificato[MAXN]; // (serve davvero questo array?)
int precedente[MAXN]; // vale 0 se sono il primo della lista, precedente[i] dice l'id del tizio prima di i
int successivo[MAXN]; // idem con il tizio dopo
int classifica[MAXN]; // classifica[i] contiene la posizione dell'i-esimo tizio di "posizioni"

void inizia(int N, int* ids) {
	::N = N;
	for (int i=1; i<=N; i++) posizioni[i] = ids[i-1]+1;
	for (int i=1; i<=N; i++) inverso[posizioni[i]] = i;
	for (int i=1; i<=N; i++) precedente[i] = posizioni[inverso[i]-1];
	for (int i=1; i<=N; i++) successivo[i] = posizioni[inverso[i]+1];
	for (int i=1; i<=N; i++) classifica[i] = i;
}

void squalifica(int id) {
	id++;
	squalificato[id] = true;
	int pos = inverso[id];
	precedente[successivo[id]] = precedente[id];
	successivo[precedente[id]] = successivo[id];
	for (pos = pos+1; pos <= N; pos++) classifica[pos]--; // Qui si perde tempo
	
	//for (int i=1; i<=N; i++) cout << precedente[i] << " "; cout << endl;
	//for (int i=1; i<=N; i++) cout << successivo[i] << " "; cout << endl;
}

void supera(int id) {
	id++;
	int pos1 = inverso[id];
	int pos2 = inverso[precedente[id]];
	swap(posizioni[pos1], posizioni[pos2]);
	swap(inverso[id], inverso[precedente[id]]);
	
	int prec = precedente[id];
	int succ = successivo[id];
	int precprec = precedente[prec];
	
	precedente[id] = precprec;
	precedente[prec] = id;
	precedente[succ] = prec;
	
	successivo[id] = prec;
	successivo[precprec] = id;
	successivo[prec] = succ;
	
	//for (int i=1; i<=N; i++) cout << precedente[i] << " "; cout << endl;
	//for (int i=1; i<=N; i++) cout << successivo[i] << " "; cout << endl;
	
}

int partecipante(int id) {
	int pos = id;
	// Cerco l'ultimo elemento di classifica che abbia come valore pos
	// Per ora in O(N)
	for (int i=N; i>=1; i--)
		if (classifica[i] == pos)
			return posizioni[i]-1;
			
	assert(false); // Qui non ci dovrebbe mai arrivare
}
