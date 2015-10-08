#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int R;
const int MAXR = 100000;
int A[MAXR], B[MAXR];

void ex(const char *msg, float res) {
	cerr << msg;
	cout << res;

	exit(0);
}

int main(int argc, char *argv[]) {
	if (argc < 4) return 1;

	ifstream fin(argv[1]);  // input
	ifstream fcor(argv[2]); // output corretto
	ifstream fout(argv[3]); // da controllare

	fin >> R;
	for (int i = 0; i < R; i++) fin >> A[i] >> B[i];

	int MinK = 1e9;
	int LastT, NextT;
	fcor >> LastT;
	for (int i = 1; i < R; i++) {
		fcor >> NextT;
		MinK = min(MinK, NextT - LastT);
		LastT = NextT;
	}

	// Qua devo gestire ciò che resta!
	if (!(fout >> LastT)) {
		ex("Soluzione malformata", 0.0);
	}
	if (LastT < A[0] or B[0] < LastT) {
		ex("Soluzione errata: atterraggio non nell'intervallo", 0.0);
	}
	for (int i = 1; i < R; i++) {
		if (!(fout >> NextT)) ex("Soluzione malformata", 0.0);
		if (NextT < A[i] or B[i] < NextT) ex("Soluzione errata: atterraggio non nell'intervallo", 0.0);
		if (NextT < LastT) ex("Soluzione errata: atterraggi non in ordine", 0.0);
		if (NextT-LastT < MinK) ex("Soluzione subottima: non viene realizzato il minimo K", 0.0);
		LastT = NextT;
	}

	ex("Soluzione corretta", 1.0);

	return 0;
}
