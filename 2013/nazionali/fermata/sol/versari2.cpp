#include <cstdio>
#include <cstring>
using namespace std;
#define MAXS 1000
#define MAXC 1000
#define MAXN 1000
char *din;
int *st;
int *pt;
int *nastro;
int N,C,S;
bool dfs(int n,int s){
	if(n==0) return true;
	if(din[n * S + s]) return din[n * S + s]==1;
	din[n * S + s]=2;
	if(dfs(n+pt[nastro[n] * S + s],st[nastro[n] * S + s])){
		din[n * S + s]=1;
		return true;
	}
	return false;
}
int main(){
#ifdef EVAL
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	scanf("%d%d%d",&N,&S,&C);
	din=new char[N * S];
    memset(din, 0, sizeof(char) * (N * S));
	st=new int[C * S];
	pt=new int[C * S];
	nastro=new int[N];
	for(int i=0;i<S*C;i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		st[b * S + a]=c;
		pt[b * S + a]=d;
	}
	for(int i=0;i<N;i++) scanf("%d",nastro+i);
	for(int i=0;i<S;i++) din[0 * S + i]=1;
	for(int i=0;i<N;i++) dfs(i,0);
	int cnt=0;
	for(int i=0;i<N;i++) if(din[i * S + 0]==1) cnt++;
	printf("%d\n",cnt);
	for(int i=0;i<N;i++) if(din[i * S + 0]==1) printf("%d\n",i);
}
