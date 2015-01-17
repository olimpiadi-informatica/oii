/*
	Matteo Boscariol - 17/3/2010
	Soluzione molto lenta al problema "sbarramento"
	(per conferma)
	
	Complessità O(n!)
	
	Per ogni possibile permutazione delle truppe,
	calcola il costo di posizionare le truppe in
	questo ordine sulla riga prescelta, e ne estrae
	il massimo.
*/
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>

#define MAXN 501
using namespace std;

int n,r;

int row[MAXN+1];
int col[MAXN+1];

int col_pos[MAXN+1];

int main()
{
	FILE *fin,*fout;
	fin=fopen("input.txt","r");
	fscanf(fin,"%d %d",&n, &r);
	for (int i=1;i<=n;i++)
	{
		fscanf(fin,"%d %d",row+i,col+i);
		col_pos[i]=i;
	}
	fclose(fin);
	int mincost=INT_MAX;
	
	do
	{
		int currcost=0;
		for(int i=1;i<=n;i++)
			currcost+=abs(row[i]-r)+abs(col[i]-col_pos[i]);
		if(currcost<mincost)
			mincost=currcost;
	}
	while(next_permutation(col_pos+1,col_pos+n+1));
	
	fout = fopen("output.txt","w");
	fprintf(fout,"%d\n",mincost);
	fclose(fout);
	return 0;
}
