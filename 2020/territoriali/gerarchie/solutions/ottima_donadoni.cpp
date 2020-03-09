#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int gerarchie(vector<int> up, vector<int> values) {
    int N = up.size();

    vector<int> value_to_node(N);
    for (int i = 0; i < N; ++i) {
        value_to_node[values[i]] = i;
    }

    vector<int> values_order(values.begin(), values.end());
    sort(values_order.begin(), values_order.end(), greater<int>());

    int count = 0;
    for (int v : values_order) {
        int i = value_to_node[v];
        while (up[i] != -1 && values[up[i]] < values[i]) {
            int u = up[i];
            int vu = values[u];
            // scambio u con i
            value_to_node[vu] = i;
            value_to_node[v] = u;
            values[i] = vu;
            values[u] = v;
            i = u;
            count++;
        }
    }
    return count;
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        vector<int> parents(N), values(N);
        for (int i = 0; i < N; ++i) {
            cin >> parents[i] >> values[i];
        }
        cout << "Case #" << t << ": " << gerarchie(parents, values) << endl;
    }
}
