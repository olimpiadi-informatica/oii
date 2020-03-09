long long conta(int S, int s[], int P, int p[]) {
    long long sol = 0;
    int right = -1;
    int c = p[0];
    int count = 0;
    for (int left = 0; left < S; count -= s[left] == c, left++) {
        while (right < S && count < P) {
            right++;
            count += s[right] == c;
        }
        if (count == P)
            sol += S-right;
    }
    return sol;
}
