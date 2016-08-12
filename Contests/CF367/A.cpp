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

double sqr(double a) {
    return a * a;
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

int main() {
    int a, b, n;
    cin >> a >> b;
    cin >> n;
    double res = 1e100;
    for (int i = 0; i < n; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        res = min(res, dist(a, b, x, y) / v);
    }
    printf("%.15f\n", res);
}

