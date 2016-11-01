#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()

template<typename T> inline bool checkmin(T &a, T b) { if (b < a) { a = b; return 1; } return 0; }
template<typename T> inline bool checkmax(T &a, T b) { if (b > a) { a = b; return 1; } return 0; }

typedef long long ll;

const int N = (int)3e5 + 10;

int n, q, wei[N], lc[N], rc[N], fa[N], rev[N];
ll add[N], maximum[N];

// splay
inline bool isroot(int x) {
    if (fa[x] == 0) return true;
    return x != lc[fa[x]] && x != rc[fa[x]];
}
inline void push(int x) {
    if (rev[x]) {
        if (lc[x]) rev[lc[x]] ^= 1;
        if (rc[x]) rev[rc[x]] ^= 1;
        swap(lc[x], rc[x]);
        rev[x] = 0;
    }
    if (add[x]) {
        if (lc[x]) wei[lc[x]] += add[x], add[lc[x]] += add[x], maximum[lc[x]] += add[x];
        if (rc[x]) wei[rc[x]] += add[x], add[rc[x]] += add[x], maximum[rc[x]] += add[x];
        add[x] = 0;
    }
}
inline void update(int x) {
    maximum[x] = wei[x];
    if (lc[x]) maximum[x] = max(maximum[x], maximum[lc[x]]);
    if (rc[x]) maximum[x] = max(maximum[x], maximum[rc[x]]);
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
    vector<int> v;
    v.emplace_back(t);
    for (int x = t; !isroot(x); x = fa[x]) v.emplace_back(fa[x]);
    reverse(ALL(v));
    for (int x : v) {
        push(x);
    }
    for (; !isroot(t); ) {
        int f = fa[t];
        if (isroot(f)) {
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
// link cut tree
int access(int u) {
    int v = 0;
    for (; u; u = fa[u]) splay(u), rc[u] = v, update(u), v = u;
    for (; lc[v]; v = lc[v]);
    return v;
}

void addEdge(int x, int y) {
    int fx = access(x);
    int fy = access(y);
    if (fx == fy) {
        puts("-1");
    } else {
        access(x);
        splay(x);
        rc[x] = 0;
        fa[x] = y;
        rev[x] = true;
        push(x);
        update(x);
    }
}

void removeEdge(int x, int y) {
    int fx = access(x);
    int fy = access(y);
    if (fx != fy || x == y) {
        puts("-1");
    } else {
        // x becomes the root of its tree
        access(x);
        splay(x);
        rc[x] = 0;
        fa[x] = 0;
        rev[x] = true;
        push(x);
        update(x);

        // remove edges between y and y's parent
        access(y);
        splay(y);
        fa[lc[y]] = 0;
        lc[y] = 0;
        update(y);
    }
}

void modify(int x, int y, int w) {
    int fx = access(x);
    int fy = access(y);
    if (fx != fy) {
        puts("-1");
    } else {
        for (int u = x, v = 0; u; u = fa[u]) {
            splay(u);
            if (fa[u] == 0) {
                if (rc[u]) {
                    wei[rc[u]] += w;
                    add[rc[u]] += w;
                    maximum[rc[u]] += w;
                    push(rc[u]);
                    update(rc[u]);
                }
                if (v && v != rc[u]) {
                    wei[v] += w;
                    add[v] += w;
                    maximum[v] += w;
                    push(v);
                    update(v);
                }
                wei[u] += w;
                update(u);
                break;
            }
            rc[u] = v; update(u); v = u;
        }
    }
}

void query(int x, int y) {
    int fx = access(x);
    int fy = access(y);
    if (fx != fy) {
        puts("-1");
    } else {
        for (int u = x, v = 0; u; u = fa[u]) {
            splay(u);
            if (fa[u] == 0) {
                ll res = wei[u];
                if (rc[u]) res = max(res, maximum[rc[u]]);
                if (v) res = max(res, maximum[v]);
                printf("%lld\n", res);
                break;
            }
            rc[u] = v; update(u); v = u;
        }
    }
}

void resetTree(int n) {
    memset(wei, 0, sizeof wei);
    memset(lc, 0, sizeof lc);
    memset(rc, 0, sizeof rc);
    memset(fa, 0, sizeof fa);
    memset(rev, 0, sizeof rev);
    memset(add, 0, sizeof add);
    memset(maximum, 0, sizeof maximum);
}

int main() {
    while (scanf("%d", &n) == 1) {
        resetTree(n);
        vector<pair<int, int>> tree(n - 1);
        for (int i = 0; i < tree.size(); ++i) {
            scanf("%d%d", &tree[i].first, &tree[i].second);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", wei + i);
        }
        for (int i = 1; i <= n; ++i) {
            maximum[i] = wei[i];
        }
        for (auto &&it : tree) {
            addEdge(it.first, it.second);
        }
        for (scanf("%d", &q); q-- > 0; ) {
            int op, x, y, w;
            scanf("%d", &op);
            switch (op) {
            case 1:
                scanf("%d%d", &x, &y);
                addEdge(x, y);
                break;
            case 2:
                scanf("%d%d", &x, &y);
                removeEdge(x, y);
                break;
            case 3:
                scanf("%d%d%d", &w, &x, &y);
                modify(x, y, w);
                break;
            case 4:
                scanf("%d%d", &x, &y);
                query(x, y);
                break;
            }
        }
        puts("");
    }
}
