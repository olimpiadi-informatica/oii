/*
 *
 *
 *
 *
 *
 */

#define MAXN 1000000

#include<vector>
#include<iostream>
#include<cassert>

using namespace std;

void nuovo_gruppo();
void aggiungi(int bambino);

int* enemy;
vector<int> visit_parity(MAXN,-1);
vector<int> assigned_group(MAXN,-1);

int ngroups = 2;

void visit(int curr) {
	int next = enemy[curr];
	cerr << curr << endl;
	assert(next!=curr);

	// The next node already has a group, assign the opposite group to the current one.
	if(assigned_group[next] >= 0) {
		assigned_group[curr] = (assigned_group[next]==0?1:0);
		assert(assigned_group[curr] != assigned_group[next]);
		return;
	}

	// The next node does not have a group but it has been visited.
	// Thus we're in a loop: determine the length parity and assign a group accordingly.
	if(visit_parity[next]>=0) {

		if(visit_parity[next]==visit_parity[curr]) {
			assigned_group[curr]=2;
			ngroups=3;
			// cerr << assigned_group[curr] << " -> " << assigned_group[next] << endl;
			assert(assigned_group[curr] != assigned_group[next]);
		}
		else {
			assigned_group[curr]=1;
			assert(assigned_group[curr] != assigned_group[next]);
		}
		return;
	}

	// The next node has not been visited. Set the parity, visit, then determine this node's group.
	visit_parity[next] = 1^visit_parity[curr];
	visit(next);
	assigned_group[curr] = (assigned_group[next]==0?1:0);
	assert(assigned_group[curr] != assigned_group[next]);
}


void smista(int N, int nemico[]) {
	enemy=nemico;
	for(int i=0;i<N;i++)
		cout << enemy[i] << " ";
	cout << endl;

	for(int i=0;i<N;i++)
		if(visit_parity[i]==-1) {
			visit_parity[i] = 0;
			visit(i);
		}

	for(int group=0;group<ngroups;group++) {
		nuovo_gruppo();
		for(int i=0;i<N;i++)
			if(assigned_group[i] == group)
				aggiungi(i);
	}
}
