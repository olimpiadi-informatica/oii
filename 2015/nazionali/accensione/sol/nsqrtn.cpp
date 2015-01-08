#include <iostream>
#include <cstdlib>

using namespace std;

const int MAXN = 1000000;

void Accendi(int N, int acceso[], int pulsante[]) {
	// Parto dal fondo: ogni volta che trovo un computer da accendere,
	// premo il pulsante relativo e aggiorno tutti i divisori (l'ordine delle operazioni non conta)
	for (int i=N; i>0; i--) {
		if (acceso[i] == false) {
			pulsante[i] = true;
			for (int j=1; j*j<=i; j++)
				if (i%j == 0) {
					acceso[j] ^= true;
					if (j*j != i)
						acceso[i/j] ^= true;
				}
		}
	}
}
