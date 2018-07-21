/** 
 * Sorpasso in O(N) ma se il generatore è fatto male, probabilmente molto meno...
 * Squalifica in O(1)
 * Risposta in O(N)
 **/

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define MAXN 1000005

using namespace std;

int N;
int posizioni[MAXN]; // posizioni[i] contiene l'id dell'i-esimo in classifica
int inverso[MAXN]; // dice in che posizione sta i (non è la posizione vera, può esserci gente squalificata prima di lui in realtà)
bool squalificato[MAXN]; // (serve davvero questo array?)

void inizia(int N, int* ids) {
	::N = N;
	for (int i=1; i<=N; i++) posizioni[i] = ids[i-1];
    for (int i=1; i<=N; i++)
        inverso[posizioni[i]] = i;
}

void squalifica(int id) {
	squalificato[id] = true;
}

void supera(int id) {
	int a = inverso[id]; // posizione del tizio che supera
    int b = a-1; // sarà la posizione del tizio che è stato superato
    while (squalificato[posizioni[b]]) b--;
    swap(posizioni[a], posizioni[b]);
    inverso[id] = b;
    inverso[posizioni[a]] = a;
}

int partecipante(int id) {
	int pos = id;
    int cont = 0;
    for (int i=0; i<id; i++) {
        cont++;
        while (squalificato[posizioni[cont]]) cont++;
    }
    return posizioni[cont];
}
