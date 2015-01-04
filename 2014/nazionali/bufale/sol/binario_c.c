long long solve(int N, int M[], int P[]){
    long long tot = 0;
    long long l = 0;
    int cm = 0;
    int cp = 0;
    int i;
    for(i=0; i<N; i++){
        if(cm >= N/2){
            tot += P[i];
            continue;
        }
        if(cp >= N/2){
            tot += M[i];
            continue;
        }
        if(M[i] == 1 && P[i] == 0){
            cm++;
            tot++;
        }
        else if(M[i] == 0 && P[i] == 1){
            cp++;
            tot++;
        }
        else l += M[i];
    }
    return l+tot;
}
