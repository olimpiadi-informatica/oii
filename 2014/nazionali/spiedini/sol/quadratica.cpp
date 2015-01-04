#define MAXN 10000000
int zb[MAXN], ze[MAXN];
int sb[MAXN], se[MAXN];
int solve(int N, int K, int S[]){
    for(int i=1; i<N; i++){
        sb[i] = S[i-1] + sb[i-1];
        zb[i] = (S[i-1]==0) + zb[i-1];
    }
    for(int i=N-1; i>0; i--){
        se[i-1] = S[i] + se[i];
        ze[i-1] = (S[i]==0) + ze[i];
    }
    int res = 0;
    for(int i=0; i<N; i++)
        for(int j=i; j<N; j++){
            if(sb[i]+se[j]>K) continue;
            if(zb[i]+ze[j]>res) res = zb[i]+ze[j];
        }
    return res;
}
