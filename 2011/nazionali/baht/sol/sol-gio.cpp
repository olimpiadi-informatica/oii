
/*

Soluzione di Giovanni Mascellani

Utilizzo la stessa tecnica di Stefano (ho scritto qualcosa al proposito nella
sua soluzione), però reimplemento per double check. :-)

*/

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_VAL_NUM = 10000;

int instNum, valNum;
int vals[MAX_VAL_NUM];

int main() {

    assert(scanf("%d", &instNum) == 1); 

	for (int i = 0; i < instNum; i++) {
        assert(scanf("%d", &valNum) == 1);
		for (int j = 0; j < valNum; j++) {
            assert(scanf("%d", &vals[j]) == 1);
		}
		sort(vals, vals+valNum);
		int sum = 0;
		for (int j = 0; j < valNum && sum+1 >= vals[j]; j++) {
			sum += vals[j];
		}
		printf("%d\n", sum+1);
	}

	return 0;

}

