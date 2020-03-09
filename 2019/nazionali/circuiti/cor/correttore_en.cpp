/**
 *  Autore: Luca Versari
 */

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "sparsepp/spp.h"

int subtask;
int N;

int input_depth_max;

const int HARD_COST_LIMIT = 50000;
const int COST_MAX = 1100;

// Extremes inclusive.
int rng(int min, int max) {
    assert(min <= max);
    static std::mt19937_64 rng_;
    return std::uniform_int_distribution<int>(min, max)(rng_);
}

double partial_score(double c, double c_max) {
    assert(c >= 0);
    if (c <= c_max) return 1.0;
    return c_max / c;
}

double score(int depth, int cost) {
    return partial_score(depth, input_depth_max) *
           partial_score(cost, COST_MAX);
}

using ll = long long;

void err(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void ex(std::string msg, float res) {
    if (!msg.empty()) fprintf(stderr, "%s ", msg.c_str());
    printf("%f\n", res);
    exit(0);
}

std::function<ll(ll, ll)> ops[] = {
    [](ll a, ll b) { return a + b; }, [](ll a, ll b) { return a - b; },
    [](ll a, ll b) { return a * b; }, [](ll a, ll b) { return std::min(a, b); },
    [](ll a, ll b) { return std::max(a, b); }};

// TODO: aggiungere altri operatori
spp::sparse_hash_map<std::string, int> operators = {
    {"+", 0}, {"-", 1}, {"*", 2}, {"min", 3}, {"max", 4}};

std::ifstream fout;

std::vector<int> input_data;
std::vector<ll> output_data;
ll max_depth;

class Node {
   public:
    enum Kind { INPUT, CONST, COMPUTE, OUTPUT };
    ll value() const { return val_; }
    void compute();
    ll depth() const { return depth_; }
    ll cost() const { return kind == COMPUTE; }
    Node(Kind kind, int pos, ll val, int a, int b, int op)
        : kind(kind), pos_(pos), val_(val), a_(a), b_(b), op_(op) {}

   private:
    Kind kind;
    int pos_;
    ll val_;
    int a_;
    int b_;
    int op_;
    ll depth_ = 0;
};

Node InputNode(int pos) { return Node(Node::INPUT, pos, 0, -1, -1, 0); }
Node OutputNode(int in, int pos) {
    return Node(Node::OUTPUT, pos, 0, in, -1, 0);
}
Node ConstNode(ll val) { return Node(Node::CONST, 0, val, -1, -1, 0); }
Node OpNode(int a, int b, int op) {
    return Node(Node::COMPUTE, 0, 0, a, b, op);
}

std::vector<Node> program;

void Node::compute() {
    if (kind == INPUT) {
        val_ = input_data.at(pos_);
    }
    if (kind == COMPUTE) {
        val_ = ops[op_](program[a_].value(), program[b_].value());
        depth_ = std::max(program[a_].depth(), program[b_].depth()) + 1;
    }
    if (kind == OUTPUT) {
        output_data[pos_] = program[a_].value();
        depth_ = program[a_].depth();
        if (max_depth < depth_) {
            max_depth = depth_;
        }
    }
}

/* cost, depth */
std::pair<int, int> Evaluate() {
    max_depth = 0;
    ll cost = 0;
    for (auto &op : program) {
        op.compute();
        cost += op.cost();
    }
    return {cost, max_depth};
}

void readProgram(int input_size, int output_size) {
    input_data.resize(input_size);
    output_data.resize(output_size);
    spp::sparse_hash_map<std::string, int> nodes;
    auto add_node = [&nodes](std::string name, Node node) {
        if (nodes.count(name)) {
            ex("Output " + name + " was redefined.", 0.0);
        }
        program.push_back(std::move(node));
        nodes.emplace(name, program.size() - 1);
    };
    auto get_node = [&nodes](std::string name) {
        if (nodes.count(name)) return nodes.at(name);
        if (name.find("out[") == 0) {
            ex("Output " + name + " was not computed.", 0.0);
        } else {
            ex("Node " + name + " was not defined.", 0.0);
        }
        return 0;
    };
    for (int i = 0; i < input_size; i++) {
        add_node("in[" + std::to_string(i) + "]", InputNode(i));
    }

    auto skip_spaces = [](const char *c, int &pos) {
        while (c[pos] && isblank(c[pos])) pos++;
    };

    auto get_op = [skip_spaces](const char *c, int &pos, std::string &out) {
        skip_spaces(c, pos);
        out = "";
        while (c[pos] && !operators.count(out) && !isblank(c[pos])) {
            out += c[pos];
            pos++;
        }
        return operators.count(out);
    };

    auto get_int = [skip_spaces](const char *c, int &pos, ll &out) {
        skip_spaces(c, pos);
        out = 0;
        bool neg = false;
        bool found_digit = false;
        if (c[pos] && (c[pos] == '-' || c[pos] == '+')) {
            neg = c[pos] == '-';
            pos++;
        }
        while (c[pos] && isdigit(c[pos])) {
            found_digit = true;
            out = out * 10 + c[pos] - '0';
            pos++;
        }
        if (neg) out = -out;
        return found_digit;
    };

    auto get_var = [skip_spaces, get_int](const char *c, int &pos,
                                          std::string &out, std::string &base,
                                          ll &idx) {
        skip_spaces(c, pos);
        out = "";
        base = "";
        idx = 0;
        bool found_ide = false;
        if (!isalpha(c[pos]) && c[pos] != '_') return false;
        while (c[pos] && (isalnum(c[pos]) || c[pos] == '_')) {
            found_ide = true;
            base += c[pos];
            pos++;
        }
        if (!found_ide) return false;
        if (c[pos] != '[') return false;
        pos++;
        if (!get_int(c, pos, idx)) return false;
        if (c[pos] != ']') return false;
        pos++;
        out = base + '[' + std::to_string(idx) + ']';
        return true;
    };

    auto get_eq = [skip_spaces](const char *c, int &pos) {
        skip_spaces(c, pos);
        if (c[pos] != '=') return false;
        pos++;
        return true;
    };

    auto check_end = [skip_spaces](const char *c, int &pos) {
        skip_spaces(c, pos);
        return !c[pos];
    };

    int line_count = 0;
    std::string line;
    while (std::getline(fout, line)) {
        if (++line_count > HARD_COST_LIMIT) {
            ex("The file has too many lines.", 0.0);
        }
         if (line[line.size() - 1] == '\r') line.pop_back();
         for (char c : line) {
            if (!(isalnum(c) || isblank(c) || c == '[' || c == ']' ||
                  c == '=' || c == '+' || c == '-')) {
                std::string msg = std::string("Carattere non valido");
                ex(msg.c_str(), 0.0);
            }
        }

        const char *c = line.c_str();
        int pos = 0;
        if (check_end(c, pos)) continue;
        std::string out;
        std::string a;
        std::string op;
        std::string b;
        std::string base;
        ll idx;
        ll val;
        if (!get_var(c, pos, out, base, idx)) {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": identifier expected",
               0.0);
        }
        if (base == "in") {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": cannot assign to in",
               0.0);
        }
        if (!get_eq(c, pos)) {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": expected =",
               0.0);
        }
        if (get_int(c, pos, val)) {
            a = "%%val%%" + std::to_string(val);
            if (!nodes.count(a)) {
                add_node(a, ConstNode(val));
            }
        } else if (!get_var(c, pos, a, base, idx)) {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": identifier or integer expected",
               0.0);
        }
        if (!get_op(c, pos, op)) {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": operator expected",
               0.0);
        }
        if (get_int(c, pos, val)) {
            b = "%%val%%" + std::to_string(val);
            if (!nodes.count(b)) {
                add_node(b, ConstNode(val));
            }
        } else if (!get_var(c, pos, b, base, idx)) {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": identifier or integer expected",
               0.0);
        }
        if (!check_end(c, pos)) {
            ex("Error on line " + line + ", char " +
                   std::to_string(pos) + ": end of line expected",
               0.0);
        }
        add_node(out, OpNode(get_node(a), get_node(b), operators.at(op)));
    }
    for (int i = 0; i < output_size; i++) {
        add_node("%%dummy%%" + std::to_string(i),
                 OutputNode(get_node("out[" + std::to_string(i) + "]"), i));
    }
}

void fillRandomData(int min, int max) {
    for (auto &in : input_data) {
        in = rng(min, max);
    }
}

void run_it(std::vector<std::pair<int, int>> tests,
            std::function<std::string()> check) {
    std::pair<int, int> p;
    for (auto test : tests) {
        fillRandomData(test.first, test.second);
        p = Evaluate();
        std::string out = check();
        if (out != "") {
            ex(("Output is wrong: " + out).c_str(), 0.0);
        }
    }
    ex(("Output is correct, depth = " + std::to_string(p.second) +
        ", cost = " + std::to_string(p.first))
           .c_str(),
       score(p.second, p.first));
}

void checkSum() {
    readProgram(N, 1);
    run_it({{0, 100},
            {0, 1000},
            {0, 1000000},
            {-1000000, 1000000},
            {std::numeric_limits<int>::min(), -1},
            {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}},
           []() {
               long long val = 0;
               for (int v : input_data) {
                   val += v;
               }
               if (output_data[0] == val) return std::string("");
               return "result " + std::to_string(output_data[0]) +
                      " incorrect, correct value " + std::to_string(val);
           });
}

void checkPrefixSum() {
    readProgram(N, N);
    run_it({{0, 100},
            {0, 1000},
            {0, 1000000},
            {-1000000, 1000000},
            {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}},
           []() {
               std::vector<ll> ps;
               for (int v : input_data) {
                   if (ps.size())
                       ps.push_back(ps.back() + v);
                   else
                       ps.push_back(v);
               }
               for (int i = 0; i < N; i++) {
                   if (ps[i] != output_data[i])
                       return "result " + std::to_string(output_data[i]) +
                              " at position " + std::to_string(i) +
                              " incorrect, correct value " +
                              std::to_string(ps[i]);
               }
               return std::string("");
           });
}

bool is_prime(int v) {
    for (int j = 2; j * j <= v; j++) {
        if (v % j == 0) return false;
    }
    return true;
}

void checkCountPrimes(int maxV) {
    readProgram(N, 1);
    run_it({{2, std::min(100, maxV)},
            {2, std::min(1000, maxV)},
            {2, std::min(1000000, maxV)},
            {2, std::min(1000000, maxV)},
            {2, maxV}},
           []() {
               int res = 0;
               for (int v : input_data) {
                   if (is_prime(v)) res++;
               }
               if (output_data[0] == res) return std::string("");
               return "result " + std::to_string(output_data[0]) +
                      " incorrect, correct value " + std::to_string(res);
           });
}

void checkMaxSubarray() {
    readProgram(N, 1);
    run_it({{0, 10},
            {-10, 100},
            {-100, 1000},
            {-1000, 1000000},
            {-1000000, 1000000},
            {std::numeric_limits<int>::min(), -1},
            {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}},
           []() {
               ll max = 0;
               ll s = 0;
               for (int v : input_data) {
                   s += v;
                   if (s < 0) s = 0;
                   if (s > max) max = s;
               }
               if (output_data[0] == max) return std::string("");
               return "result " + std::to_string(output_data[0]) +
                      " incorrect, correct value " + std::to_string(max);
           });
}

int main(int argc, char **argv) {
    if (argc != 4)
        err("Usage: correttore <input> <correct output> <test output>");

    FILE *fin;
    fin = fopen(argv[1], "r");
    fout.open(argv[3]);
    if (!fin) err("Cannot open input file!");
    if (!fout) err("Cannot open output file!");
    int maxV;
    fscanf(fin, "%d %d %d", &subtask, &N, &input_depth_max);
    switch (subtask) {
        case 1:
            checkSum();
            break;
        case 2:
            checkPrefixSum();
            break;
        case 4:
            fscanf(fin, "%d", &maxV);
            checkCountPrimes(maxV);
            break;
        case 3:
            checkMaxSubarray();
            break;
        default:
            return 1;
    };

    ex("Unexpected error.", 0.0);
}
