#include <vector>
#include <iostream>
#include <assert.h>
typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

std::vector<int> compute_fall(int end, int* altezze, int N) {
    std::vector<int> fall_until(N);
    fall_until[end-1] = altezze[end-1] + end-1;
    for (int i=end-2; i>-1; i--) {
        int j = i+1;
        while (j < i+altezze[i] && j < end) {
            j = fall_until[j];
        }
        fall_until[i] = std::max(j, i+altezze[i]);
    }
    return fall_until;
}

std::vector<int> log2{-1};
typedef std::vector<std::vector<int>> rmq_t;

rmq_t prepare_rmq(const std::vector<int>& base) {
    while (log2.size() <= base.size()) {
        log2.push_back(log2[log2.size()/2]+1);
    }
    rmq_t data(log2[base.size()]+1);
    data[0] = base;
    for (int e=1; e<log2[base.size()]+1; e++) {
        for (int i=0; i<(int)base.size()-(1<<e)+1; i++) {
            data[e].push_back(std::max(data[e-1][i], data[e-1][i+(1<<(e-1))]));
        }
    }
    return data;
}

int max(int a, int b, const rmq_t& rmq) {
    if (b > (int)rmq[0].size()) b = rmq[0].size();
    if (a == b) return 0;
    int ans = 0;
    int level = log2[b-a];
    ans = std::max(rmq[level][a], rmq[level][b-(1<<level)]);
    return ans;
}

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
    auto final_fall = compute_fall(N, altezze, N);
    if (final_fall[0] > N-1) return OK;
    std::vector<int> initial_fall(N, 0);
    int f = 1;
    for (int i=0; i<N; i++) {
        initial_fall[i] = f;
        if (i < f) {
            f = std::max(f, i+altezze[i]);
        }
    }
    rmq_t final_rmq = prepare_rmq(final_fall);
    for (int i=1; i<N; i++) {
        auto middle_fall = compute_fall(i, altezze, N);
        rmq_t middle_rmq = prepare_rmq(middle_fall);
        for (int j=0; j<i; j++) {
            if (initial_fall[j] <= j) break;
            int initial_end = std::max(initial_fall[j], j+altezze[i]);
            int middle_end = max(j+1, initial_end, middle_rmq);
            if (middle_end < initial_end) middle_end = initial_end;
            if (middle_end <= i) continue;
            if (middle_end < i+altezze[j]) middle_end = i+altezze[j];
            int final_end = max(i+1, middle_end, final_rmq);
            if (final_end < middle_end) final_end = middle_end;
            if (final_end > N-1) {
                scambio->domino1 = j;
                scambio->domino2 = i;
                return RISOLTO;
            }
        }
    }
    return IMPOSSIBILE;
}
