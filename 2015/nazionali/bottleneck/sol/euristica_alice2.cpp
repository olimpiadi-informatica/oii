#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXM = 1000000;
const int MAXN = 100000;
const int INF = 1000000001;

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int R, int C) {
	int m = capacita[0];
	
	for (int i=1; i<M; i++)
		m = min(m, capacita[i]);
		
	return m;
}
