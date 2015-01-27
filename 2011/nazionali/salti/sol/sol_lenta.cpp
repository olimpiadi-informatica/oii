/*
 * Soluzione lenta di Giovanni per salti
 * Brute-force su tutte le possibili combinazioni di salti, argh...
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

int n;
bool salti[30];

int somma() {

	int res = 0;
	for (int i = 0; i < 30; i++) {
		if (salti[i]) res++;
	}
	return res;

}

int valore() {

	int res = 0;
	int tmp = 1;
	for (int i = 0; i < 30; i++) {
		if (salti[i]) res += tmp;
		tmp *= 2;
	}
	return res;

}

void genera(int k = 29) {

	if (k == -1) {
		if (valore() == n) {
			printf("%d\n", somma());
			exit(0);
		}
		return;
	}

	genera(k-1);
	salti[k] = true;
	genera(k-1);
	salti[k] = false;

}

int main() {

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	scanf("%d", &n);
	genera();
	return 0;

}

