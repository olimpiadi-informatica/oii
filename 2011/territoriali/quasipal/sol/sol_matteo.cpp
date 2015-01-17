/*
	Matteo Boscariol - 17/3/2010
	Soluzione al problema "quasipal"
*/

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<algorithm>
#define MAXN 9
#define MAXM 9

using namespace std;


int n=0,m=0;

//rettangolo quasipal permutato:
char rettangolo[MAXM][MAXN+1];

int permutation[MAXN];

int main()
{
		
    #ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    FILE *fin = stdin, *fout = stdout;
	fscanf(fin,"%d %d",&m,&n);
	for(int i=0;i<m;i++)
	{
		fscanf(fin,"%s",rettangolo[i]);
		permutation[i]=i;
	}
	fclose(fin);
	
	bool quasipal;
	do
	{
		quasipal=true;
		for(int i=0;i<(m+1)/2 && quasipal;i++)
		{
			int curr_row=permutation[i];
			int oppo_row=permutation[m-1-i];
			for(int j=0;j<n && quasipal;j++)
				if(rettangolo[curr_row][j]!=rettangolo[oppo_row][j] && rettangolo[curr_row][j]!='0' && rettangolo[oppo_row][j]!='0')
					quasipal=false;
		}
//		printf("qui\n");
	}
	while(!quasipal && next_permutation(permutation,permutation+m));	
	
	for(int i=0;i<m;i++)
		fprintf(fout,"%s\n",rettangolo[permutation[i]]);
	return 0;
}
