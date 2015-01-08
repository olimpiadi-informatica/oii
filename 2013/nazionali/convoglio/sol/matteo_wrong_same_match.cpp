#include<cstdlib>
#include<iostream>
#include<fstream>

using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif 

int N, M;

int main() {
    in >> N >> M;
    for(int i=0;i<N;i++) {
        int src, dst;
        in >> src >> dst;
        out << src << " " << dst << endl;
    }
    return 0;
}
