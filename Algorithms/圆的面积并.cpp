#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;
const double PI = acos(-1.0);
const int maxn = 1010;
struct Point {
    double x, y;
    Point() { x = y = 0; }
    Point(double x, double y): x(x), y(y) {}
    Point operator +(const Point &a) const { return Point(x + a.x, y + a.y); }
    Point operator -(const Point &a) const { return Point(x - a.x, y - a.y); }
    Point operator *(double k) const { return Point(x * k, y * k); }
    Point operator /(double k) const { return Point(x / k, y / k); }
    double len() const { return sqrt(len2()); }
    double len2() const { return x * x + y * y; }
};
inline double det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline int sign(double x) { return x < -eps ? -1 : x > eps; }
inline double sqr(double x) { return x * x; }
struct Circle {
    Point o;
    double r;
    Circle() {}
    Circle(const Point &o, double r): o(o), r(r) {}
} c[maxn];
struct Event {
    Point p;
    double ang;
    int add;
    Event() {}
    Event(const Point &_p, double _ang, int _add): p(_p), ang(_ang), add(_add) {}
    bool operator <(const Event &a) const { return ang < a.ang; }
} events[maxn * 2];
int E, cnt;

void circleCrossCircle(const Circle &a, const Circle &b) {
    double l = (a.o - b.o).len2(), ll = (a.o - b.o).len();
    if (ll < fabs(a.r - b.r) + eps || ll > a.r + b.r - eps) return;
    double s = ((a.r - b.r) * (a.r + b.r) / l + 1) * .5;
    double t = sqrt(-(l - sqr(a.r - b.r)) * (l - sqr(a.r + b.r)) / (l * l * 4));
    Point dir = b.o - a.o, ndir = Point(-dir.y, dir.x);
    Point aa = a.o + dir * s + ndir * t;
    Point bb = a.o + dir * s - ndir * t;
    double A = atan2(aa.y - a.o.y, aa.x - a.o.x);
    double B = atan2(bb.y - a.o.y, bb.x - a.o.x);
    events[E++] = Event(bb, B, 1);
    events[E++] = Event(aa, A, -1);
    if (B > A) cnt++;
}
bool removed[maxn];
double Area[maxn];
int C;
bool overlap(const Circle &a, const Circle &b) { return (a.o - b.o).len() <= a.r - b.r + eps; }

int main() {
    scanf("%d", &C);
    for (int i = 0; i < C; ++i) scanf("%lf%lf%lf", &c[i].o.x, &c[i].o.y, &c[i].r);
    for (int i = 0; i <= C; ++i) Area[i] = 0;
    for (int i = 0; i < C; ++i) {
        E = 0; cnt = 1;
        for (int j = 0; j < C; ++j) if (j != i && overlap(c[j], c[i])) cnt++;
        for (int j = 0; j < C; ++j) if (i != j) circleCrossCircle(c[i], c[j]);
        //cnt表示覆盖次数超过cnt
        if (E == 0) Area[cnt] += PI * c[i].r * c[i].r;
        else {
            sort(events, events + E);
            events[E] = events[0];
            for (int j = 0; j < E; ++j) {
                cnt += events[j].add; 
                Area[cnt] += det(events[j].p, events[j + 1].p) * .5;
                double theta = events[j + 1].ang - events[j].ang;
                if (theta < 0) theta += PI * 2.;
                Area[cnt] += theta * c[i].r * c[i].r * .5 - sin(theta) * c[i].r * c[i].r * .5;
            }
        }
    }
    double cntOdd = 0, cntEven = 0;
    for (int i = 1; i <= C; ++i) {
        if (i & 1) cntOdd += Area[i] - Area[i + 1];
        else cntEven += Area[i] - Area[i + 1];
    }
    printf("%.5f %.5f\n", cntOdd, cntEven);
}

