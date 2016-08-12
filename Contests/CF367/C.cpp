#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()

template<typename T>
inline void checkmin(T &a, T b) {
    if (a == -1 || b < a) {
        a = b;
    }
}

template<typename T>
inline void checkmax(T &a, T b) {
    if (b > a) {
        a = b;
    }
}

typedef long long ll;

const int maxn = 100000 + 10;
const ll inf = (int)1e18;

int n, c[maxn];
ll dp[maxn][2];

int main() {
    cin >> n;
    vector<vector<string>> vs(n, vector<string>(2));
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> vs[i][0];
        vs[i][1] = vs[i][0];
        reverse(vs[i][1].begin(), vs[i][1].end());
    }
    for (int i = 0; i < 2; ++i) {
        dp[0][i] = i * c[0];
    }
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i][1] = -1;
        for (int j = 0; j < 2; ++j) if (dp[i - 1][j] != -1) {
            for (int k = 0; k < 2; ++k) {
                if (vs[i][k] >= vs[i - 1][j]) {
                    checkmin(dp[i][k], dp[i - 1][j] + k * c[i]);
                }
            }
        }
    }
    ll res = -1;
    for (int i = 0; i < 2; ++i) if (dp[n - 1][i] != -1) {
        checkmin(res, dp[n - 1][i]);
    }
    cout << res << endl;
}

