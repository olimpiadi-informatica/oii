/**
 *  Autore: Nessuno
 */

#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <cstring>

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


const int MAX_FIB = 35;
int fib[MAX_FIB];

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
    if(fscanf(fin, "%d", &N) != 1)
        err("Input format error");

    char str[1024];
    if (NULL == fgets(str, 1024, fout))
        ex("Formato non valido.", 0.0);

    // NOTE: strlen will also counts the spaces
    int len = strlen(str);
    if (len == 0)
        ex("Formato non valido.", 0.0);


    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < MAX_FIB; i++)
        fib[i] = fib[i-1]+fib[i-2];

    int sum = 0;
    for (int i = 0; i < len; i++) {
        // if the string is tooo long
        if (i >= MAX_FIB && (str[i] == '1' || str[i] == '0')) {
            ex("Formato non valido.", 0.0);
        }
        if (str[i] == '1') {
            sum += fib[i];
        } else if (str[i] == '0') {
            sum += 0;
        } else if (isspace(str[i])) {
            // Terminate the input at the first space character. NOTE: if
            // the first word is the solution anything after will be ok
            break;
        }
        else {
            ex("Formato non valido.", 0.0);
        }
    }

    if (sum == N)
        ex("Corretto.", 1.0);
    else
        ex("Errato.", 0.0);
}
