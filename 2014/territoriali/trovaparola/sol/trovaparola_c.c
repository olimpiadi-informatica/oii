/*
 * Autore: Luca Versari <veluca93@gmail.com>
 *
 * La soluzione implementa una visita in profondita' (DFS) per
 * cercare di comporre la parola P partendo dal suo d-esimo
 * carattere, sapendo che ci troviamo in posizione (i, j) nella
 * griglia di lettere. Usiamo l'accortezza di evitare di passare due
 * volte per la stessa cella, dato che la lunghezza di qualsiasi
 * percorso che va da (1, 1) a (i, j) e' sempre uguale, e quindi ci
 * ritroveremmo ogni volta nella stessa cella (i, j) ma con lo stesso
 * indice d da cui "ripartire", e gia' sappiamo che non riusciremo
 * a comporre la parola (se cosi' non fosse l'avremmo trovata prima).
 */
#include <stdio.h>
#define MAXR 100
typedef enum{false, true} bool;

int R, C, i;
char P[2*MAXR];
char grid[MAXR][MAXR+1];
bool vis[MAXR][MAXR];
char ans[2*MAXR];

bool dfs(int r, int c, int d){
    char cur;
    if(r>=R || c>=C) return false;
    if(grid[r][c] != P[d]) return false;
    if(!P[d+1]) return true;
    if(vis[r][c]) return false;
    vis[r][c] = true;
    cur = 0;
    if(dfs(r+1, c, d+1)) cur = 'B';
    if(dfs(r, c+1, d+1)) cur = 'D';
    if(cur) ans[d] = cur;
    return cur;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d", &R, &C);
    scanf("%s", P);
    for(i=0; i<R; i++) scanf("%s", grid[i]);
    printf("%s\n", dfs(0, 0, 0)?ans:"ASSENTE");
    return 0;
}
