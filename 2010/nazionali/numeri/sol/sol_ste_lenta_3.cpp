/*
  Comprime gli zeri
  Ma poi fa la cosa stupida (N*MAXLENGTH)
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
  //  for (int i = 0; i < realTreesNum; i++)
    //    printf("%d\n", zeros[i]);
  treesNum = realTreesNum;

  int count = 0;
  int M = treesNum, N = wrong;
  for (int i = 0; i < treesNum; ++i)
    {
      int sum = 0;
      for (int j = i; j < M; j++)
        {
          sum += trees[j];
          if (sum > N) break;
          if (sum == N)
            {
              //              printf("%d %d %d %d\n", i, j, zeros[i], zeros[j+1]);
              count += (zeros[i]+1)*(zeros[j+1]+1);
              break;
            }
        }

    }

  printf("%d\n", count);

  return 0;

}
