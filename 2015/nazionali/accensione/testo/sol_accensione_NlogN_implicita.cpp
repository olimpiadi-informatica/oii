void Accendi(int N, int acceso[], int pulsante[]) {
	for (int i = N; i >= 1; i--) {
		int stato_del_pc_i = acceso[i];
		
		// Controllo tutti i pulsanti con numero multiplo di i
		for (int j = 2 * i; j <= N; j += i) {
			// Se il pulsante j è stato premuto, lo stato del computer
			// i è stato invertito
			if (pulsante[j] == 1)
				stato_del_pc_i ^= 1;
		}
		
		if (stato_del_pc_i == 0)
			pulsante[i] = 1;
	}
}
