#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1, 0), b(n);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        if (b[i] <= a[i + 1] - a[i]) {
            ret++;
        }
    }
    cout << ret << endl;
}

int main() {
    int testCount;
    cin >> testCount;
    for (int testId = 1; testId <= testCount; ++testId) {
        solve();
    }
}

