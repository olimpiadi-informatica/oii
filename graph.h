#include <vector>
#include <set>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <stdint.h>

#define GRAPH_WEIGHTED_BOTH     3
#define GRAPH_WEIGHTED_VERTICES 2
#define GRAPH_WEIGHTED_EDGES    1
#define GRAPH_UNWEIGHTED        0
#define GRAPH_DIRECTED          1
#define GRAPH_UNDIRECTED        0
#define GRAPH_RANDOM            0
#define GRAPH_CYCLE             1
#define GRAPH_PATH              2
#define GRAPH_TREE              3
#define GRAPH_FOREST            4
#define GRAPH_CLIQUE            5
#define GRAPH_STAR              6
#define GRAPH_WHEEL             7
#define GRAPH_DAG               8
using namespace std;


/*
 *	Tiny Mersenne Twister, used as a 64-bit random number generator.
 *	Copyright (c) 2011 Mutsuo Saito, Makoto Matsumoto, Hiroshima
 *	University and The University of Tokyo. All rights reserved.
 *	http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/TINYMT/LICENSE.txt
 */
#define TINYMT64_MASK 0x7fffffffffffffffULL
#define TINYMT64_SH0 12
#define TINYMT64_SH1 11
#define TINYMT64_SH8 8
#define MIN_LOOP 8

struct TINYMT64_T {
	uint64_t status[2];
	unsigned mat1;
	unsigned mat2;
	uint64_t tmat;
};

typedef struct TINYMT64_T tinymt64_t;
tinymt64_t rnd;
inline static void tinymt64_next_state() {
	uint64_t x;

	rnd.status[0] &= TINYMT64_MASK;
	x = rnd.status[0] ^ rnd.status[1];
	x ^= x << TINYMT64_SH0;
	x ^= x >> 32;
	x ^= x << 32;
	x ^= x << TINYMT64_SH1;
	rnd.status[0] = rnd.status[1];
	rnd.status[1] = x;
	rnd.status[0] ^= -((long long)(x & 1)) & rnd.mat1;
	rnd.status[1] ^= -((long long)(x & 1)) & (((uint64_t)rnd.mat2) << 32);
}

inline static uint64_t tinymt64_temper() {
	uint64_t x;
	x = rnd.status[0] + rnd.status[1];
	x ^= rnd.status[0] >> TINYMT64_SH8;
	x ^= -((long long)(x & 1)) & rnd.tmat;
	return x;
}

inline static uint64_t tinymt64_generate_uint64() {
	tinymt64_next_state();
	return tinymt64_temper();
}
void tinymt64_init(uint64_t seed) {
	rnd.status[0] = seed ^ ((uint64_t)rnd.mat1 << 32);
	rnd.status[1] = rnd.mat2 ^ rnd.tmat;
	int i;
	for (i = 1; i < MIN_LOOP; i++) {
	rnd.status[i & 1] ^= i + 6364136223846793005ULL
		* (rnd.status[(i - 1) & 1]
		   ^ (rnd.status[(i - 1) & 1] >> 62));
	}
	if ((rnd.status[0] & TINYMT64_MASK) == 0 &&
	rnd.status[1] == 0) {
	rnd.status[0] = 'T';
	rnd.status[1] = 'M';
	}
}

/*
 *	Functions to write the output in "standard"/binary format.
 */
#ifdef BINARY_OUTPUT
#define BUFSIZE 8192
int printbuf[BUFSIZE];
#else
#define BUFSIZE 32768
char printbuf[BUFSIZE];
#endif
int printpos;
inline void flush(){
	fwrite(printbuf,sizeof(printbuf[0]),printpos,stdout);
	printpos=0;
}
#ifndef BINARY_OUTPUT
inline void putC(char c){
	if(printpos==BUFSIZE) flush();
	printbuf[printpos++]=c;
}
#endif
inline void printint(int v, char e){
#ifdef BINARY_OUTPUT
	if(printpos==BUFSIZE) flush();
	printbuf[printpos++]=v;
#else
	if(printpos>BUFSIZE-30) flush();
	if(v<0){
		printbuf[printpos++]='-';
		v=-v;
	}
	if(v==0){
		printbuf[printpos++]='0';
		putC(e);
		return;
	}
	int c=0;
	while(v>0){
		int a=v/10;
		printbuf[printpos++]=v-a*10+'0';
		v=a;
		c++;
	}
	for(int i=0;i<c/2;i++)
		swap(printbuf[printpos-i-1],printbuf[printpos-c+i]);
	putC(e);
#endif
}
/*
 * 	Random number functions: randint returns a random integer in the range
 *	[0,i), while randnum returns n distinct random integers in the range
 *	[0,max).
 */
#ifndef USE_RAND
inline uint64_t randint(uint64_t i){ return tinymt64_generate_uint64()%i; }
#else
inline uint64_t randint(uint64_t i){ return ((((unsigned long long)rand())<<31)+rand())%i; }
#endif
vector<uint64_t> randnum(uint64_t max, uint64_t n){
	assert(n<=max);
	vector<uint64_t> res;
	pair<uint64_t,uint64_t> *q;
	uint64_t cnt=0;
	q=new pair<uint64_t,uint64_t>[n+1];
	q[cnt++]=make_pair(0,max);
	while(n>0){
		uint64_t pos=randint(cnt);
		n--;
		uint64_t sel=q[pos].first+randint(q[pos].second-q[pos].first);
		if(sel+1!=q[pos].second)
			q[cnt++]=make_pair(sel+1,q[pos].second);
		if(q[pos].first==sel){
			cnt--;
			q[pos].second=q[cnt].second;
			q[pos].first=q[cnt].first;
		}
		else q[pos].second=sel;
		res.push_back(sel);
	}
	delete[] q;
	return res;
}
/*
 *	Union-Find data structure, used for the function connect()
 */
class unionfind{
	private:
	int *parent;
	int *rank;
	public:
	unionfind(int N){
		rank=new int[N];
		parent=new int[N];
		for(int i=0;i<N;i++) rank[i]=1;
		for(int i=0;i<N;i++) parent[i]=i;
	}
	inline int find(int v){
		if(parent[v]==v) return v;
		return parent[v]=find(parent[v]);
	}
	inline void merge(int a, int b){
		int ra=find(a);
		int rb=find(b);
		if(rank[ra]>rank[rb]){
			rank[rb]+=rank[ra];
			parent[ra]=rb;
		}
		else{
			rank[ra]+=rank[rb];
			parent[rb]=ra;
		}
	}
	~unionfind(){
		delete[] rank;
		delete[] parent;
	}
};
/*
 * 	The graph main class.
 */
class graph{
	private:
	int weighted;
	bool directed;
	bool edj_shuffle;
	int (*w)(bool);
	vector<int> *adj;
	vector<int> *weights;
	int *labels,*weight;
	int N,M;
	inline pair<int,int> convert(uint64_t a, bool both){
		if(both) return make_pair(a/(N-1),a%(N-1));
		uint64_t src=(sqrt(8*a+1)+1)/2;
		uint64_t dst=a-src*(src-1)/2;
		return make_pair(src,dst);
	}
	inline void add_edge(int src,int dst){
		adj[src].push_back(dst);
		if(weighted & GRAPH_WEIGHTED_EDGES)
			weights[src].push_back(w(true));
		M++;
	}
	inline void add_edge_check(int src,int dst){
		for(unsigned i=0; i<adj[src].size(); i++)
			if(adj[src][i] == dst) return;
		add_edge(src, dst);
	}
	void add_edges(int M, bool both){
		uint64_t mmax;
		if(both) mmax=((uint64_t)N)*(N-1);
		else mmax=((uint64_t)N)*(N-1)/2;
		vector<uint64_t> edj=randnum(mmax,M);
		this->M=0;
		for(int i=0;i<M;i++){
			int src,dst;
			pair<int,int> t=convert(edj[i],both);
			src=t.first;
			dst=t.second;
			if(dst==src) dst=N-1;
			add_edge(src,dst);
		}
	}
	public:
	/*
	 *	Builds the graph. w is a function that recieves "true" if we are
	 *	requesting the weight of an edge, and "false" otherwise.
	 */
	graph(int vertices, int directed, int weighted, int type, int edges, int seed, int(*w)(bool)){
#ifndef USE_RAND
		tinymt64_init(seed);
#else
		srand(seed);
#endif
		N=vertices;
		adj=new vector<int>[N];
		weights=new vector<int>[N];
		weight=new int[N];
		labels=new int[N];
		for(int i=0;i<N;i++) labels[i]=i;
		this->w=w;
		edj_shuffle=false;
		if(weighted!=GRAPH_UNWEIGHTED)
			assert(this->w);
		if(weighted & GRAPH_WEIGHTED_VERTICES)
			for(int i=0;i<N;i++) weight[i]=w(false);
		this->weighted=weighted;
		this->directed=directed;
		switch(type){
			case GRAPH_RANDOM:
				add_edges(edges,directed==GRAPH_DIRECTED);
				break;
			case GRAPH_CYCLE:
				for(int i=0;i<N-1;i++) add_edge(i,i+1);
				add_edge(N-1,0);
				break;
			case GRAPH_PATH:
				for(int i=0;i<N-1;i++) add_edge(i,i+1);
				break;
			case GRAPH_TREE:
				for(int i=1;i<N;i++) add_edge(randint(i),i);
				break;
			case GRAPH_FOREST:{
				assert(edges<vertices);
				vector<uint64_t> v=randnum(vertices-1,edges);
				for(unsigned i=0;i<v.size();i++)
					add_edge(randint(v[i]+1),v[i]+1);
				break;
			}
			case GRAPH_CLIQUE:
				for(int i=0;i<N;i++)
					for(int j=i+1;j<N;j++)
						add_edge(i,j);
				break;
			case GRAPH_STAR:
				for(int i=1;i<N;i++) add_edge(0,i);
				break;
			case GRAPH_WHEEL:
				for(int i=1;i<N;i++) add_edge(0,i);
				for(int i=0;i<N-1;i++) add_edge(i,i+1);
				add_edge(N-1,0);
				break;
			case GRAPH_DAG:
				assert(directed==GRAPH_DIRECTED);
				add_edges(edges,false);
				break;
			default:
				fprintf(stderr,"Not implemented\n");
				assert(0==1);
		}
	}
	/*
	 *	Prints the number of vertices and edges of the graph, ending the
	 *	line with a character c.
	 */
	void printsize(char c){
		printint(N,' ');
		printint(M,c);
		flush();
	}
	/*
	 *	Prints the weight of the vertices.
	 */
	void printweight(){
		vector<int> rmap;
		rmap.resize(N);
		for(int i=0;i<N;i++) rmap[labels[i]]=i;
		for(int i=0;i<N;i++) printint(weight[rmap[i]],' ');
		#ifndef BINARY_OUTPUT
		putC('\n');
		#endif
	}
	/*
	 *	Print the edges, with their weight, if they have one.
	 */
	void printedges(){
		vector<pair<pair<int,int>,int > > edj;
		edj.reserve(M);
		for(int i=0;i<N;i++)
			for(unsigned j=0;j<adj[i].size();j++){
				if(weighted & GRAPH_WEIGHTED_EDGES)
					edj.push_back(make_pair(
						make_pair(i,adj[i][j]),
						weights[i][j]));
				else
					edj.push_back(make_pair(
						make_pair(i,adj[i][j]),
						0));
			}
		if(edj_shuffle) random_shuffle(edj.begin(),edj.end(),randint);
		if(weighted & GRAPH_WEIGHTED_EDGES){
			for(unsigned i=0;i<edj.size();i++){
				printint(labels[edj[i].first.first],' ');
				printint(labels[edj[i].first.second],' ');
				printint(edj[i].second,'\n');
			}
		}
		else{
			for(unsigned i=0;i<edj.size();i++){
				printint(labels[edj[i].first.first],' ');
				printint(labels[edj[i].first.second],'\n');
			}
		}
		flush();
	}
	/*
	 *	Prints the whole graph in the standard olympic format
	 */
	void print(){
		printsize('\n');
		if(weighted & GRAPH_WEIGHTED_VERTICES) printweight();
		printedges();
	}
	/*
	 *	Relabels the vertices and changes the order in which the edges
	 *	are printed.
	 */
	void shuffle(){
		random_shuffle(labels+1, labels+N-1, randint);
		edj_shuffle=true;
	}
	/*
	 * Adds a path from vertex i to j, adding edges i-> i+1, i+1->i+2, ...
	 * if i<j, and i->i-1, i-1->i-2, ... otherwise
	 */
	void add_path(int b, int e){
		if(b<e){
			for(int i=b; i<e; i++)
				add_edge_check(i, i+1);
		}else{
			for(int i=b; i>e; i--)
				add_edge_check(i, i-1);
		}
	}
	/*
	 *	Adds the minimum number of edges to make the graph connected.
	 */
	void connect(){
		unionfind u(N);
		for(int i=0;i<N;i++)
			for(unsigned j=0;j<adj[i].size();j++)
				u.merge(i,adj[i][j]);
		int ref=u.find(0);
		for(int i=0;i<N;i++)
			if(u.find(i)!=ref){
				add_edge(ref,i);
				u.merge(ref,i);
				ref=u.find(0);
			}
	}
	~graph(){
		delete[] adj;
		delete[] weights;
		delete[] labels;
		delete[] weight;
	}
};
