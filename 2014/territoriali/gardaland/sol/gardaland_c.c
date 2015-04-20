/*
 * Autore: Luca Versari <veluca93@gmail.com>
 * L’idea e’ di mantenere un array, nella cui posizione i-esima
 * teniamo il numero di atleti di cui la squadra i-esima e’ composta.
 * Man mano che otteniamo informazioni sugli studenti che sono gia’
 * saliti sui pulman, decrementiamo in modo opportuno e dalla
 * posizione opportuna il numero di studenti che sono saliti.
 */
#include <stdio.h>
#define MAXN 110

int npers[MAXN];
int N, L, ans, i, a, b;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d", &N, &L);
    ans = N;
    for(i=0; i<N; i++)
        scanf("%d", &npers[i]);
    for(i=0; i<L; i++){
        scanf("%d%d", &a, &b);
        npers[a] -= b;
        if(npers[a] == 0) ans--;
    }
    printf("%d\n", ans);
    for(i=0; i<N; i++)
        if(npers[i])
            printf("%d %d\n", i, npers[i]);
    return 0;
}
