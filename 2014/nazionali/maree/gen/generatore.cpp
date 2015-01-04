#include "graph.h"

int const MAXN = 2000000;
int const MAXT = 1000000000;

int n;	// Numero di componenti
vector<int> components;	// Numero di nodi di ciascuna componente
vector<int> partenza;	// Primo nodo di ciascuna componente
vector< pair<int,int> > components_edges;	// Archi a livello di componenti

set< pair<int,int> > edges;	// Archi veri
vector< pair<int,int> > shuffled_edges;	// Archi veri mescolati

vector<int> permutation;	// Permutazione da applicare ai vertici

int myrandom (int i) {
	return rand() % i;
}

void make_components_graph(int N, int K, int X, int Y, int R, int H) {
	// Costruzione del grafo delle componenti

	int i=0;	// Nodi creati
	n = 0;
	while ( i < N ) {
		int j = rand() % K + 1;
		if ( i+j > N ) j = N-i;
		components.push_back(j);
		partenza.push_back(i);
		i += j;
		n++;
	}

	int a = X * n / 100;	// Numero di componenti da cui partire verso destra
	if ( a >= n ) a = n-1;

	for (i=0; i<a; ++i) {
		int num = rand() % R + 1;	// Numero di archi che faccio partire
		int maxlun = min( H, n-1-i );
		for (int j=0; j<num; ++j) {
			int lun = rand() % maxlun + 1;	// Distanza a cui far arrivare l'arco
			components_edges.push_back( pair<int,int>(i, i+lun) );
		}
	}

	int b = Y * n / 100;	// Numero di componenti da cui partire verso sinistra
	if ( b >= n ) b = n-1;

	for (i=0; i<b; ++i) {
		int num = rand() % R + 1;	// Numero di archi che faccio partire
		int maxlun = min( H, n-1-i );
		int lun = rand() % maxlun + 1;	// Distanza a cui far arrivare l'arco
		components_edges.push_back( pair<int,int>(n-1-i, n-1-i-lun) );
	}

	/*
	printf("COMPONENTI\n");
	for (int i=0; i<n; ++i) {
		printf("%d inizia da %d\n", i, partenza[i]);
	}
	*/
}

int random_node(int i) {
	// Ritorna un nodo a caso della i-esima componente
	int j = rand() % components[i];
	return partenza[i] + j;
}

void make_real_graph(int R, int N) {
	int cont = 0;

	for (int i=0; i<n; ++i) {
		int v = components[i];

		// Uso i vertici da cont a cont+v-1
		if ( v >= 2 ) {
			for (int j=0; j<v; ++j) {
				edges.insert( pair<int,int>( cont+j, cont+((j+1)%v) ) );
			}
		}

		int quanti = rand() % ( v*R );	// Archi aggiuntivi da generare
		if ( v <= 5 ) quanti = rand() % v;

		for (int j=0; j<quanti; ++j) {
			int a = rand() % v;
			int b = rand() % v;
			if ( a == b ) continue;
			edges.insert( pair<int,int>( cont+a, cont+b ) );
		}

		cont += v;
	}

	/*
	printf("ARCHI INTERNI\n");
	for (set< pair<int,int> >::iterator i=edges.begin(); i!=edges.end(); ++i) {
		printf("%d %d\n", (*i).first, (*i).second);
	}
	*/

	for (int i=0; i<components_edges.size(); ++i) {
		int a = components_edges[i].first;
		int b = components_edges[i].second;

		int aa = random_node(a);
		int bb = random_node(b);

		// printf("Arco dalla componente %d alla componente %d: %d %d\n", a, b, aa, bb);

		edges.insert( pair<int,int>(aa, bb) );
	}

	// Scelgo la permutazione dei vertici

	permutation.resize(N);
	for (int i=0; i<N; ++i) {
		permutation[i] = i;
	}
	vector<int>::iterator first = permutation.begin();
	first++;
	vector<int>::iterator last = permutation.end();
	last--;

	random_shuffle( first, last, myrandom );

	// Rinomino i vertici nell'elenco degli archi

	for ( set< pair<int,int> >::iterator i = edges.begin(); i != edges.end(); ++i ) {
		shuffled_edges.push_back( pair<int,int> ( permutation[ (*i).first ], permutation[ (*i).second ] ) );
	}

	// Mescolo gli archi

	random_shuffle( shuffled_edges.begin(), shuffled_edges.end(), myrandom );
}


void print_graph(int N, int T) {
	//printf("STAMPO IL GRAFO\n");

	printf("%d %d %d\n", N, shuffled_edges.size(), T);

	for (int i=0; i<shuffled_edges.size(); ++i) {
		printf("%d %d\n", shuffled_edges[i].first, shuffled_edges[i].second);
	}

}

bool visitato[MAXN];
vector<int> vicini[MAXN];
queue< pair<int,int> > coda;

pair<int,int> distanze[MAXN];	// Distanza di ogni nodo da 0 (prima della marea) e da N-1 (dopo la marea)

vector< pair<int,int> > distanze_buone;	// Distanze tra 0 e i nodi da cui dopo la marea si riesce ad arrivare a N-1,
										// e corrispondente t2

void BFS(int nodo, int tempo, int type) {
	if ( visitato[nodo] ) return;

	visitato[nodo] = 1;

	// printf("Nodo %d a distanza %d\n", nodo, tempo);
	if ( type == 0 ) distanze[nodo].first = tempo;
	else distanze[nodo].second = tempo;

	for (int i=0; i<vicini[nodo].size(); ++i) {
		coda.push( pair<int,int>( vicini[nodo][i], tempo+1 ) );
	}
}

void runBFS(int nodo, int type) {

	coda.push( pair<int,int>(nodo, 0) );
	while ( !coda.empty() ) {
		int nodo = coda.front().first;
		int time = coda.front().second;
		coda.pop();
		BFS(nodo, time, type);
	}

}

int chooseT(int N) {
	assert( N <= MAXN );

	for (int i=0; i<shuffled_edges.size(); ++i) {
		vicini[ shuffled_edges[i].first ].push_back( shuffled_edges[i].second );
	}

	// Prima della marea

	for (int i=0; i<N; ++i) {
		visitato[i] = 0;
		distanze[i].first = -1;
	}

	runBFS(0, 0);

	// Dopo la marea

	for (int i=0; i<N; ++i) {
		visitato[i] = 0;
		distanze[i].second = -1;
	}

	runBFS(N-1, 1);

	/*
	for (int i=0; i<N; ++i) {
		printf("Nodo %d: %d %d\n", i, distanze[i].first, distanze[i].second);
	}
	*/

	// Cerco il T che mi piace di piu'

	for (int i=0; i<N; ++i) {
		if ( distanze[i].second != -1 && distanze[i].first != -1 ) distanze_buone.push_back( distanze[i] );
	}
	sort( distanze_buone.begin(), distanze_buone.end() );

	int m = distanze_buone.size();
	if ( m == 0 ) return rand() % N + 1;

	int q = rand() % (m+1);	// Voglio scegliere un T per cui T < distanze_buone[q]
	int T;

	if ( q == 0 ) {
		// Voglio un T tra 0 e distanze_buone[0]-1
		// fprintf(stderr,"Caso 0\n");
		if ( distanze_buone[0].first == 0 ) return 0;
		int T = rand() % distanze_buone[0].first;
	}
	else if ( q < m ) {
		// Voglio un T tra distanze_buone[q-1] e distanze_buone[q]-1
		// fprintf(stderr,"Caso 1, %d.... %d\n", q, distanze_buone[q-1].first);
		if ( distanze_buone[q-1].first == distanze_buone[q].first ) return distanze_buone[q].first;
		int T = rand() % ( distanze_buone[q].first - distanze_buone[q-1].first ) + distanze_buone[q-1].first;
	}
	else {
		// Voglio un T tra distanze_buone[m-1] e MAXT
		// fprintf(stderr,"Caso 1\n");
		int T = rand() % ( MAXT - distanze_buone[m-1].first ) + distanze_buone[m-1].first;
		fprintf(stderr,"Caso 2\n");
	}

	return T;
}


int main(int argc, char** argv){
	int N, K, H, X, Y, R, T, M, P, S;
	if(argc != 11){
		fprintf(stderr,"Wrong number of arguments\n");
		return 1;
	}
	N = atoi(argv[1]);	// Numero di nodi
	K = atoi(argv[2]);	// Massima grandezza di una componente
	H = atoi(argv[3]);	// Massima distanza a cui arrivano gli archi in avanti
	X = atoi(argv[4]);	// Numero di componenti (in percentuale) da cui partire verso destra
	Y = atoi(argv[5]);	// Numero di componenti (in percentuale) da cui partire verso sinistra
	R = atoi(argv[6]);	// Rapporto approssimativo archi/vertici
	T = atoi(argv[7]);	// Tempo di cambio marea (non usato nel generatore di tipo 3)
	M = atoi(argv[8]);	// Numero approssimativo di archi (usato dal generatore di tipo 1)
	P = atoi(argv[9]);	// Tipo di grafo da generare
	S = atoi(argv[10]);	// Seed

	srand(S);

	switch(P) {
		case 0:
			// Caso di prova
			printf("9 10 5\n0 1\n1 4\n4 2\n2 0\n2 3\n4 5\n7 5\n6 7\n6 3\n8 6\n");
			break;

		case 1:
			// Grafo a caso di Luca
			{
			graph g(N, GRAPH_DIRECTED, GRAPH_UNWEIGHTED, GRAPH_RANDOM, M, S, NULL);
			int l = randint(((N<T)?N:T)+1);
			g.add_path(0, l);
			g.add_path(N-1, l);
			g.shuffle();
			g.printsize(' ');
			printf("%d\n", T);
			g.printedges();
			}
			break;

		case 2:
			// Grafo buffo generico di Giove
			make_components_graph(N, K, X, Y, R, H);
			make_real_graph(R, N);
			print_graph(N, T);
			break;

		case 3:
			// Grafo buffo di Giove + scelta sensata del tempo di marea
			make_components_graph(N, K, X, Y, R, H);
			make_real_graph(R, N);
			T = chooseT(N);
			// printf("Ho scelto T = %d\n", T);
			print_graph(N, T);
	}

	return 0;
}

