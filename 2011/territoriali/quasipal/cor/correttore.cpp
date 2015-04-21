/*
	Matteo Boscariol - 20/3/2010
	Correttore del problema "quasipal"
	
	Complessità stimata O(n^2)

	fase 1: Controlla che le colonne siano quasi palindrome	
	fase 2: Ordina le stringhe di input e output per
	controllare che siano le stesse.
*/

#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<string>
#include<algorithm>

#define MAXN 8
#define MAXM 8

using namespace std;

int n=0,m=0;
string originale[MAXM];
string elaborato[MAXM];


void ex( const char *msg, float res );

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		fprintf(stderr,"Usage: %s <input> <output> <test_output>\n", argv[0]);
		exit(1);
	}
	
	ifstream input,test;
	input.open(argv[1],ios::in);
	test.open(argv[3],ios::in);
	

	if(!input.is_open() || !test.is_open())
	{
		fprintf(stderr,"Impossibile aprire alcuni file per la correzione\n");
		exit(1);
	}
	
	input>>m>>n;

	for(int i=0;i<m;i++)
	{
		input>>originale[i];
		test>>elaborato[i];
		//printf("%d\n",i);
		if(elaborato[i].length()!=n) ex("Risposta errata (lunghezza errata).",0.0);
	}
	input.close();
	test.close();
	
	//controllo che le colonne siano quasi palindrome
	for(int i=0;i<(m+1)/2;i++)
		for(int j=0;j<n;j++)
		{
			if(!(elaborato[i][j]==elaborato[m-1-i][j] || elaborato[i][j]=='0' || elaborato[m-1-i][j]=='0'))
				ex("Risposta errata (stringhe non palindrome).",0.0);
		}
	//controllo che i due input siano costituiti dalle stesse stringhe
	sort(elaborato, elaborato + m);
	sort(originale, originale + m);
	for(int i=0;i<m;i++)
		if(elaborato[i].compare(originale[i]) !=0)
			ex("Risposta errata (stringhe diverse).",0.0);
	ex("Risposta corretta.",1.0);
	return 0;
}

void ex( const char *msg, float res )
{
  if( msg ) {
    fprintf( stderr, "[\x1b[1m\x1b[31m%s\x1b[m] ", msg );
  }
  printf( "%f\n", res );
  exit( 0 );
}
