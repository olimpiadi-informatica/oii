#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 1000;
const int WIDTH_LIMIT = 200;
std::vector<std::vector<std::vector<int>>> input_grid;
std::vector<int> input_heights;
std::vector<int> input_widths;
std::vector<std::string> solution_grid;

int compute(const std::vector<std::vector<int>> &grid, int H, int W) {
  std::vector<std::vector<std::pair<int, int>>> parent(
      H, std::vector<std::pair<int, int>>(W));
  std::vector<std::vector<int>> dist(H, std::vector<int>(W, 1e9));
  using pq_type = std::tuple<int, std::pair<int, int>, std::pair<int, int>>;
  std::priority_queue<pq_type, std::vector<pq_type>, std::greater<pq_type>> pq;
  pq.emplace(0, std::make_pair(0, 0), std::make_pair(0, 0));
  while (!pq.empty()) {
    auto t = pq.top();
    pq.pop();
    auto d = std::get<0>(t);
    auto pos = std::get<1>(t);
    auto par = std::get<2>(t);
    if (dist[pos.first][pos.second] != 1e9)
      continue;
    dist[pos.first][pos.second] = d;
    parent[pos.first][pos.second] = par;
    if (pos.first == H - 1 && pos.second == W - 1)
      break;
    auto pq_push = [&](int i, int j) {
      if (i < 0 || i >= H)
        return;
      if (j < 0 || j >= W)
        return;
      pq.emplace(std::max(d, abs(grid[i][j] - grid[pos.first][pos.second])),
                 std::make_pair(i, j), pos);
    };
    pq_push(pos.first, pos.second + 1);
    pq_push(pos.first, pos.second - 1);
    pq_push(pos.first + 1, pos.second);
    pq_push(pos.first - 1, pos.second);
  }
  int num_length = std::to_string(grid[0][0]).length();
  if ((num_length + 3) * W > WIDTH_LIMIT)
    return dist[H - 1][W - 1];
  std::pair<int, int> cur{H - 1, W - 1};
  std::vector<std::pair<int, int>> solution{cur};
  while (cur.first || cur.second) {
    cur = parent[cur.first][cur.second];
    solution.push_back(cur);
  }

  std::vector<std::vector<std::string>> tmp(
      2 * H - 1, std::vector<std::string>(2 * W - 1));
  for (int i = 0; i < 2 * H - 1; i++) {
    for (int j = 0; j < 2 * W - 1; j++) {
      if (j % 2 == 1) {
        tmp[i][j] = "   ";
      } else if (i % 2 == 1) {
        tmp[i][j] = std::string(num_length, ' ');
      } else {
        tmp[i][j] = std::to_string(grid[i / 2][j / 2]);
      }
    }
  }

  auto pad =
      [&](std::string c) { // String that represents a single unicode char
        int x = num_length - 1;
        int a = x / 2;
        int b = x - a;
        return std::string(a, ' ') + c + std::string(b, ' ');
      };
  auto direction = [&](std::pair<int, int> p, std::pair<int, int> q) {
    if (p.first == q.first) {
      if (p.second < q.second) {
        tmp[p.first + q.first][p.second + q.second] = u8" ► ";
      } else {
        tmp[p.first + q.first][p.second + q.second] = u8" ◄ ";
      }
    } else {
      if (p.first < q.first) {
        tmp[p.first + q.first][p.second + q.second] = pad(u8"▼");
      } else {
        tmp[p.first + q.first][p.second + q.second] = pad(u8"▲");
      }
    }
  };
  for (size_t i = 1; i < solution.size(); i++) {
    direction(solution[i], solution[i - 1]);
  }
  for (const auto &v : tmp) {
    solution_grid.push_back("");
    for (const auto &s : v) {
      solution_grid.back() += s;
    }
  }

  return dist[H - 1][W - 1];
}

void grade(int t, int answer) {
  solution_grid.clear();
  int correct_answer =
      compute(input_grid[t], input_heights[t], input_widths[t]);
  // std::cout << " " << answer << " " << correct_answer << std::endl;
  if (correct_answer == answer) {
    std::cout << 1.0 << std::endl;
    std::cerr << 0 << std::endl;
    return;
  }
  std::cout << 0.0 << std::endl;
  std::string output = "Risposta sbagliata. La risposta corretta era " +
                       std::to_string(correct_answer);
  for (const std::string &s : solution_grid) {
    output += "\n" + s;
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
    int H, W;
    fin >> H >> W;
    input_grid.emplace_back(H, std::vector<int>(W));
    input_heights.emplace_back(H);
    input_widths.emplace_back(W);
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        fin >> input_grid.back()[i][j];
      }
    }
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
