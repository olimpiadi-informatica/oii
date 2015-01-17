/*
	Matteo Boscariol - 17/3/2010
	Soluzione al problema "sbarramento"
	
	Complessità O(n)
	
	"Sposta" verticalmente tutte le truppe sulla riga
	prescelta, successivamente partendo dalla prima cella 
	della riga, calcola la differenza di unità nella
	cella rispetto al numero atteso (ovvero 1) e aggiunge
	il suo modulo al costo. Se la differenza non è 0,
	aggiunge la differenza alla cella successiva (simula
	uno spostamento di truppe a destra se è positiva, 
	a sinistra se è negativa).
*/

#include<cstdio>
#include<cstdlib>
#include<cassert>
#define MAXN 501

using namespace std;


int n=0,r=0;
int cost=0;

//numero di truppe nella colonna specificata.
int truppe_col[MAXN];

int main()
{
	for(int i=0;i<MAXN;i++)
		truppe_col[i]=0;
		
	FILE *fin,*fout;
	fin=fopen("input.txt","r");
	fscanf(fin,"%d %d",&n,&r);
	for(int i=0;i<n;i++)
	{
		int i_row,i_col;
		fscanf(fin,"%d %d",&i_row,&i_col);
		cost+=abs(i_row-r);
		truppe_col[i_col]++;
	}
	fclose(fin);
	
	for(int i=1;i<=n;i++)
	{
		int var=truppe_col[i]-1;
		cost+=abs(var);
		if(i<n)
			truppe_col[i+1]+=var;
		else assert(var==0);
	}
	
	fout=fopen("output.txt","w");
	fprintf(fout,"%d\n",cost);
	fclose(fout);
	return 0;
}
