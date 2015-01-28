#include <cstdio>
#include <climits>
#include <cmath>
#include <cstdlib>

int
main(int argc, char* argv[])
{

  if (argc != 6)
    return 1;
  else
    {
      int N = atoi(argv[1]);
      int M = atoi(argv[2]);
      long long int P = atoll(argv[3]);
      long long int Q = atoll(argv[4]);
      long long int S = atoll(argv[5]);
        
      srand(S);

      printf("%d %d\n", N, M);
      
      for(int i = 0; i < M; ++i)
        {
          double r = (double)(rand()) / INT_MAX;
          long long int tmp = 4*Q*(Q+1);
          if (100*r < P) printf("0 ");
          else printf("%d ", (int)((1 + sqrt(1 + tmp*(1 - (100*r-P)/(100-P)))) / 2.0));
        }
      printf("\n");
      return 0;
    }
}
