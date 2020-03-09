#include <vector>
#include <unordered_map>
#include <cassert>
// #include <cstdio>

using namespace std;

const long long MOD = 46'337;
const int MAX_SOL = 1'000'000'000;

int min_length(std::vector<int>& v, const int k) {
    vector<int> count(k);
    int taken = 0;
    int l = 0;
    int m = v.size();
    for (int i = 0; i < v.size(); i++) {
        // add element
        if (count[v[i]] == 0) {
            taken++;
        }
        count[v[i]]++;

        // remove useless
        while (count[v[l]] > 1) {
            count[v[l]]--;
            l++;
        }

        if (taken == k) {
            m = min(m, i-l+1);
        }
    }
    return m;
}

class segment_t {
    vector<long long> node;
    const int n;

    void update(int delta, int i, int l, int r, int pos) {
        // outside
        if (i < l || i > r) {
            return;
        }

        // leaf
        if (l == r) {
            node[pos] += delta;
            return;
        }

        update(delta, i, l, (l+r)/2, pos*2);
        update(delta, i, (l+r)/2+1, r, pos*2+1);

        if(node[pos*2] == -1 && node[pos*2+1] == -1) {
            node[pos] = -1;
        } else {
            node[pos] = (1ll * node[pos*2] * node[pos*2+1]);
        }

        if(node[pos] > MAX_SOL || node[pos] < 0) {
            node[pos] = -1;
        }
    }

    public:
    segment_t(int _n) : n(_n) {
        node.resize(4*n);
    }

    void add(int v) {
        update(1, v, 0, n-1, 1);
    }

    void remove(int v) {
        update(-1, v, 0, n-1, 1);
    }

    int get_mult() {
        return node[1];
    }
};

int conta(int n, int k, std::vector<int>& v) {

    int m = min_length(v, k);

    segment_t st(k);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        st.add(v[i]);
        if (i >= m) {
            st.remove(v[i-m]);
        }

        assert(st.get_mult() != -1);
        res += st.get_mult();
    }

    return res % MOD;
}
