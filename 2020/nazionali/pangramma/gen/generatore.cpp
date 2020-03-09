#include <algorithm>
#include <cassert>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>

#define MAX_NUMBER (46330)

using namespace std;

void map_random(vector<int>& v, mt19937& r) {
    size_t next_index = 0;
    unordered_map<int, size_t> mapper;
    for(int i : v) {
        if(!mapper.count(i)) {
            mapper[i] = next_index++;
        }
    }
    vector<int> p;
    unordered_set<int> a;
    uniform_int_distribution<int> g(0, MAX_NUMBER);
    while(p.size() < next_index) {
        int c = g(r);
        if(!a.count(c)) {
            a.insert(c);
            p.push_back(c);
        }
    }
    for(int& i : v) {
        i = p[mapper[i]];
    }
}

// TIPO 0
vector<int> gen_random(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 0);
    assert(k >= 3); // otherwise, use single or binary
    assert(k < n); // otherwise, use permutation
    uniform_int_distribution<int> u(0, k - 1);
    vector<int> v(n);
    for(size_t i = 0; i < v.size(); i++) {
        if(i < k) {
            v[i] = i;
        } else {
            v[i] = u(r);
        }
    }
    shuffle(v.begin(), v.end(), r);
    return v;
}

// TIPO 1
vector<int> gen_binary(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 0);
    assert(k == 2);
    uniform_int_distribution<int> u(0, 1);
    vector<int> v(n);
    for(int& i : v) {
        i = u(r);
    }
    return v;
}

// TIPO 2
vector<int> gen_single(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 0);
    assert(k == 1);
    vector<int> v(n, 0);
    return v;
}

// TIPO 3 [C = lunghezza uguali]
vector<int> gen_cycles(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 1);
    assert(k > 2);
    int c = atoi(argv[0]);
    vector<int> v(n);
    size_t index = 0;
    while(index < n) {
        v[index++] = 0;
        for(int i = 0; i < c && index < n; i++) {
            v[index++] = 1;
        }
        vector<int> p(k - 2);
        iota(p.begin(), p.end(), 2);
        shuffle(p.begin(), p.end(), r);
        for(int i = 0; i < k - 2 && index < n; i++) {
            v[index++] = p[i];
        }
        for(int i = 0; i < c && index < n; i++) {
            v[index++] = 1;
        }
    }
    return v;
}

// TIPO 4
vector<int> gen_permutation(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 0);
    assert(k == n);
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), r);
    return v;
}

// TIPO 5
vector<int> gen_smile(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 0);
    vector<int> v(n);
    v[0] = 0;
    v[n - 1] = 1;
    size_t _n = n - 2;
    size_t _k = k - 2;
    vector<int> p = gen_random(_n, _k, r, 0, argv);
    for(size_t i = 0; i < p.size(); i++) {
        v[i + 1] = p[i] + 2;
    }
    return v;
}

// TIPO 6
vector<int> gen_hrep(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 1);
    int h = atoi(argv[0]);
    vector<int> v(n);
    size_t index = 0;
    while(index < n) {
        for(size_t i = 0; i < k && index < n; i++) {
            for(size_t j = 0; j < h; j++) {
                v[index++] = i;
            }
        }
    }
    return v;
}

// TIPO 7: [a, b, c] (the solution will be a*b*c+a+b-1, n must be (a+b+1)*(c+1)+1)
vector<int> gen_exact_solution(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 3);
    assert(k == 4);
    int a = atoi(argv[0]);
    int b = atoi(argv[1]);
    int c = atoi(argv[2]);
    assert(n == (a + b + 1) * (c + 1) + 1);
    vector<int> v(n);
    size_t index = 0;
    v[index++] = 0;
    for(size_t i = 0; i < a + b - 1; i++) {
        v[index++] = 2;
    }
    v[index++] = 3;
    v[index++] = 1;
    int next_break = 0;
    for(size_t j = 0; j < c; j++) {
        for(size_t i = 0; i < a; i++) {
            v[index++] = 2;
        }
        for(size_t i = 0; i < b; i++) {
            v[index++] = 3;
        }
        v[index++] = next_break;
        next_break ^= 1;
    }
    return v;
}

static int build_reps(vector<int> &buff, mt19937& r, vector<int> const& alphabet, int l) {
    for (int i = 0; i < alphabet.size(); i++) {
        for (int j = 0; j < i + 2; j++) {
            buff.push_back(alphabet[i]);
            if (buff.size() >= l) return i + 1;
        }
    }
}

// TIPO 8
vector<int> gen_multiple_freqs(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    // The parameter n is ignored and generated based on k
    assert(argc == 1);
    int x = atoi(argv[0]);
    vector<int> sequence;

    size_t O = 2 * x;
    size_t U = O * O;
    size_t N = 3 * U;

    vector<int> unique;
    for (int i = 0; i < U; i++) {
        unique.push_back(i);
    }
    shuffle(unique.begin(), unique.end(), r);


    vector<int> omega;
    for (int i = 0; i < O; i++) {
        omega.push_back(U + i);
    }
    // shuffle(omega.begin(), omega.end(), r);

    vector<int> reps;
    O = build_reps(reps, r, omega, U/2);

    if (k != (O + U) || n != N) {
        fprintf(stderr, "Needed values: N = %lu, K = %lu\n", N, O + U);
        assert(k == O);
        assert(n == N);
    }

    shuffle(reps.begin(), reps.end(), r);

    for (size_t u = 0; u < U / 2; u++) {
        sequence.push_back(unique[u * 2]);
        sequence.push_back(unique[u * 2 + 1]);
        sequence.push_back(reps[u]);
    }

    for (int i = 0; sequence.size() < N; i++) {
        sequence.push_back(sequence[i]);
    }

    return sequence;
}

// TIPO 9 (The output is a series of perfect pangrams (exactly one letter for each alphabet))
// separated by maximum X letters
vector<int> gen_perfect_pangram(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    vector<int> buffer(k);
    iota(buffer.begin(), buffer.end(), 0);
    shuffle(buffer.begin(), buffer.end(), r);

    assert(argc == 1);
    int X = atoi(argv[0]);
    assert(X <= k);

    uniform_int_distribution<int> g(0, X);

    while (buffer.size() < n) {
        int s = min(g(r), (int) (n - buffer.size()));

        assert(s <= k);

        vector<int> shuffled(buffer.begin() + buffer.size() - k, buffer.begin() + buffer.size() - k + s);
        shuffle(shuffled.begin(), shuffled.end(), r);
        buffer.insert(buffer.end(), shuffled.begin(), shuffled.end());
    }
    return buffer;
}

/*
    Generatore cattivo.
    Usa meta delle lettere per controllare la lunghezza dei pangrammi.
    L'altra metà per avere molte evidenziazioni.
 */
vector<int> gen_hard(size_t &n, size_t &k, mt19937& r, size_t argc, char** argv) {
    assert(argc == 1);
    int L = atoi(argv[0]);
    assert(k%2 == 0);
    assert(L >= 3*k/2);

    vector<int> all_letters(k);
    iota(all_letters.begin(), all_letters.end(), 0);
    shuffle(all_letters.begin(), all_letters.end(), r);

    uniform_int_distribution<int> g(k/2, k-1);

    int missing;
    vector<int> count(k);
    vector<int> buffer(0);

    // INITIALIZE

    missing = 0;
    for(int i = 1; i < k/2; i++) {
        // pivots
        buffer.push_back(i);
        count[i]++;
    }

    for(int i = k/2; i < k; i++) {
        // fillers
        buffer.push_back(i);
        buffer.push_back(i);
        count[i] += 2;
    }

    while(buffer.size() < L-1) {
        int to_add = g(r);
        buffer.push_back(to_add);
        count[to_add]++;
    }

    shuffle(buffer.begin() + 1, buffer.end(), r);

    // LOOP

    while (buffer.size() < n) {
        int to_remove = buffer[buffer.size() - L + 1];

        int to_add;
        if(to_remove < k/2) {
            to_add = missing;
            missing = to_remove;
        } else if(count[to_remove] <= 2) {
            assert(count[to_remove] == 2);
            to_add = to_remove;
        } else {
            to_add = g(r);
        }

        buffer.push_back(to_add);
        count[to_add]++;
        count[to_remove]--;
    }

    return buffer;
}

map<string, function<vector<int>(size_t&, size_t&, mt19937&, size_t, char**)>> generator = {
    { "random", gen_random },
    { "binary", gen_binary },
    { "single", gen_single },
    { "cycles", gen_cycles },
    { "permutation", gen_permutation },
    { "smile", gen_smile },
    { "hrep", gen_hrep },
    { "exact_solution", gen_exact_solution },
    { "multiple_freqs", gen_multiple_freqs },
    { "perfect_pangram", gen_perfect_pangram },
    { "hard", gen_hard },
};

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE *fin = fopen(argv[1], "r");
        int V;
        assert(fin);
        while (fscanf(fin, "%d", &V) == 1) {
            int ret = fwrite(&V, sizeof(int), 1, stdout);
            assert(ret == 1);
        }
        return 0;
    }

    assert(argc >= 5);
    size_t n = atoi(argv[1]);
    size_t k = atoi(argv[2]);
    int seed = atoi(argv[3]);
    // int shuf = atoi(argv[4]);
    const char* mtype = argv[4];
    mt19937 r(seed);
    size_t ret;
    assert(generator.count(mtype));
    vector<int> p = generator[mtype](n, k, r, argc - 5, argv + 5);
    // if(shuf) {
    //     map_random(p, r);
    // }
    int _n = n;
    ret = fwrite(&_n, sizeof(int), 1, stdout);
    assert(ret == 1);
    int _k = k;
    ret = fwrite(&_k, sizeof(int), 1, stdout);
    assert(ret == 1);
    for(size_t i = 0; i < n; i++) {
        ret = fwrite(&p[i], sizeof(int), 1, stdout);
        assert(ret == 1);
    }
    return 0;
}
