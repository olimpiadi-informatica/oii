#include <bits/stdc++.h>

void ex(const char *msg, float res) {
	fprintf(stderr, "%s ", msg);
	printf("%f\n", res);
	exit(0);
}

std::vector<int> altezze;
int N;

bool check()
{
        int needed = 0;
        int covered = 1;

        for (int i=0; i<N; i++) {
                if (needed >= covered)
                	return false;

                covered = std::max(covered, i + altezze[i]);
                needed += 1;
        }
	return true;
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << std::endl;
		return 1;
	}

	// file di input
	std::ifstream fin(argv[1]);
	// output corretto
	std::ifstream fres(argv[2]);
	// output del contestant
	std::ifstream fout(argv[3]);

	if (!fres)
		ex("Can't open jury's output file.", 0.0);
	if (!fout)
		ex("Can't open contestant's output file.", 0.0);

	// leggo il file di input
	fin >> N;
	altezze.resize(N);
	for (int i = 0; i < N; i++)
		fin >> altezze[i];

	// leggo file di output del contestant
	std::string out;
	std::getline(fout, out);

	// leggo file di output corretto
	std::string res;
	std::getline(fres, res);

	if (out == "OK") {
		if (check()) {
			ex("Output is correct", 1.0);
		} else {
			ex("Output isn't correct", 0.0);
		}
	} else if (out == "IMPOSSIBILE") {
		if (res == "IMPOSSIBILE") {
			ex("Output is correct", 1.0);
		} else {
			ex("Output isn't correct", 0.0);
		}
	} else {
        if (check()) ex("Output isn't correct", 0.0);
		std::stringstream ss_out(out);

		int a, b;
		ss_out >> a >> b;

		if (ss_out.fail())
			ex("Malformed output", 0.0);

		if( a == b )
			ex("You're trying to swap a tile with itself", 0.0);

		if( a >= N || b >= N || a < 0 || b < 0 )
			ex("Tile indices out of range", 0.0);

		std::swap(altezze[a], altezze[b]);

		if (check()) {
			if (res == "IMPOSSIBILE")
				ex("Contattare lo staff", 0.0);
			ex("Output is correct", 1.0);
		} else {
			ex("The swap didn't fix the domino chain", 0.0);
		}
	}
}
