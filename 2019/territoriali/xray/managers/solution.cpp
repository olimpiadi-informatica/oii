#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000;
const int WIDTH_LIMIT = 2000;
std::vector<std::vector<int>> inputs;
std::vector<std::pair<int, int>> operations;

int ric(int left, int right, int water, int *vec) {
  if (right < left)
    return 0;
  int my_cost = 0;
  int pos_min = left;
  for (int i = left + 1; i <= right; i++)
    if (vec[i] < vec[pos_min])
      pos_min = i;
  assert(vec[pos_min] >= water);
  if (vec[pos_min] > water) {
    my_cost = vec[pos_min] - water;
    for (int i = 0; i < my_cost; i++) {
      operations.emplace_back(left, right);
    }
    water = vec[pos_min];
  }
  my_cost += ric(left, pos_min - 1, water, vec);
  my_cost += ric(pos_min + 1, right, water, vec);
  return my_cost;
}

int compute(int N, int *vec) { return ric(1, N, 0, vec); }

void grade(int t, int answer) {
  operations.clear();
  int correct_answer = compute(inputs[t].size() - 2, inputs[t].data());
  if (correct_answer == answer) {
    std::cout << 1.0 << std::endl;
    std::cerr << 0 << std::endl;
    return;
  }
  std::cout << 0.0 << std::endl;
  std::random_shuffle(operations.begin(), operations.end());
  std::string output = "Risposta sbagliata. La risposta corretta era:";
  for (auto o : operations) {
    output +=
        " (" + std::to_string(o.first) + ", " + std::to_string(o.second) + ")";
    if (output.size() > WIDTH_LIMIT) {
      output = "Risposta sbaglata. La risposta corretta era " +
               std::to_string(correct_answer);
      break;
    }
  }
  std::cerr << output.size() << std::endl;
  std::cerr << output << std::flush;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s input\n", argv[0]);
    return 1;
  }
  int T;
  std::ifstream fin(argv[1]);
  fin >> T;

  for (int t = 0; t < T; t++) {
    int N;
    fin >> N;
    inputs.emplace_back();
    inputs.back().push_back(0);
    for (int i = 0; i < N; i++) {
      int a;
      fin >> a;
      inputs.back().push_back(a);
    }
    inputs.back().push_back(0);
  }

  int testcase = 0;
  int output = 0;
  while (cin) {
    cin >> testcase;
    if (!testcase)
      return 0;
    cin >> output;
    grade(testcase - 1, output);
  }
}
