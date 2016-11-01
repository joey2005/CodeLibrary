#include <bits/stdc++.h>

using namespace std;

template<typename INT, const int V, const INT infty>
struct Dinic {
    struct Edge {
        int v, last; INT f, capa;
        Edge(int v, INT capa, int last): v(v), f(0), capa(capa), last(last) {}
        Edge() {}
    };

    Dinic(int S, int T): source(S), sink(T) {
        initFlow();
    }

    void initFlow() {
        memset(info, -1, sizeof info);
        edges.clear();
    }

    void resetFlow() {
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].f = 0;
        }
    }

    void addEdge(int u, int v, INT c1, INT c2 = 0) {
        edges.emplace_back(v, c1, info[u]);
        info[u] = edges.size() - 1;
        edges.emplace_back(u, c2, info[v]);
        info[v] = edges.size() - 1;
    }

    int bfs() {
        memset(dist, -1, sizeof dist);
        front = back = 0;
        que[back++] = sink;
        dist[sink] = 0;
        while (front < back) {
            int u = que[front++];
            for (int i = info[u]; i >= 0; i = edges[i].last) {
                int v = edges[i].v;
                if (edges[i ^ 1].f < edges[i ^ 1].capa && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    que[back++] = v;
                }
            }
        }
        return dist[source] != -1;
    }

    INT dfs(int u, INT can) {
        if (u == sink) {
            return can;
        }
        INT res = 0;
        for (int i = cur[u]; i >= 0; i = edges[i].last) {
            int v = edges[i].v;
            INT w = edges[i].capa - edges[i].f;
            if (w && dist[v] + 1 == dist[u]) {
                w = dfs(v, min(w, can - res));
                if (w) {
                    cur[u] = i;
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

    INT flow() {
        INT res = 0, f;
        while (bfs()) {
            memcpy(cur, info, sizeof info);
            res += dfs(source, infty);
        }
        return res;
    }

    vector<Edge> edges;
    int info[V + 1], cur[V + 1];
    int front, back, que[V + 1];
    int dist[V + 1];
    int source, sink;
};

typedef Dinic<int, 100010, INT_MAX / 3> Flow;

int main() {
}

