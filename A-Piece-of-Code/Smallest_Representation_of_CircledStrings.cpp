#include <bits/stdc++.h>

using namespace std;

string getSmallest(string _s) {
    int L = _s.size(), i, j, k, l;
    string s = _s + _s;
    for (i = 0, j = 1; j < L; ) {
        for (k = 0; k < L && s[i + k] == s[j + k]; k ++);
        if (k >= L) break;
        if (s[i + k] < s[j + k]) {
            j += k + 1;
        } else {
            l = i + k;
            i = j;
            j = max(l, j) + 1;
        }
    }
    return s.substr(i, L);
}

int main() {
}
