/*
 *  Soluzione di lungomare.
 *
 *  Autore: Giada Franz tradotta in C da Giorgio Audrito
 *
 *  Descrizione: come soluzione_giada.
 * 
 */

#define MAXN 10240000

long long risolvi[MAXN][2];
int len = 0;

inline void push(long long a, long long b) {
    risolvi[len][0] = a;
    risolvi[len][1] = b;
    len++;
}

inline long long* top() {
    return risolvi[len-1];
}

inline void pop() {
    len--;
}

long long percorri(int N, long long L, long long D[], long long P[]) {
    // (P+D, P-D)
    push(L, -L);
    
    for (int i = N-1; i >= 0; i--) {
        int fatto = 0;
        while (fatto == 0) {
            if (P[i] + D[i] >= top()[0] && P[i] - D[i] >= top()[1]) fatto = 1;
            else if (P[i] + D[i] <= top()[0] && P[i] - D[i] <= top()[1]) {
                pop();
            }
            else {
                push(P[i] + D[i], P[i] - D[i]);
                fatto = 1;
            }
        }
    }
    
    while (top()[1] >= 0) pop();
    push(0, 0);
    
    long long res = 0, prec[2], at[2];
    prec[0] = top()[0];
    prec[1] = top()[1];
    pop();
    
    while (len) {
        at[0] = top()[0];
        at[1] = top()[1];
        pop();
        if (res < at[0] + prec[1]) res = at[0] + prec[1];
        prec[0] = at[0];
        prec[1] = at[1];
    }
    return res;
}

