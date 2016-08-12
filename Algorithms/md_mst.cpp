/*
曼哈顿最小生成树
只需要考虑每个点的 pi/4*k -- pi/4*(k+1)的区间内的第一个点，这样只有4n条无向边。 
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 110000;

struct Point {
    int x, y, id;
} a[maxn];

int N;
int father[maxn];

void Rotate(Point &a) {
    int t = a.x;
    a.x = -a.y;
    a.y = t;
}

int find(int x) {
    int t, tt;
    for (t = x; father[t] >= 0; t = father[t]);
    for (; father[x] >= 0; ) {
        tt = father[x];
        father[x] = t;
        x = tt;
    }
    return t;
}

void Union(int x, int y) {
    if (-father[x] > -father[y]) swap(x, y);
    father[y] += father[x];
    father[x] = y;
}

struct Edge {
    int x, y, z;

    Edge() {
    }

    Edge(int x, int y, int z): x(x), y(y), z(z) {
    }

    bool operator <(const Edge &a) const {
        return z < a.z;
    }
};

vector<Edge> edges;

void Kruskal() {
    sort(edges.begin(), edges.end());
    for (int i = 0; i < N; ++i) father[i] = -1;
    long long ans = 0;
    for (int i = 0, kn = 0; i < edges.size() && kn < N - 1; i++) {
        int kx = find(edges[i].x), ky = find(edges[i].y);
        if (kx != ky) {
            ans += edges[i].z;
            Union(kx, ky);
            kn++;
        }
    }
    printf("%lld\n", ans);
}

const int inf = INT_MAX / 3;

Point cp[maxn];
int dp[maxn], rec[maxn], yl[maxn];

bool cmp(const Point &a, const Point &b) {
    return a.y - a.x < b.y - b.x || a.y - a.x == b.y - b.x && a.y > b.y;
}

inline int lowbit(int x) {
    return (x & (-x));
}

inline int calc(const Point &s, const Point &t) {
    return abs(s.x - t.x) + abs(s.y - t.y);
}

void Work() {
    for (int i = 0; i < N; ++i) {
        cp[i] = a[i];
    }
    for (int i = 0; i < N; ++i) {
        yl[i] = cp[i].y;
    }
    sort(yl, yl + N);
    int tot = unique(yl, yl + N) - yl;

    sort(cp, cp + N, cmp);
    for (int i = 1; i <= tot; ++i) dp[i] = inf;
    for (int i = 0; i < N; ++i) {
        int id = -1, res = inf;
        int pos = 1 + (int)(lower_bound(yl, yl + tot, cp[i].y) - yl);
        for (int x = pos; x <= tot; x += lowbit(x)) {
            if (dp[x] < res) {
                res = dp[x];
                id = rec[x];
            }
        }
        if (id != -1) {
            edges.push_back(Edge(cp[i].id, id, calc(a[cp[i].id], a[id])));
        }
        res = cp[i].x + cp[i].y;
        for (int x = pos; x > 0; x -= lowbit(x)) {
            if (res < dp[x]) {
                dp[x] = res;
                rec[x] = cp[i].id;
            }
        }
    }
}

void main2() {
    for (int i = 0; i < N; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].id = i;
    }
    edges.clear();
    //case 1
    Work();
    //case 2
    for (int j = 0; j < N; ++j) swap(a[j].x, a[j].y);
    Work();
    //case 3
    for (int j = 0; j < N; ++j) swap(a[j].x, a[j].y);
    for (int j = 0; j < N; ++j) {
        Rotate(a[j]);
    }
    Work();
    //case 4
    for (int j = 0; j < N; ++j) swap(a[j].x, a[j].y);
    Work();

    Kruskal();
}

int main() {
    for (int caseId = 1; scanf("%d", &N) == 1 && N; caseId++) {
        printf("Case %d: Total Weight = ", caseId);
        main2();
    }
}

