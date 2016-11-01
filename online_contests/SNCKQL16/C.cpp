#include <bits/stdc++.h>

using namespace std;

/*
const int N = 1 << 16;

int dp[N];

int sg(int n) {
    if (n == 0) return 0;
    if (dp[n] != -1) return dp[n];
    vector<bool> vis(6, false);
    for (int i = 2; i <= 6; ++i) {
        int ret = sg(n / i);
        if (ret < 6) vis[ret] = true;
    }
    for (int i = 0; i < 6; ++i) {
        if (!vis[i]) {
            return dp[n] = i;
        }
    }
}
*/

const int mul[] = {2, 2, 1, 3};

int calcsg(long long n) {
    if (n == 0) return 0;
    int i = 1;
    long long l = 1;
    while (n > l) {//cerr << i << ' ' << l << endl;
        n -= l;
        l *= mul[i];
        i = (i + 1) % 4;
    }
    return i;
}

int main() {
    /*
    memset(dp, -1, sizeof dp);
    int lastsg = -1, cnt = 0;
    for (int n = 1; n < N; ++n) {
        if (sg(n) != sg(n - 1)) {
            cout << lastsg << ' ' << cnt << endl;
            cnt = 1;
            lastsg = sg(n);
        } else {
            cnt++;
        }
    }
    cout << lastsg << ' ' << cnt << endl;
    */
    //calcsg(1000000000000000000LL);
    int testCount;
    cin >> testCount;
    for (int testId = 1; testId <= testCount; ++testId) {
        int n;
        cin >> n;
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            long long A;
            cin >> A;
            ret ^= calcsg(A);
        }
        puts(ret ? "Henry" : "Derek");
    }
}

