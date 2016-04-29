#include <cstdio>
#include <cassert>
#include <algorithm>

int main() {
    FILE *fr, *fw;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    int G, P;
    assert(2 == fscanf(fr, "%d%d", &G, &P));
    P--;

    int toto = 0;
    for (int i = 1; G > 0; i++) {
        // toto
        toto += std::min(i, G);
        G -= i;

        // complici
        G -= P;
    }

    fprintf(fw, "%d\n", toto);
    fclose(fr);
    fclose(fw);
    return 0;
}
