/*
 * Autore: William Di Luigi <williamdiluigi@gmail.com>
 *
 * Programmazione dinamica in R*C:
 * dp[i][j] = prossimo indice (0-based) da matchare per "continuare"
 * (i, j) -> (i+1, j) oppure (i, j)  -> (i, j+1)
 */

#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define MAXR 110
#define MAXC 110

int R, C;
string P, M[MAXR];

int dp[MAXR][MAXC], path[MAXR][MAXC];

#define BASSO  1
#define DESTRA 2

int main()
{
	fin >> R >> C;
	fin >> P;
	int L = P.length();
	for (int i=0; i<R; i++) {
		fin >> M[i];
	}
	if (M[0][0] != P[0]) {
		fout << "ASSENTE\n";
		return 0;
	}
	bool trovato = false;
	int ii, jj;
	// Punto di partenza
	dp[0][0] = 1;
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			// Prova a migliorare continuando dall'alto
			if (i > 0 && dp[i-1][j] > 0 && dp[i-1][j] < L && M[i][j] == P[dp[i-1][j]]) {
				if (dp[i][j] < dp[i-1][j] + 1) {
					dp[i][j] = dp[i-1][j] + 1;
					path[i][j] = BASSO;
				}
			}
			// Prova a migliorare continuando da sinistra
			if (j > 0 && dp[i][j-1] > 0 && dp[i][j-1] < L && M[i][j] == P[dp[i][j-1]]) {
				if (dp[i][j] < dp[i][j-1] + 1) {
					dp[i][j] = dp[i][j-1] + 1;
					path[i][j] = DESTRA;
				}
			}
			// Controlla se ho finito
			if (dp[i][j] == L) {
				trovato = true;
				ii = i;
				jj = j;
			}
		}
	}
	if (!trovato) {
		fout << "ASSENTE\n";
		return 0;
	}
	// Ricostruisci i passi fatti
	string answer = "";
	while (ii != 0 || jj != 0) {
		if (path[ii][jj] == BASSO) {
			answer += "B";
			ii --;
		} else if (path[ii][jj] == DESTRA) {
			answer += "D";
			jj --;
		}
	}
	reverse(answer.begin(), answer.end());
	fout << answer << "\n";
	return 0;
}
