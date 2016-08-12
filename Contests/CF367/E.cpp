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

const int N = 1 << 20;

int lc[N], rc[N], fa[N], size[N], v[N];

inline void update(int x) {
    size[x] = size[lc[x]] + size[rc[x]] + 1;
}

inline void right(int x, int y) {
    lc[y] = rc[x];
    if (lc[y]) fa[lc[y]] = y;
    rc[x] = y;
    fa[x] = fa[y];
    if (fa[y]) {
        if (y == lc[fa[y]]) {
            lc[fa[x]] = x;
        } else if (y == rc[fa[y]]) {
            rc[fa[x]] = x;
        }
    }
    fa[y] = x;
    update(y);
    update(x);
}

inline void left(int x, int y) {
    rc[y] = lc[x];
    if (rc[y]) fa[rc[y]] = y;
    lc[x] = y;
    fa[x] = fa[y];
    if (fa[y]) {
        if (y == lc[fa[y]]) {
            lc[fa[x]] = x;
        } else if (y == rc[fa[y]]) {
            rc[fa[x]] = x;
        }
    }
    fa[y] = x;
    update(y);
    update(x);
}

void splay(int t) {
    while (fa[t]) {
        int f = fa[t];
        if (fa[f] == 0) {
            if (t == lc[f]) {
                right(t, f);
            } else {
                left(t, f);
            }
        } else {
            int ff = fa[f];
            if (f == lc[ff]) {
                if (t == lc[f]) {
                    right(f, ff);
                    right(t, f);
                } else {
                    left(t, f);
                    right(t, ff);
                }
            } else {
                if (t == rc[f]) {
                    left(f, ff);
                    left(t, f);
                } else {
                    right(t, f);
                    left(t, ff);
                }
            }
        }
    }
}

void split(int t, int k, int &x, int &y) {
    if (k == 0) {
        x = 0;
        y = t;
    } else if (k == size[t]) {
        x = t;
        y = 0;
    } else {
        while (true) {
            if (size[lc[t]] >= k) {
                t = lc[t];
            } else {
                k -= size[lc[t]] + 1;
                if (k == 0) break;
                t = rc[t];
            }
        }
        splay(t);
        x = t;
        y = rc[t];
        fa[y] = 0;
        rc[x] = 0;
        update(x);
    }
}

int join(int x, int y) {
    if (x == 0 || y == 0) {
        return x + y;
    }
    while (rc[x]) x = rc[x];
    splay(x);
    fa[y] = x;
    rc[x] = y;
    update(x);
    return x;
}

int row[1 << 10];

int build(int l, int r) {
    if (l > r) return 0;
    int mid = (l + r) / 2;
    lc[mid] = build(l, mid - 1);
    rc[mid] = build(mid + 1, r);
    fa[lc[mid]] = fa[rc[mid]] = mid;
    update(mid);
    return mid;
}

void dfs(int t) {
    if (!t) return;
    dfs(lc[t]);
    printf("%d ", v[t]);
    dfs(rc[t]);
}

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n * m; ++i) {
        scanf("%d", v + i);
    }
    for (int i = 1; i <= n; ++i) {
        row[i] = build(m * (i - 1) + 1, m * i);
    }
    for (int i = 0; i < q; ++i) {
        int a, b, c, d, h, w;
        scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &h, &w);
        for (int j = 0; j < h; ++j) {
            int p1, p2, p3, p4, q1, q2, q3, q4;
            if (a != c) {
                split(row[j + a], b - 1, p1, p2);
                split(p2, w, p3, p4);
                split(row[j + c], d - 1, q1, q2);
                split(q2, w, q3, q4);
                row[j + a] = join(join(p1, q3), p4);
                row[j + c] = join(join(q1, p3), q4);
            } else {
                if (b > d) swap(b, d);
                split(row[j + a], b - 1, p1, p2);
                split(p2, w, p3, p4);
                split(p4, d - 1 - (b + w - 1), q1, q2);
                split(q2, w, q3, q4);
                row[j + a] = join(join(join(join(p1, q3), q1), p3), q4);
            }
            //cerr << size[row[j + a]] << ' ' << size[row[j + c]] << endl;
        }
    }
    for (int i = 1; i <= n; ++i) {
        dfs(row[i]);
        puts("");
    }
}

