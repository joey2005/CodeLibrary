#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

long long a[N], prefix[N], suffix[N];
int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    prefix[0] = 0;
    for (int i = 1; i <= n; ++i) {
        prefix[i] = max(0LL, prefix[i - 1]) + a[i];
    }
    suffix[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
        suffix[i] = max(0LL, suffix[i + 1]) + a[i];
    }
    long long ret = -(1LL << 60);
    for (int i = 1; i <= n; ++i) {
        ret = max(ret, prefix[i]);
        if (i < n) {
            ret = max(ret, max(0LL, prefix[i - 1]) + suffix[i + 1]);
        } else {
            ret = max(ret, prefix[i - 1] + suffix[i + 1]);
        }
        if (i > 1) {
            ret = max(ret, max(0LL, suffix[i + 1]) + prefix[i - 1]);
        } else {
            ret = max(ret, suffix[i + 1] + prefix[i - 1]);
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
