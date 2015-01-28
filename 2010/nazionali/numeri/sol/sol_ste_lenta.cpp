
/*

Soluzione di Stefano Maggiolo.

Quadratica con taglio stupido (quando supera N si ferma)

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
  for (int i = 0; i < treesNum; i++) {
    int tmp;
    scanf("%d", &tmp);
    trees[i] = tmp;
  }

  int count = 0;

  for (int i = 0; i < treesNum; ++i)
    {
      int sum = 0;
      for (int j = i; j < treesNum; ++j)
        {
          sum += trees[j];
          if (sum > wrong) break;
          if (sum == wrong) ++count;
        }
    }

  printf("%d\n", count);

  return 0;

}
