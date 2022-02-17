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

const int maxn = 100024;
const int inf = (int)1e9;

struct Edge {
    int v, f, c, last;
    Edge() {}
    Edge(int v, int f, int c, int last): v(v), f(f), c(c), last(last) {}
};

vector<Edge> edges;
int dist[maxn], head[maxn], info[maxn];
int que[maxn], front, back;
int source, target, vertexCount;

inline void addEdge(int a, int b, int c1, int c2 = 0) {
    edges.emplace_back(b, 0, c1, info[a]);
    info[a] = (int)edges.size() - 1;
    edges.emplace_back(a, 0, c2, info[b]);
    info[b] = (int)edges.size() - 1;
}

int dinic_bfs() {
    memset(dist, -1, sizeof(int) * vertexCount);
    front = back = 0;
    que[back++] = target;
    dist[target] = 0;
    while (front < back) {
        int u = que[front++];
        for (int i = info[u]; i >= 0; i = edges[i].last) {
            int v = edges[i].v;
            if (dist[v] == -1 && edges[i ^ 1].f < edges[i ^ 1].c) {
                que[back++] = v;
                dist[v] = dist[u] + 1;
            }
        }
    }
    return dist[source] != -1;
}

int dinic_dfs(int u, int can) {
    if (u == target) {
        return can;
    }
    int res = 0;
    for (int i = head[u]; i >= 0; i = edges[i].last) {
        int v = edges[i].v;
        if (dist[v] + 1 == dist[u] && edges[i].f < edges[i].c) {
            int w = dinic_dfs(v, min(edges[i].c - edges[i].f, can - res));
            if (w) {
                head[u] = i;
                edges[i].f += w;
                edges[i ^ 1].f -= w;
                res += w;
                if (res == can) {
                    break;
                }
            }
        }
    }
    if (res == 0) {
        dist[u] = -1;
    }
    return res;
}

int dinic() {
    int res = 0, f;
    while (dinic_bfs()) {
        memcpy(head, info, sizeof(int) * vertexCount);
        res += dinic_dfs(source, inf);
    }
    return res;
}

void initFlow(int S, int T, int n) {
    memset(info, -1, sizeof(int) * n);
    edges.clear();
    ::source = S;
    ::target = T;
    ::vertexCount = n;
}

int getId(unordered_map<int, int> &x_map, vector<int> &xs, int x) {
    if (x_map.count(x)) {
        return x_map[x];
    }
    xs.emplace_back(x);
    return x_map[x] = (int)xs.size() - 1;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int cost[2], color[2] = {'r', 'b'};
    for (int i = 0; i < 2; ++i) {
        scanf("%d", cost + i);
    }
    if (cost[0] > cost[1]) {
        swap(cost[0], cost[1]);
        swap(color[0], color[1]);
    }
    vector<int> x(n), y(n);
    unordered_map<int, int> x_map, y_map, x_mind, y_mind;
    vector<int> xs, ys;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        x_mind[x[i]] = inf;
        x[i] = getId(x_map, xs, x[i]);
        y_mind[y[i]] = inf;
        y[i] = getId(y_map, ys, y[i]);
    }
    for (int i = 0; i < m; ++i) {
        int type, l, d;
        scanf("%d%d%d", &type, &l, &d);
        if (type == 1) {
            if (x_mind.count(l)) {
                x_mind[l] = min(x_mind[l], d);
            }
        } else {
            if (y_mind.count(l)) {
                y_mind[l] = min(y_mind[l], d);
            }
        }
    }
    int Nx = x_map.size();
    int Ny = y_map.size();
    int S = Nx + Ny;
    int T = S + 1;
    int superS = S + 2;
    int superT = S + 3;
    initFlow(superS, superT, S + 4);
    vector<int> deg_x(Nx, 0), deg_y(Ny, 0);
    vector<int> eid(n);
    //cerr << Nx << ' ' << Ny << endl;
    for (int i = 0; i < n; ++i) {
        //cerr << x[i] << ' ' << y[i] << endl;
        addEdge(x[i], Nx + y[i], 1);
        eid[i] = (int)edges.size() - 2;
        //cerr << '!' << x[i] << ' ' << Nx + y[i] << ' ' << 0 << ' ' << 1 << endl;
        deg_x[x[i]]++;
        deg_y[y[i]]++;
    }
    int lx = 0;
    for (int i = 0; i < Nx; ++i) {
        int d = min(deg_x[i], x_mind[xs[i]]);
        // -d <= deg_x[i] - r - r <= d
        // (-d + deg_x[i]) / 2 <= r <= (d + deg_x[i]) / 2
        int l = (-d + deg_x[i] + 1) / 2;
        int r = (d + deg_x[i]) / 2;
        // (S, i, l, r)
        if (l > r) {
            cout << -1 << endl;
            return 0;
        }
        if (l) {
            addEdge(superS, i, l);
            addEdge(S, superT, l);
        }
        if (r - l) {
            addEdge(S, i, r - l);
        }
        lx += l;
    }
    int ly = 0;
    for (int i = 0; i < Ny; ++i) {
        int d = min(deg_y[i], y_mind[ys[i]]);
        int l = (-d + deg_y[i] + 1) / 2;
        int r = (d + deg_y[i]) / 2;
        // (Nx + i, T, l, r)
        if (l > r) {
            cout << -1 << endl;
            return 0;
        }
        if (l) {
            addEdge(superS, T, l);
            addEdge(Nx + i, superT, l);
        }
        if (r - l) {
            addEdge(Nx + i, T, r - l);
        }
        ly += l;
    }
    addEdge(T, S, inf);
    if (dinic() != lx + ly) {
        cout << -1 << endl;
    } else {
        ::source = S;
        ::target = T;
        edges[edges.size() - 1].f = edges[edges.size() - 1].c = 0;
        edges[edges.size() - 2].f = edges[edges.size() - 2].c = 0;
        dinic();
        string sol(n, ' ');
        for (int i = 0; i < n; ++i) {
            int j = eid[i];
            if (edges[j].v == Nx + y[i]) {//cerr << x[i] << ' ' << Nx + y[i] << ' ' << edges[j].f << endl;
                sol[i] = color[edges[j].f != edges[j].c];
            }
        }
        int cnt = count(sol.begin(), sol.end(), color[0]);
        cout << (ll)cost[0] * cnt + (ll)cost[1] * (n - cnt) << endl;
        cout << sol << endl;
    }
}
