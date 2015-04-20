#include <fstream>
#include <iostream>

using namespace std;

#ifdef EVAL
ifstream fin("input.txt");
ofstream fout("output.txt");
#else
istream &fin(cin);
ostream &fout(cout);
#endif

#define MAXN 110

int N, L, squadra[MAXN], answer;

int main()
{
	fin >> N >> L;
	for (int i=0; i<N; i++) {
		fin >> squadra[i];
	}
	for (int s,x,i=0; i<L; i++) {
		fin >> s >> x;
		squadra[s] -= x;
	}
	for (int i=0; i<N; i++) {
		answer += (squadra[i] > 0);
    }
	fout << answer << "\n";
	for (int i=0; i<N; i++) {
		if (squadra[i] > 0)
			fout << i << " " << squadra[i] << "\n";
	}
	return 0;
}
