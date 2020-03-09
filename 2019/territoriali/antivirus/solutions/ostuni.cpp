#include <iostream>
#include <string>
#include <unordered_set>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int c = 1; c <= t; c++) {
        int m;
        array<string, 4> s;
        array<vector<string>, 4> h;
        unordered_multiset<string> ss;
        string answer;
        for(int i = 0; i < 4; i++) {
            int garbage;
            cin >> garbage;
        }
        cin >> m;
        for(int i = 0; i < 4; i++) {
            cin >> s[i];
            for(int j = 0; j < s[i].size() - m + 1; j++) {
                h[i].emplace_back(s[i], j, m);
            }
            sort(h[i].begin(), h[i].end());
            auto last = unique(h[i].begin(), h[i].end());
            h[i].erase(last, h[i].end());
            for(const auto& x: h[i]) {
                ss.insert(x);
                if(ss.count(x) == 4) {
                    answer = x;
                }
            }
        }
        assert(answer != "");
        cout << "Case #" << c << ": ";
        for(int i = 0; i < 4; i++) {
            cout << s[i].find(answer) << " ";
        }
        cout << endl;
    }
}
