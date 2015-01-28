
/*

Soluzione di Giovanni Mascellani.

Dovrebbe essere efficiente ed è d'accordo con la soluzione
di Matteo su una ventina di casi di prova di dimensione
massima (generati con il generatore, che però mi sembra
non metta zeri ancora).

Scandisce banalmente l'array con una sliding window,
eliminando gli zeri dal vettore e memorizzandoli a
parte per rendere più efficiente e semplice il calcolo.

*/

#include <cstdlib>
#include <cstdio>

using namespace std;

const int MaxTreesNum = 1000000;

int wrong, treesNum;
int trees[MaxTreesNum];
int zeros[MaxTreesNum+1];

int main() {

#if defined(EVAL)
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  // non comprime gli zeri  
  scanf("%d %d", &wrong, &treesNum);
  for (int i = 0; i < treesNum; i++) {
    int tmp;
    scanf("%d", &tmp);
    trees[i] = tmp;
  }

  int count = 0;
  int M = treesNum, N = wrong;
  for (int i = 0; i < M; ++i)
    {
      //ma poi fa partire solo da un numero positivo
      if (trees[i] == 0) continue;
      int sum = 0;
      for (int j = i; j < M; j++)
        {
          sum += trees[j];
          if (sum > N) break;
          if (sum == N)
            {
              //poi quando arriva esattamente alla somma
              int k, l;
              for (k = i-1; k >= 0 && trees[k] == 0; k--);
              for (l = j+1; l < M && trees[l] == 0; l++);
              //conta quanti zeri ci sono all'inizio e alla fine
              count += (l-j)*(i-k);
              break;
            }
        }

    }

  printf("%d\n", count);

  return 0;

}
