/*

Giovanni Paolini

Soluzione (pesantemente buggata) per fibstr

Guarda le sottostringhe composte solo da due caratteri diversi e conta quante volte compare ciascuno dei due caratteri. Se si tratta di due numeri di Fibonacci consecutivi, allora assume che la stringa sia di Fibonacci.
Complessità: N^2 * log(N). [Il log(N) esiste per mia pigrizia; inoltre si puo' scendere ancora di piu' usando la programmazione dinamica, ma a quel punto e' piu' facile scrivere la soluzione giusta.]

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

int soli,solj; // soluzione temporanea


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
	
	for (int i=0; i<n; ++i) {
		char x = stringa[i];
		
		int j=i+1;
		while ( stringa[j] == stringa[i] && j<n ) j++;
		
		if ( j >= n ) break;
		
		char y = stringa[j];
		
		int numx = j-i;
		int numy = 0;
		
		for (; j<n; ++j) {
			if ( stringa[j] == x ) ++numx;
			else if ( stringa[j] == y ) ++numy;
			else break;
			
			for (int k=0; f[k-1]<=n; ++k) {
				
				if ( ( numy == f[k] && numx == f[k+1] ) && ( numx+numy > solj-soli+1 ) ) {
					soli = i+1;
					solj = j+1;
				}
			}
		}
		
	}
	
	
	
	printf("%d %d\n",soli,solj);
	
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
