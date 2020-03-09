#include <algorithm>

int alzati(int N, int M, int X[], int Y[]) {
  return std::max(std::min(X[0], N-1-Y[0]), std::min(Y[0], N-1-X[0]))-1;
}
