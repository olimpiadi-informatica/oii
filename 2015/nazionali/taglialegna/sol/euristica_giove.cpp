#include <iostream>

using namespace std;

void Abbatti(int, int);

int const MAXN = 2000001;

int lep[MAXN];  // fissato i, lep[i] contiene l'indice dell'albero più a sinistra
			    // distrutto dall'abbattimento di i
int rep[MAXN];  // fissato i, rep[i] contiene l'indice dell'albero più a destra
			    // distrutto dall'abbattimento di i


int f(int l, int r, bool act) {
	if (l >= r)
		return 0;
    
	int max_left = l, max_right = l;

	for (int i = l; i < r; i++)
		if (i - lep[i] > max_left - lep[max_left])
			max_left = i;
	for (int i = l; i < r; i++)
		if (rep[i] - i > rep[max_right] - max_right)
			max_right = i;
    
    int a = max_left - lep[max_left];
    int b = rep[max_right] - max_right;
    
    if ( a == b && act ) {
        int x = f(l, lep[max_left], false) + f(max_left + 1, r, false);
        int y = f(l, max_right, false) + f(rep[max_right] + 1, r, false);
        
        if ( x < y ) a++;
        else b++;
    }
    
	if ( a > b ) {
		if (act) Abbatti(max_left, 0);
		return f(l, lep[max_left], act) + f(max_left + 1, r, act);
	} else {
		if (act) Abbatti(max_right, 1);
		return f(l, max_right, act) + f(rep[max_right] + 1, r, act);
	}
}

void Pianifica(int N, int *H) {
	lep[0] = 0;
	for (int i = 1; i < N; i++) {
		int j = i-1;
		while (j >= 0 && i - j < H[i])
			j = lep[j] - 1;
		lep[i] = j + 1;
	}

	rep[N-1] = N-1;
	for (int i = N-2; i >= 0; i--) {
		int j = i + 1;
		while (j < N && j - i < H[i])
			j = rep[j] + 1;
		rep[i] = j - 1;
	}

	f(0, N, true);
}
