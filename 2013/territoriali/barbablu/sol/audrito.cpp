/*
  Autore       Giorgio Audrito

  Descrizione  Soluzione che fa un Floyd-Warshall su tutto il grafo,
               poi crea un grafo solo tra i nodi con aria, collegando i
	       nodi con distanza <20. Poi faccio il cammino minimo sul grafo rimasto.
*/

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

#define MAXN 30
#define MAXM 100
#define AIR  20
#define INFTY 1000000

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int AdjMatrix[MAXN][MAXN];
int AirMatrix[MAXN][MAXN];
int Aria[MAXN];
int N, M, C, K;

void FloydWarshall(int dist[][MAXN], int N)
{
  for (int k=0; k<N; k++)
    for (int i=0; i<N; i++)
      for (int j=0; j<N; j++)
	if ( dist[i][j] > dist[i][k] + dist[k][j] )
	  dist[i][j] = dist[i][k] + dist[k][j];
}

void MakeGraph()
{
  for (int i=0; i<K; i++)
    for (int j=0; j<K; j++)
      AirMatrix[i][j] = AdjMatrix[Aria[i]][Aria[j]] <= AIR ? AdjMatrix[Aria[i]][Aria[j]] : INFTY;
}

int
main(void)
{
  int a, b, c;

  in >> N >> M >> C >> K;
  C--;
  assert(2 <= N && N <= MAXN);
  assert(2 <= M && M <= MAXM);
  for (int i=0; i<K; i++) {
    in >> Aria[i];
    Aria[i]--;
  }
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++)
      AdjMatrix[i][j] = INFTY;
    AdjMatrix[i][i] = 0;
  }
  for (int i=0; i<M; i++) {
    in >> a >> b >> c;
    a--, b--;
    AdjMatrix[a][b] = c;
    AdjMatrix[b][a] = c;
  }

  FloydWarshall(AdjMatrix, N);

  MakeGraph();

  FloydWarshall(AirMatrix, K);

  int best=INFTY;
  for (int i=0; i<K; i++)
    if (Aria[i] == C) {
      for (int j=0; j<K; j++)
	if (AdjMatrix[0][Aria[j]] <= AIR && best > AdjMatrix[0][Aria[j]] + AirMatrix[j][i] ) {
	  best = AdjMatrix[0][Aria[j]] + AirMatrix[j][i];
	}
      if (best < INFTY)
	out << best << endl;
      else
	out << -1 << endl;
      break;
    }
  return 0;
}
