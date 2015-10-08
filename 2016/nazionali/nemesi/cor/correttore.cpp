#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

int N;
const int MAXN = 100000;
int nemici[MAXN];
int gruppo[MAXN];

void ex(const char *msg, float res = 0) {
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
	for (int i = 0; i < N; i++) fin >> nemici[i];

	string line;
	int g_cor = 0;
	while (getline(fcor, line)) g_cor++;
	
	int g_out = 0;
	while (getline(fout, line)) {
		g_out++;
		stringstream s(line);
		int at;
		while (s >> at) {
			if (gruppo[at] != 0) ex("Output malformato: bambini duplicati");
			gruppo[at] = g_out;
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (gruppo[i] == 0) ex("Output malformato: bambini mancanti");
	}
	
	for (int i = 0; i < N; i++) {
		if (gruppo[i] == gruppo[nemici[i]]) ex("Risposta errata: due nemici nello stesso gruppo");
	}
	
	if (g_cor == g_out) ex("Risposta corretta", 1.0);

	ex("Risposta subottima", 1.0 /(1<<(g_out-g_cor)));

	return 0;
}
