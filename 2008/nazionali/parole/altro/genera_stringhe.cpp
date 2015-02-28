#include<stdlib.h>
#include<stdio.h>

#define MAXN 64
char A[MAXN];
int N;

void bgen( int b ){
	int i;
	if (b == 0){
		for (i=0; i< N; i++)
			printf("%c", A[i]);
		printf("\n"); 
	} else {
		A[b-1] = '0';
		bgen( b-1 );
		A[b-1] = '1';
		bgen( b-1 );
	}
}

int main(int argc, char *argv[]){
	

	N = atoi(argv[1]);
	bgen( N );
	return 0;
}
