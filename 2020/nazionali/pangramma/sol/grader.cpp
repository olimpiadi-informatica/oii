#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#ifdef __APPLE__
    #define fread_unlocked fread
#endif

using namespace std;

int conta(int n, int k, vector<int>& v);

int main() {
    size_t r;
    int n, k;
    r = fread_unlocked(&n, sizeof(int), 1, stdin);
    assert(r == 1);
    r = fread_unlocked(&k, sizeof(int), 1, stdin);
    assert(r == 1);
    vector<int> v(n);
    int already_read = 0;
    while(already_read < n) {
        already_read += fread_unlocked(v.data() + already_read, sizeof(int), n - already_read, stdin);
    }
    cout << conta(n, k, v) << endl;
    return EXIT_SUCCESS;
}
