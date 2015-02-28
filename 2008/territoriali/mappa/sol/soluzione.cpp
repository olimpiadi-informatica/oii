#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const int INF = 1000000;
const int MAXN = 100;

int N;
char m[MAXN+2][MAXN+2];
int ris[MAXN+2][MAXN+2];
queue< pair<int,int> > q;

int
esegui(void)
{
  int i, j;
  int k = 0;
  q.push(pair<int,int>(1,1));
  m[1][1] = 'v';
  ris[1][1] = 1;
  while (!q.empty())
    {
      pair<int,int> pos = q.front();
      k++;
      int r = pos.first, c = pos.second;
      q.pop();
      for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
          {
            if (m[r+i][c+j] == '*')
              {
                if (r+i == N && c+j == N)
                  return ris[r][c] + 1;
                m[r+i][c+j] = 'v';
                ris[r+i][c+j] = ris[r][c]+1;
                q.push(pair<int, int>(r+i, c+j));
              }
          }
    }
  return ris[N][N];
}

int
main(void)
{
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif

  int i, j;
  in >> N;
  for (i = 1; i <= N; i++)
    {
      in >> (m[i] + 1);
      m[i][0] = m[i][N+1] = '+';
      for (j = 1; j <= N; j++)
        ris[i][j] = INF;
    }
  for (j = 0; j <= N; j++)
    m[0][j] = m[N+1][j] = '+';
  // m e` cerchiata da un quadrato di lastroni insormontabili per praticita`  

  out << esegui() << endl;

  return 0;
}
