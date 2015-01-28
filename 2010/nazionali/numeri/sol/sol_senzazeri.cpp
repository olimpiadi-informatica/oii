
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
  
  scanf("%d %d", &wrong, &treesNum);
  int realTreesNum = 0;
  for (int i = 0; i < treesNum; i++) {
    int tmp;
    scanf("%d", &tmp);
    if (tmp == 0) zeros[realTreesNum]++;
    else trees[realTreesNum++] = tmp;
  }
  treesNum = realTreesNum;

  int start = 0;
  int end = 0;
  int sum = 0;
  int count = 0;

  while ((start < treesNum) || (end < treesNum)) {
    if ((sum <= wrong) && (end < treesNum)) {
      sum += trees[end];
      end++;
    } else {
      sum -= trees[start];
      start++;
    }
    if (sum == wrong) {
    //      count += (1+zeros[start])*(1+zeros[end]);
      count += 1;
    }
  }

  printf("%d\n", count);

  return 0;

}
