#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()

template<typename T>
inline void checkmin(T &a, T b) {
    if (b < a) {
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

const int maxn = (int)1e5 + 10;

int n, x[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", x + i);
    }
    sort(x, x + n);
    int q;
    for (scanf("%d", &q); q-- > 0; ) {
        int coins;
        scanf("%d", &coins);
        printf("%d\n", (int)(upper_bound(x, x + n, coins) - x));
    }
}

