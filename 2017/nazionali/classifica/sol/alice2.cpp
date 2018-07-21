/** 
 * Sorpasso in O(1)
 * Squalifica in O(N)
 * Risposta in O(log N)
 **/

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define MAXN 1000005

using namespace std;

int N;
int posizioni[MAXN]; // posizioni[i] contiene l'id dell'i-esimo in classifica
int inverso[MAXN];
bool squalificato[MAXN]; // (serve davvero questo array?)
int precedente[MAXN]; // vale 0 se sono il primo della lista, precedente[i] dice l'id del tizio prima di i
int successivo[MAXN]; // idem con il tizio dopo
vector<int> classifica; // classifica[i] contiene la posizione dell'i-esimo tizio di "posizioni"

void inizia(int N, int* ids) {
	::N = N;
	for (int i=1; i<=N; i++) posizioni[i] = ids[i-1]+1;
	for (int i=1; i<=N; i++) inverso[posizioni[i]] = i;
	for (int i=1; i<=N; i++) precedente[i] = posizioni[inverso[i]-1];
	for (int i=1; i<=N; i++) successivo[i] = posizioni[inverso[i]+1];
	for (int i=0; i<=N; i++) classifica.push_back(i); // diventa un array di N+1 elementi, di cui il primo inutile
}

void squalifica(int id) {
	id++;
	squalificato[id] = true;
	int pos = inverso[id];
	precedente[successivo[id]] = precedente[id];
	successivo[precedente[id]] = successivo[id];
	for (pos = pos+1; pos <= N; pos++)
		classifica[pos] = classifica[pos]-1; // Qui si perde tempo
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
}

int partecipante(int id) {
	int pos = id;
	// Cerco l'ultimo elemento di classifica che abbia come valore pos
	vector<int>::iterator ub = upper_bound(classifica.begin(), classifica.end(), pos);
	return posizioni[ub - 1 - classifica.begin()]-1;	
}
