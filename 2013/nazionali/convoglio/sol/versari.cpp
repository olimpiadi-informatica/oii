#include <cstdio>
#include <vector>
using namespace std;
vector<int> graph[200000];
int N,M;
int daddies[200000];
bool isancestor[200000];
vector<int> cycle;
int new_match[100000];
int dfs(int n,int d){
	if(daddies[n]){
		if(isancestor[n]){
			cycle.push_back(n);
			int t=d;
			cycle.push_back(t);
			while(t!=n){
				t=daddies[t]-1;
				cycle.push_back(t);
			}
			return true;
		}
		else return false;
	}
	daddies[n]=d+1;
	isancestor[n]=true;
	for(unsigned i=0;i<graph[n].size();i++)
		if(graph[n][i]!=d && dfs(graph[n][i],n))
			return true;
	isancestor[n]=false;
	return false;
}
int main(){
#ifdef EVAL
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		b+=N;
		if(i<N) graph[a].push_back(b);
		else graph[b].push_back(a);
	}
	for(int i=0;i<2*N;i++){
		while(daddies[i] && i<N) i++;
		if(i==N) break;
		if(dfs(i,-2)){
			for(unsigned i=1;i<cycle.size();i++)
				if(cycle[i-1]<N)
					new_match[cycle[i-1]]=cycle[i];
			for(int i=0;i<N;i++)
				if(!new_match[i])
					new_match[i]=graph[i][0];
			for(int i=0;i<N;i++) printf("%d %d\n",i,new_match[i]-N);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
