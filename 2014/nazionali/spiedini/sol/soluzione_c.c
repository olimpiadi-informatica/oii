int ze, se, zb, sb, i;
int solve(int N, int K, int s[]){
    for(i=0; i<N; i++){
        if(!s[i]) ze++;
        se += s[i];
    }
    int p1 = 0;
    int p2 = 0;
    int res = 0;
    while(p1<N){
        while(p2<N && se+sb>K){
            if(!s[p2]) ze--;
            se -= s[p2++];
        }
        if(p2 == N && se+sb>K) break;
        if(p1<=p2 && ze+zb>res) res = ze+zb;
        if(!s[p1]) zb++;
        sb += s[p1++];
    }
    return res;
}
