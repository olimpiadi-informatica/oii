/**
 *  Soluzione subottima
 *
 *  Autore: Federico
 *
 *  Descrizione: Si cerca il K minimo scorrendoli tutti ed una volta 
 *  trovato viene realizzato linearmente.
 *  La complessità è R*T.
 */

void pianifica(int R, int A[], int B[], int T[]) {
	// Ricerca lineare sul minor K possibile
	int l = 0;
	bool feasible = true;
	while (feasible) {
		l++;
		
		int FirstTimeFree = 0;
		for (int i = 0; i < R; i++) {
			if (FirstTimeFree < A[i]) FirstTimeFree = A[i] + l;
			else if (FirstTimeFree <= B[i]) FirstTimeFree += l;
			else {
				feasible = false;
				break;
			}
		}
	}
	l--;
	
	// Assumendo K=l, viene riempito adeguatamente l'array T[]
	int FirstTimeFree = 0;
	for (int i = 0; i < R; i++) {
		if (FirstTimeFree < A[i]) T[i] = A[i], FirstTimeFree = A[i] + l;
		else T[i] = FirstTimeFree, FirstTimeFree += l;
	}
}

