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

int main() {
    out << -1 << endl;
    return 0;
}
