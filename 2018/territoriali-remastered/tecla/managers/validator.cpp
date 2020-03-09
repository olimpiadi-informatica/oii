#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50, "t");
    inf.readEoln();

    while (T--) {
	    int n = inf.readInt(1, 30, "n");
	    inf.readSpace();
	    int m = inf.readInt(1, 100, "m");
	    inf.readEoln();

	    set<pair<int, int>> edges;

	    for (int i=0; i<m; i++) {
		int a = inf.readInt(0, n - 1, "a_i");
		inf.readSpace();
		int b = inf.readInt(0, n - 1, "b_i");
		inf.readEoln();

		ensuref(a != b, "Graph can't contain self-loops");
		ensuref(edges.count({a, b}) == 0, "Graph can't contain multiple edges between a pair of vertices");

		edges.insert({a, b});
	    }
    }

    inf.readEof();
}
