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

vector<int> adj[maxn];
vector<vector<int>> heavy_paths;
int n, size[maxn], dep[maxn], fa[maxn], id[maxn], pos[maxn];
int tot, tin[maxn], tout[maxn], seq[maxn << 1];
int front, back, que[maxn];

void heavy_light_decomposition() {
    front = back = 0;
    que[back++] = 0;
    fa[0] = dep[0] = 0;
    while (front < back) {
        int u = que[front++];
        for (int v : adj[u]) {
            if (v != fa[u]) {
                que[back++] = v;
                fa[v] = u;
                dep[v] = dep[u] + 1;
            }
        }
    }
    heavy_paths.clear();
    for (int i = n - 1; i >= 0; --i) {
        int u = que[i];
        size[u] = 1;
        pair<int, int> prefer(0, -1);
        for (int v : adj[u]) {
            if (v != fa[u]) {
                size[u] += size[v];
                prefer = min(prefer, make_pair(size[v], v));
            }
        }
        id[u] = heavy_paths.size();
        int w = prefer.second;
        if (w >= 0 && size[w] * 2 > size[u]) {
            id[u] = id[w];
        }
        if (id[u] == heavy_paths.size()) {
            heavy_paths.emplace_back(vector<int>());
        }
        pos[u] = heavy_paths[id[u]].size();
        heavy_paths[id[u]].emplace_back(u);
    }
}

void dfs(int v, int u) {
    tin[v] = ++tot;
    seq[tot] = v;
    for (int w : adj[v]) {
        if (w != u) {
            dfs(w, v);
        }
    }
    tout[v] = ++tot;
    seq[tot] = v;
}

int main() {
}

