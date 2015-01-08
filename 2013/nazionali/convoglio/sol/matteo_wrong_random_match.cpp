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

int N, M;

vector<int> random_match;

int main() {
    srand(42);
    in >> N >> M;
    random_match.resize(N);
    for(int i=0;i<N;i++) {
        random_match[i] = i;
    }

    for(int i=0;i<N-1;i++) {
        int tmp = random_match[i];
        int dest = i + rand() % (N-i);
        random_match[i] = random_match[dest];
        random_match[dest] = tmp;
        out << i << " " << random_match[i] << endl;
    }
    out << N-1 << " " << random_match[N-1] << endl;
    return 0;
}
