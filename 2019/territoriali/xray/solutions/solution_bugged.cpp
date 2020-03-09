/**
 *  Soluzione di xray
 *
 *  Costo di questa soluzione: lineare, calcola per ogni massimo locale il gap
 * dal minimo locale che lo porta verso il minimo globale.
 *
 * BUGGATA nel caso in cui tutti i numeri siano uguali
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int compute(std::vector<int> elements) {
  if (elements.size() == 1)
    return elements[0];
  std::vector<int> distinct_elements;
  int last_element = -1;
  for (size_t i = 0; i < elements.size(); i++) {
    if (elements[i] != last_element) {
      distinct_elements.push_back(elements[i]);
      last_element = elements[i];
    }
  }
  std::swap(elements, distinct_elements);
  size_t N = elements.size();
  std::vector<bool> is_local_min(N);
  std::vector<bool> is_local_max(N);
  is_local_min[0] = elements[0] < elements[1];
  is_local_max[0] = elements[0] > elements[1];
  is_local_min[N - 1] = elements[N - 1] < elements[N - 2];
  is_local_max[N - 1] = elements[N - 1] > elements[N - 2];
  for (size_t i = 1; i < N - 1; i++) {
    is_local_min[i] =
        (elements[i] < elements[i - 1]) && (elements[i] < elements[i + 1]);
    is_local_max[i] =
        (elements[i] > elements[i - 1]) && (elements[i] > elements[i + 1]);
  }
  int min_pos = 0;
  for (size_t i = 0; i < N; i++) {
    if (elements[i] < elements[min_pos])
      min_pos = i;
  }
  size_t cost = elements[min_pos];
  for (size_t i = 0; i < N; i++) {
    if (!is_local_max[i])
      continue;
    size_t smallest_local_min = 0;
    if (min_pos < i) {
      size_t j = i - 1;
      while (j > 0 && !is_local_min[j])
        j--;
      smallest_local_min = elements[j];
    } else {
      size_t j = i + 1;
      while (j < N && !is_local_min[j])
        j++;
      smallest_local_min = elements[j];
    }
    /*    std::cout << i << " " << elements[i] << " " << min_pos << " "
                  << smallest_local_min << std::endl;*/
    cost += elements[i] - smallest_local_min;
  }
  return cost;
}

void solve(int t) {
  int N;
  cin >> N;
  std::vector<int> elements;

  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;
    elements.push_back(a);
  }

  cout << "Case #" << t << ": " << compute(elements) << endl;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    solve(t);
  }
}
