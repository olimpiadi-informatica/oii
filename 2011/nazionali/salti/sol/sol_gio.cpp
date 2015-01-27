/*
 * Soluzione di Giovanni per salti
 * Spero non servano commenti...
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

int main() {

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);

	int res = 0;
	while (n != 0) {
		if (n & 1) res++;
		n >>= 1;
	}

	printf("%d\n", res);

	return 0;

}

