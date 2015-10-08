/**
 *  Soluzione di nemesi
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Soluzione che trova i cicli in modo stupido in O(n^2),
 *  assegna il gruppo per i bambini in ogni ciclo e poi negli altri 
 */


#include <iostream>
#define MAXN 100000
using namespace std;

void nuovo_gruppo();

void aggiungi(int bambino);

int N;
int nem[MAXN]; //grafo
int gru[MAXN]; //gruppo
int res = 2; //numero di gruppi (minimo 2)


bool ciclo(int v) { //controlla se v sta in un ciclo
	int at = v;
	int tt = 0;
	while (tt < N) {
		tt++;
		at = nem[at];
		if (at == v) return true;
	}
	return false;
}

void assegna(int v) {
	if (gru[v] != 0) return;
	assegna(nem[v]);
	if (gru[nem[v]] == 3) gru[v] = 1;
	else gru[v] = 3 - gru[nem[v]];
}

void smista(int n, int nemico[]) {
	N = n;
	for (int i = 0; i < N; i++) nem[i] = nemico[i];
	
	for (int i = 0; i < N; i++) {
		if (gru[i] == 0 and ciclo(i)) {
			int gg = 1;
			gru[i] = 1;
			int at = nem[i];
			while (at != i) {
				if (nem[at] == i and gg == 2) {
					gru[at] = 3;
					res = 3;
					break;
				}
				gg = 3-gg;
				gru[at] = gg;
				at = nem[at];
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (gru[i] == 0) assegna(i);
	}
	
	for (int k = 1; k <= res; k++) {
		nuovo_gruppo();
		for (int i = 0; i < N; i++) {
			if (gru[i] == k) aggiungi(i);
		}
	}
}
