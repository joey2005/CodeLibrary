#include <bits/stdc++.h>

using namespace std;

void extendedKMP(char a[], char b[], int m, int n, int ret[]) {
    int N = m + n + 1;
    vector<int> s(N + 1);
    for (int i = 0; i < m; ++i) s[i] = a[i];
    s[m] = 1000000000;
    for (int i = 0; i < n; ++i) s[m + 1 + i] = b[i];
    vector<int> next(N + 1, 0);
    next[1] = 0;
    for (int &j = next[1]; 1 + j < m && s[j] == s[1 + j]; ++j);
    int best = 1;
    for (int i = 2; i < N; ++i) {
        int LL = best + next[best], L = next[i - best];
        if (L < LL - i) {
            next[i] = L;
        } else {
            next[i] = max(0, LL - i);
            for (int &j = next[i]; i + j < N && s[j] == s[i + j]; ++j);
            best = i;
        }
    }
    for (int i = 0; i < n; ++i) ret[i] = next[m + 1 + i];
}

int main() {
}
