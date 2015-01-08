#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAXN = 1000000;

vector<int> divisori[MAXN + 1];

void Accendi(int N, int acceso[], int pulsante[]) {
	// Precalcolo tutti i divisori
	for (int i=1; i<=N; i++)
		for (int j=i; j<=N; j+=i)
			divisori[j].push_back(i);
	
	// Parto dal fondo: ogni volta che trovo un computer da accendere,
	// controllo se è acceso o spento. Se è spento, premo il pulsante
	// e aggiorno i divisori, che ho precalcolato
	for (int i=N; i>0; i--) 
		if (acceso[i] == false) {
			pulsante[i] = true;
			
			for (int j=0; j<(int)divisori[i].size(); j++)
				acceso[divisori[i][j]] = (!acceso[divisori[i][j]]);
		}
}
