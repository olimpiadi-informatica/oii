#include <cstdio>
#include <cctype>
#include <fstream>
using namespace std;
#define MAXS 1000
#define MAXC 1000
#define MAXN 1000
char **din;
int **st;
int **pt;
int *nastro;
int N,C,S;
bool dfs(int n,int s){
	if(n==0) return true;
	if(din[n][s]) return din[n][s]==1;
	din[n][s]=2;
	if(dfs(n+pt[nastro[n]][s],st[nastro[n]][s])){
		din[n][s]=1;
		return true;
	}
	return false;
}
int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");
  
    in >> N >> S >> C;
	din=new char*[N];
	st=new int*[C];
	pt=new int*[C];
	nastro=new int[N];
	for(int i=0;i<N;i++) din[i]=new char[S];
	for(int i=0;i<C;i++) st[i]=new int[S];
	for(int i=0;i<C;i++) pt[i]=new int[S];
	for(int i=0;i<S*C;i++){
		int a,b,c,d;
        in >> a >> b >> c >> d;
		st[b][a]=c;
		pt[b][a]=d;
	}
	for(int i=0;i<N;i++) in >> nastro[i];
	for(int i=0;i<S;i++) din[0][i]=1;
	for(int i=0;i<N;i++) dfs(i,0);
	int cnt=0;
	for(int i=0;i<N;i++) if(din[i][0]==1) cnt++;
    out << cnt << "\n";
	for(int i=0;i<N;i++) if(din[i][0]==1) out << i << "\n";
}
