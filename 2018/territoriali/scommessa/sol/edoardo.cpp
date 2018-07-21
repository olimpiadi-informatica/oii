#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 150;

int nums[MAX_N];
int parity[MAX_N];
// unibili finendo ad i-1 se prefix[i] == 0
int prefix[MAX_N];
// unibili partendo da i+1 se suffix[i] == 0
int suffix[MAX_N];

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	int N;
	in >> N;
	
	for (int i = 0; i < N; i++) {
		in >> nums[i];
		parity[i] = (nums[i] % 2 == 0) ? 1 : -1;
	}

	for (int i = 0; i < N-1; i++)
		prefix[i+1] = prefix[i]+parity[i];
	for (int i = N-1; i >= 1; i--)
		suffix[i-1] = suffix[i]+parity[i];

	vector<int> sol;
	for (int i = 0; i < N; i++)
		if (prefix[i] == 0 && suffix[i] == 0)
			sol.push_back(nums[i]);

	out << sol.size() << endl;
	for (int n : sol)
		out << n << ' ';
	out << endl;
}
