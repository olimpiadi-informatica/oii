/*
    Backtracking dei possibili match.
*/

#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif 

// Lista di adiacenza dai nodi a sx ai nodi a dx
vector<vector<int> > adjlist;
vector<int> match;
vector<int> current_match;
vector<bool> picked;
bool different_match_found = false;

int N, M;

void bt(int current) {
    if(current == N) {
        for(int i=0;i<N;i++)
            if(match[i] != current_match[i]) {
                different_match_found=true;
                break;
            }
    }
    else {
        for(vector<int>::iterator it = adjlist[current].begin();
            it != adjlist[current].end() && !different_match_found; it++) {
            if(!picked[*it]) {
                current_match[current] = *it;
                picked[*it] = true;
                bt(current+1);
                picked[*it] = false;
            }
        }
    }
}

int main() {
    in >> N >> M;
    adjlist.resize(N);
    match.resize(N);
    current_match.resize(N);
    picked.resize(N, false);
    for(int i=0;i<M;i++) {
        int src, dst;
        in >> src >> dst;
        adjlist[src].push_back(dst);
        if(i<N)
            match[src] = dst;
    }

    bt(0);

    if(!different_match_found)
      out << -1 << endl;
    else {
        for(int i=0;i<N;i++) {
            out << i << " " << current_match[i] << endl;
        }
    }
    return 0;
}
