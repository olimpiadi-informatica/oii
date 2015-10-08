#include<iostream>
using namespace std;

void pianifica(int R, int A[], int B[], int T[]) {
	T[0] = A[0];
	int d= ( B[1]-A[0] )+1;
	bool invalid = true;
	while(invalid) {
		d--;
		invalid=false;
		for(int i=1;i<R;i++) {
			T[i] = T[i-1]+d;
			if (T[i] < A[i])
				T[i] = A[i];
			if (T[i] > B[i]) {
				invalid=true;
				break;
			}
		}
	}
}
