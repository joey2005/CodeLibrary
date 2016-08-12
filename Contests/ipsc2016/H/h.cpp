#include <bits/stdc++.h>

using namespace std;

const int maxn = 10000000 + 10;
const int maxq = 25000000 + 10;
const long long md = (long long)1e9 + 7;

long long sum[maxn << 2];
bool fz[maxn << 2];
long long fa[maxn << 2], fa_rev[maxn << 2], cover[maxn << 2];
int len[maxn << 2];
int n, q;

inline long long cnt(long long len) {
    return len * (len + 1) / 2 % md;
}

inline void pushdown(int i) {
    if (fz[i]) {
        fz[i * 2] = true;
        fa[i * 2] = fa_rev[i * 2] = cover[i * 2] = 0;
        sum[i * 2] = 0;
        fz[i * 2 + 1] = true;
        fa[i * 2 + 1] = fa_rev[i * 2 + 1] = cover[i * 2 + 1] = 0;
        sum[i * 2 + 1] = 0;
        fz[i] = false;
        //return;
    }
    if (fa[i]) {
        fa[i * 2] += fa[i];
        cover[i * 2] += len[i * 2 + 1];
        cover[i * 2] %= md;
        sum[i * 2] += cnt(len[i * 2]);
        sum[i * 2] += (long long)len[i * 2] * len[i * 2 + 1];
        sum[i * 2] %= md;
        fa[i * 2 + 1] += fa[i];
        cover[i * 2 + 1] += 0;
        sum[i * 2 + 1] += cnt(len[i * 2 + 1]);
        sum[i * 2 + 1] += (long long)len[i * 2 + 1] * 0;
        sum[i * 2 + 1] %= md;
        fa[i] = 0;
    }
    if (fa_rev[i]) {
        fa_rev[i * 2 + 1] += fa_rev[i];
        cover[i * 2 + 1] += len[i * 2];
        cover[i * 2 + 1] %= md;
        sum[i * 2 + 1] += cnt(len[i * 2 + 1]);
        sum[i * 2 + 1] += (long long)len[i * 2 + 1] * len[i * 2];
        sum[i * 2 + 1] %= md;
        fa_rev[i * 2] += fa_rev[i];
        cover[i * 2] += 0;
        sum[i * 2] += cnt(len[i * 2]);
        sum[i * 2] += (long long)len[i * 2] * 0;
        sum[i * 2] %= md;
        fa_rev[i] = 0;
    }
    if (cover[i]) {
        cover[i * 2] += cover[i];
        cover[i * 2] %= md;
        sum[i * 2] += cover[i] * len[i * 2];
        sum[i * 2] %= md;
        cover[i * 2 + 1] += cover[i];
        cover[i * 2 + 1] %= md;
        sum[i * 2 + 1] += cover[i] * len[i * 2 + 1];
        sum[i * 2 + 1] %= md;
        cover[i] = 0;
    }
}

void build(int i, int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
    }
    len[i] = r - l + 1;
    fz[i] = false;
    fa[i] = fa_rev[i] = cover[i] = 0;
    sum[i] = 0;
}

long long query(int i, int l, int r, int x, int y) {
    if (x > r || y < l) {
        return 0;
    }
    if (x <= l && y >= r) {
        return sum[i];
    }
    int mid = (l + r) / 2;
    pushdown(i);
    //cerr << "!!!" << l << ' ' << r << ' ' << x << ' ' << y << '=' << sum[i] << ' ' << sum[i * 2] << ' ' << sum[i * 2 + 1] << endl;
    long long cur = 0;
    cur += query(i * 2, l, mid, x, y);
    cur += query(i * 2 + 1, mid + 1, r, x, y);
    cur %= md;
    return cur;
}

void add(int i, int l, int r, int x, int y) {
    if (x > r || y < l) {
        return;
    }
    if (x <= l && y >= r) {
        long long add = (y - x + 1) - (l - x) - len[i];
        /*
        if (l == 1 && r == 2 && x == 1 && y == 3) {
            cerr << y - x + 1 << ' ' << l - x << ' ' << len[i] << endl;
            cerr << "!!" << add << endl;
        }
        */
        sum[i] += cnt(len[i]);
        sum[i] += add * len[i];
        sum[i] %= md;
        fa[i] += 1;
        cover[i] += add;
        cover[i] %= md;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(i);
    add(i * 2, l, mid, x, y);
    add(i * 2 + 1, mid + 1, r, x, y);
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
    sum[i] %= md;
}

void add_rev(int i, int l, int r, int x, int y) {
    if (x > r || y < l) {
        return;
    }
    if (x <= l && y >= r) {
        long long add = (y - x + 1) - (y - r) - len[i];
        sum[i] += cnt(len[i]);
        sum[i] += add * len[i];
        sum[i] %= md;
        fa_rev[i] += 1;
        cover[i] += add;
        cover[i] %= md;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(i);
    add_rev(i * 2, l, mid, x, y);
    add_rev(i * 2 + 1, mid + 1, r, x, y);
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
    sum[i] %= md;
}

void raise(int i, int l, int r, int x, int y, long long v) {
    if (x > r || y < l) {
        return;
    }
    if (x <= l && y >= r) {
        sum[i] += v * len[i];
        sum[i] %= md;
        cover[i] += v;
        cover[i] %= md;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(i);
    raise(i * 2, l, mid, x, y, v);
    raise(i * 2 + 1, mid + 1, r, x, y, v);
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
    sum[i] %= md;
}

void zero(int i, int l, int r, int x, int y) {
    if (x > r || y < l) {
        return;
    }
    if (x <= l && y >= r) {
        sum[i] = 0;
        fz[i] = true;
        fa[i] = fa_rev[i] = cover[i] = 0;
        return;
    }
    int mid = (l + r) / 2;
    pushdown(i);
    zero(i * 2, l, mid, x, y);
    zero(i * 2 + 1, mid + 1, r, x, y);
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
    sum[i] %= md;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t-- > 0) {
        int a, b, c;
        scanf("%d%d", &n, &q);
        for (int i = 0; i < n - 1; ++i) {
            scanf("%d%d", &a, &b);
        }
        build(1, 1, n - 1);
        long long ans = 0;
        for (int qq = 1; qq <= q; ++qq) {
            scanf("%d%d%d", &a, &b, &c);
            long long cur = 0;
            if (c == 1) {
                if (a < b) {
                    cur += query(1, 1, n - 1, a, b - 1);
                    cur += cnt(b - a - 1);
                    zero(1, 1, n - 1, a, b - 1);
                    add(1, 1, n - 1, a, b - 1);
                    raise(1, 1, n - 1, 1, a - 1, b - a);
                    raise(1, 1, n - 1, b, n - 1, b - a);
                } else {
                    cur += query(1, 1, n - 1, b, a - 1);
                    cur += cnt(a - b - 1);
                    zero(1, 1, n - 1, b, a - 1);
                    add_rev(1, 1, n - 1, b, a - 1);
                    raise(1, 1, n - 1, 1, b - 1, a - b);
                    raise(1, 1, n - 1, a, n - 1, a - b);
                }
            } else {
                if (a < b) {
                    cur += query(1, 1, n - 1, a, b - 1);
                    zero(1, 1, n - 1, a, b - 1);
                } else {
                    cur += query(1, 1, n - 1, b, a - 1);
                    zero(1, 1, n - 1, b, a - 1);
                }
            }
            //cerr << '!' << sum[1] << endl;
            cur %= md;
            ans = (ans + qq * cur) % md;
            //cerr << cur << endl;
        }
        printf("%d\n", (int)ans);
    }
}

