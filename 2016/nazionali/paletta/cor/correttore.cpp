#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int N;
const int MAXN = 1500000;
int V[MAXN];

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

	fin >> N;
	for (int i = 0; i < N; i++) fin >> V[i];

	long long scambiCor;
	fcor >> scambiCor;

	long long scambi;
	if (!(fout >> scambi)) {
		ex("Output malformato", 0.0);
	}
    if (scambi == -1 xor scambiCor == -1) {
        ex("Risposta errata: ordinabilità non rispettata", 0.0);
    }

    if (scambi == scambiCor) 
        ex("Risposta corretta", 1.0);

    ex("Risposta errata: numero di scambi errato", 0.2);
	return 0;
}
