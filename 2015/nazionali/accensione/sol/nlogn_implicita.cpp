#include <iostream>
#include <cstdlib>
using namespace std;

const int MAXN = 1000000;

void Accendi(int N, int acceso[], int pulsante[]) {
	// Parto dal fondo: ogni volta che trovo un computer da accendere,
	// controllo se è acceso o spento controllando i suoi multipli
	// Nel caso sia spento, premo l'interruttore relativo
	for (int i=N; i>0; i--) {
		int x = 2*i;
		while (x <= N) {
			if (pulsante[x] == true)
				acceso[i] = (!acceso[i]);
			x += i;
		}
		
		if (acceso[i] == false)
			pulsante[i] = true;
	}
}
