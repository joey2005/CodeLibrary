#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

char s[N];
int cnt[300];
int n, k;

void solve() {
    cin >> s >> k;
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; s[i]; ++i) {
        cnt[s[i]]++;
    }
    vector<int> cnts;
    for (int i = 0; i < 300; ++i) {
        if (cnt[i]) {
            cnts.push_back(cnt[i]);
        }
    }
    n = cnts.size();
    int ret = 1 << 30;
    for (int i = 1; i < N; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (cnts[j] < i) {
                count += cnts[j];
            } else {
                count += max(0, cnts[j] - (i + k));
            }
        }
        ret = min(ret, count);
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
