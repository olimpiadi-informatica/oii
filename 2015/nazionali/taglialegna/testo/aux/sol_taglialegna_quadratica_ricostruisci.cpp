// ricostruisci_tagli(i) si occupa di tagliare, attraverso opportune chiamate alla funzione Abbatti, il
// minimo numero di alberi affinchè tutti gli alberi da i a N-1 inclusi risultino abbattuti alla fine del
// processo. Riusa internamente le informazioni calcolate dalla funzione risolvi illustrata poco prima
void ricostruisci_tagli(int i) {
	if (i == N)
		return;

	int primo_albero = risolvi(i).primo_albero;
	direzione_t direzione = risolvi(i).direzione;

	Abbatti(primo_albero, direzione);

	if (direzione == SINISTRA)
		ricostruisci_tagli(primo_albero + 1);
	else
		ricostruisci_tagli(rep[i] + 1);
}