/*

Giovanni Paolini

Soluzione per salta

*/

#include <cstdio>

using namespace std;

const int MAXN = 1000005;

int n;
int v[MAXN];
bool visitato[MAXN];
int nummancanti;

void leggi() {
	scanf("%d",&n);
	for (int i=1; i<=n; ++i) {
		scanf("%d",v+i);
	}
	nummancanti = n;
}

void risolvi() {
	int pos = 1;
	while ( !visitato[pos] ) {
		visitato[pos] = 1;
		nummancanti--;
		pos = ( pos + v[pos] ) % n + 1;
	}
	
	if (nummancanti == 0) {
		fprintf(stderr, "Molto male, l'input non soddisfa i requisiti");
	}
	printf("%d\n",nummancanti);
	for (int i=1; i<=n; ++i) {
		if (!visitato[i]) {
			nummancanti--;
			printf("%d",i);
			if ( nummancanti > 0 ) printf(" ");
		}
	}
	printf("\n");
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
