/*
 * Autore: Luca Versari <veluca93@gmail.com>
 *
 * Esegue una ricerca in profondita' per controllare quante attrazioni
 * sono raggiungibili partendo dal nodo 0.
 * Viene passata una mask di bit alla funzione dfs per decidere quali archi
 * usare:
 *   (1) Se il primo bit e' impostato, posso usare gli autobus
 *   (2) Se il secondo bit e' impostato, posso usare i traghetti
 *
 * Quindi ci sono quattro possibilita':
 *   (1) Se m=0, uso solo archi gratuiti
 *   (2) Se m=1, uso archi gratuiti e gli autobus
 *   (3) Se m=2, uso archi gratuiti e i traghetti
 *   (4) Se m=3, uso archi gratuiti, autobus e traghetti
 *
 * Nota: In C++, la struct adj puo' essere sostituita da un vector.
 */
#include <stdio.h>
#include <stdlib.h>
#define MAXN 1010
typedef enum{false, true} bool;

struct adj{
    int size;
    int capacity;
    int* values;
};

void adjInit(struct adj* a){
    a->size = 0;
    a->capacity = 1;
    a->values = malloc(sizeof(int));
}

void adjInsert(struct adj* a, int v){
    if(a->capacity == a->size){
        a->capacity *= 2;
        a->values = realloc(a->values, a->capacity*sizeof(int));
    }
    a->values[a->size++] = v;
}

int N, A, M[3];
struct adj graph[3][MAXN];
bool attr[MAXN];
bool visited[4][MAXN];

int dfs(int n, int m){
    int r, i, j;
    if(visited[m][n]) return 0;
    visited[m][n] = true;
    r = attr[n];
    for(j=0; j<3; j++)
        if((j&m) == j)
            for(i=0; i<graph[j][n].size; i++)
                r += dfs(graph[j][n].values[i], m);
    return r;
}

int main(){
    int i, j, a, b;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d%d%d%d", &N, &A, &M[0], &M[1], &M[2]);
    for(i=0; i<A; i++){
        scanf("%d", &a);
        attr[a] = true;
    }
    for(j=0; j<3; j++){
        for(i=0; i<N; i++) adjInit(&graph[j][i]);
        for(i=0; i<M[j]; i++){
            scanf("%d%d", &a, &b);
            adjInsert(&graph[j][a], b);
            adjInsert(&graph[j][b], a);
        }
    }
    for(i=0; i<4; i++)
        printf("%d\n", dfs(0, i));
    return 0;
}
