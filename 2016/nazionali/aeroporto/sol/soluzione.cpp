/**
 *  Soluzione ottima
 *
 *  Autore: Federico
 *
 *  Descrizione: Viene fatta una ricerca binaria sul K minimo ed una volta 
 *  trovato viene realizzato linearmente.
 *  La complessità è R*log(T).
 */

void pianifica(int R, int A[], int B[], int T[]) {
	// Ricerca binaria sul minor K possibile
	int l = 0;
	int r = 1e9;
	while (l+1  < r) {
		int m = (l+r)/2;
		bool feasible = true;
		
		int FirstTimeFree = 0;
		for (int i = 0; i < R; i++) {
			if (FirstTimeFree < A[i]) FirstTimeFree = A[i] + m;
			else if (FirstTimeFree <= B[i]) FirstTimeFree += m;
			else {
				feasible = false;
				break;
			}
		}
		
		if (feasible) l = m;
		else r = m;
	}
	
	// Assumendo K=l, viene riempito adeguatamente l'array T[]
	int FirstTimeFree = 0;
	for (int i = 0; i < R; i++) {
		if (FirstTimeFree < A[i]) T[i] = A[i], FirstTimeFree = A[i] + l;
		else T[i] = FirstTimeFree, FirstTimeFree += l;
	}
}

