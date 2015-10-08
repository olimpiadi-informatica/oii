

#define MAXN 1000000

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>
using namespace std;

void nuovo_gruppo();
void aggiungi(int bambino);


void smista(int N, int nemici[]) {
	vector<int> gruppo(N,-1);
	int max_groups = 2;
	for(int i=0;i<N;i++) {
		int prev_group = -1;
		for(int cur = i; gruppo[cur] == -1;  prev_group = gruppo[cur], cur = nemici[cur]) {
			gruppo[cur] = 0;
			while (gruppo[nemici[cur]] == gruppo[cur] || prev_group == gruppo[cur])
				++(gruppo[cur]);
			max_groups = max(gruppo[cur]+1, max_groups);
			//cerr << cur << ": " << gruppo[cur] << endl;
		}
	}

	for(int g=0;g<max_groups;g++) {
		nuovo_gruppo();
		for(int i=0;i<N;i++)
			if(gruppo[i] == g)
				aggiungi(i);
	}
}
