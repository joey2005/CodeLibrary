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

const int inf = 1 << 30;

multiset<pair<int, int>> sets[31];

void insert(int x) {
    for (int i = 0; i <= 30; ++i) {
        sets[i].emplace(x >> i, x);
    }
}

void remove(int x) {
    for (int i = 0; i <= 30; ++i) {
        sets[i].erase(sets[i].lower_bound(make_pair(x >> i, x)));
    }
}

void query(int x) {
    int res = 0;
    for (int i = 30; i >= 0; --i) {
        res = res * 2 + 1;
        multiset<pair<int, int>>::iterator it = sets[i].lower_bound(make_pair(res ^ (x >> i), -inf));
        if (it != sets[i].end() && it->first == (res ^ (x >> i))) {
            //cerr << '!' << x << ' ' << i << ' ' << res << ' ' << (res ^ (x >> i)) << endl;
            continue;
        }
        res ^= 1;
    }
    printf("%d\n", res);
}

int main() {
    insert(0);
    int n, x;
    scanf("%d", &n);
    while (n-- > 0) {
        char op[10];
        scanf("%s%d", op, &x);
        if (*op == '+') {
            insert(x);
        } else if (*op == '-') {
            remove(x);
        } else {
            query(x);
        }
    }
}

