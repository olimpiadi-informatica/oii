/*

Giovanni Paolini


Soluzione per fibstr

Programmazione dinamica: il sottoproblema (i,k) consiste nel dire se la sottostringa [ i, i+f[k] ) e' buona (f[k] e' il k-esimo numero di fibonacci).

*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 1000002;
const int MAXL = 100;

int n;
char stringa[MAXN];
int f[MAXL]; // numeri di fibonacci

int soli,solj,solk; // soluzione temporanea

pair<char,char> analisi[MAXN][3]; // analisi[i][l%3] dice se la stringa da [i,i+f[l]) e' di Fibonacci (nel qual caso scrive i due simboli) o se non lo e' (nel qual caso scrive pair(0,0))

void leggi() {
	scanf("%d\n",&n);
	
	for (int i=0; i<n; ++i) {
		stringa[i] = getchar();
	}
}

void calcola_fibonacci() {
	f[0] = 1;
	f[1] = 1;
	
	for (int i=2; f[i-1]<=n; ++i) {
		f[i] = f[i-1] + f[i-2];
	}

}

void risolvi() {
	calcola_fibonacci();
	
	soli = 1;
	solj = 1;
	solk = 1;
	
	// Passi base k=2, k=3
	for (int i=0; i+1<n; ++i) {
		if ( stringa[i] != stringa[i+1] ) {
			analisi[i][2] = pair<char,char>(stringa[i],stringa[i+1]);
			if ( solk < 2 ) {
				soli = i;
				solj = i+1;
				solk = 2;
			}
		}
		else {
			analisi[i][2] = pair<char,char>(0,0);
		}
	}
	
	for (int i=0; i+2<n; ++i) {
		if ( stringa[i] == stringa[i+2] && stringa[i] != stringa[i+1] ) {
			analisi[i][0] = pair<char,char>(stringa[i],stringa[i+1]);
			if ( solk<3 ) {
				soli = i;
				solj = i+2;
				solk = 3;
			}
		}
		else {
			analisi[i][0] = pair<char,char>(0,0);
		}
	}
	
	// Ricorsione
	for (int k=4; f[k]<=n; ++k) {
		int x = f[k-2];
		int y = f[k-1];
		int z = f[k];
		
		for (int i=0; i+z-1<n; ++i) {
			if ( analisi[i][(k-1)%3] == analisi[i+y][(k-2)%3] ) {
				analisi[i][k%3] = analisi[i][(k-1)%3];
				if ( ( analisi[i][k%3] != pair<char,char>(0,0) ) && ( solk < k ) ) {
					soli = i;
					solj = i+z-1;
					solk = k;
				}
			}
			else {
				analisi[i][k%3] = pair<char,char>(0,0);
			}
		}
		
	}
	
	printf("%d %d\n",soli+1,solj+1);
	
	// Quella che segue e' la stampa della sottostringa che risolve
	/*
	for (int i=soli-1; i<=solj-1; ++i) {
		printf("%c",stringa[i]);
	}
	printf("\n");
	*/
}


int main() {
	
	#ifdef EVAL
	  freopen("input.txt", "r", stdin);
	  freopen("output.txt", "w", stdout);
	#endif
	
	leggi();
	risolvi();
	
	return 0;
}
