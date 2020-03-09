// Soluzione O(S³), per ogni inizio i e fine j controlla se p in s[i, ..., j]

long long conta(int S, int s[], int P, int p[]) {
    auto check = [&](int l, int r) {
        int j = 0;
        for (int i = l; i <= r && j < P; i++)
            if (s[i] == p[j])
                j++;
        return j == P;
    };
    long long sol = 0;
    for (int l = 0; l < S; l++)
        for (int r = l; r < S; r++)
            if (check(l, r))
                sol++;
    return sol;
}
