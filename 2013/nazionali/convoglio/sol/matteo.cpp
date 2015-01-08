#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>
#include<list>

using namespace std;

int N, M;

// Lista di adiacenza per i soli nodi a destra, con destinazione
// i nodi a sinistra.
vector<vector<int> > adjlist;
// Il matching suggerito.
vector<int> match;

// Vettore dei visitati per la DFS.
vector<bool> visited;

vector<bool> is_ancestor;
#define NO_CYCLE 0
#define CYCLE_FOUND 1
#define CYCLE_ENDED 2

// Stato della ricerca del ciclo
int status = NO_CYCLE;
int cycle_root = 0;

void dfs(int current) {
    visited[current] = true;
    is_ancestor[current]=true;
    int matched = match[current];
    for(vector<int>::iterator it = adjlist[matched].begin();
        it != adjlist[matched].end(); it++) {
        if(*it != current) {
            if(visited[*it] && is_ancestor[*it]) {
                //fprintf(stderr, "ciclo con %d -> %d ...%d\n", current, matched, *it);
                status = CYCLE_FOUND;
                cycle_root = *it;
                match[*it] = matched;
                return;
            }
            if(!visited[*it]) {
                dfs(*it);
                if(status == CYCLE_FOUND) {
                    match[*it] = matched;
                    if(cycle_root == current)
                        status = CYCLE_ENDED;
                    return;
                }
                if(status == CYCLE_ENDED)
                    return;
            }
        }
    }
    is_ancestor[current]=false;
}

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif 

int main() {
    in >> N >> M;
    adjlist.resize(N);
    match.resize(N);
    visited.resize(N, false);
    is_ancestor.resize(N, false);
    for(int i=0;i<M;i++) {
        int src, dst;
        in >> src >> dst;
        if(i<N)
            match[src] = dst;
        else
            adjlist[dst].push_back(src);
    }

    for(int i=0;i<N;i++) {
        if(!visited[i])
            dfs(i);
        if(status == CYCLE_ENDED)
            break;
    }

    if(status == NO_CYCLE)
      out << -1 << endl;
    else {
        for(int i=0;i<N;i++) {
            out << i << " " << match[i] << "\n";
        }
        out << endl;
    }
    return 0;
}
