/*
 * Autore: William Di Luigi <williamdiluigi@gmail.com>
 *
 * L'idea e' di mantenere un array, nella cui posizione i-esima
 * teniamo il numero di atleti di cui la squadra i-esima e' composta.
 * Man mano che otteniamo informazioni sugli studenti che sono gia'
 * saliti sui pulman, decrementiamo in modo opportuno e dalla
 * posizione opportuna il numero di studenti che sono saliti.
 */

#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define MAXN 110

int N, L, squadra[MAXN], answer;

int main()
{
	fin >> N >> L;
	for (int i=0; i<N; i++) {
		fin >> squadra[i];
	}
	for (int s,x,i=0; i<L; i++) {
		fin >> s >> x;
		squadra[s] -= x;
	}
	for (int i=0; i<N; i++) {
		answer += (squadra[i] > 0);
    }
	fout << answer << "\n";
	for (int i=0; i<N; i++) {
		if (squadra[i] > 0)
			fout << i << " " << squadra[i] << "\n";
	}
	return 0;
}
