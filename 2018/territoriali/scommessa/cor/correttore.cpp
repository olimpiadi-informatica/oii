#include <set>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cstring>

using namespace std;

void err(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void ex(const char *msg, float res) {
    if(msg)
        fprintf(stderr, "%s ", msg);
    printf("%f\n", res);
    exit(0);
}

int main(int argc, char** argv) {
    if(argc != 4)
        err("Usage: correttore <input> <correct output> <test output>");

    FILE *fin, *fout, *fcor;
    fin = fopen(argv[1], "r");
    fout = fopen(argv[3], "r");
    fcor = fopen(argv[2], "r");
    if(!fin)
        err("Cannot open input file!");
    if(!fout)
        err("Cannot open output file!");
    if(!fcor)
        err("Cannot open correct output file!");

    int N;
    if(fscanf(fout, "%d", &N) != 1)
        ex("Formato errato", 0.0);
    int Ncor;
    if(fscanf(fcor, "%d", &Ncor) != 1)
        err("Correct solution format error");

    if (N != Ncor)
        ex("Errato.", 0.0);

    set<int> nums;
    for (int i = 0; i < N; i++) {
        int n;
        if (fscanf(fout, "%d", &n) != 1)
            ex("Formato errato", 0.0);
        nums.insert(n);
    }

    set<int> cor;
    for (int i = 0; i < Ncor; i++) {
        int n;
        if (fscanf(fcor, "%d", &n) != 1)
            err("Correct solution format error");
        cor.insert(n);
    }

    if (cor == nums)
        ex("Corretto.", 1.0);
    else
        ex("Errato.", 0.0);
}
