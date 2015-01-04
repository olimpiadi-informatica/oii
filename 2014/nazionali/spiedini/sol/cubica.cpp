int solve(int N, int K, int s[]){
    int res = 0;
    for(int i=0; i<N; i++)
        for(int j=i; j<=N; j++){
            int K_ = 0;
            for(int k=0; k<i; k++) K_ += s[k];
            for(int k=j; k<N; k++) K_ += s[k];
            if(K_>K) continue;
            int zc = 0;
            for(int k=0; k<i; k++) if(!s[k]) zc++;
            for(int k=j; k<N; k++) if(!s[k]) zc++;
            if(zc>res) res = zc;
        }
    return res;
}
