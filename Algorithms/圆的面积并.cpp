#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;
const double pi = acos(-1.0);
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
inline double sqr(double x) { return x * x; }
inline double det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline int sign(double x) { return x < -eps ? -1 : x > eps; }

const int maxn = 1024;
struct Circle {
    Point o; double r;
    Circle() {}
    Circle(const Point &o, double r): o(o), r(r) {}
} cir[maxn];
inline bool overlap(const Circle &a, const Circle &b) { return (a.o - b.o).len() <= a.r - b.r + eps; }

struct Event {
    Point p; double deg; int cnt;
    Event() {}
    Event(Point _p, double _deg, int _cnt) { p=_p; deg=_deg; cnt=_cnt; }
    bool operator <(const Event &a) const { return deg < a.deg; }
} events[maxn << 1];
int eventCount, cnt;

void circleIntersectCircle(const Circle &a, const Circle &b) {
    double l = (a.o - b.o).len2(), ll = (a.o - b.o).len();
    if (ll < fabs(a.r - b.r) + eps || ll > a.r + b.r - eps) return;
    double s = ((a.r - b.r) * (a.r + b.r) / l + 1) * .5;
    double t = sqrt(-(l - sqr(a.r - b.r)) * (l - sqr(a.r + b.r)) / (l * l * 4));
    Point dir = b.o - a.o, ndir = Point(-dir.y, dir.x);
    Point aa = a.o + dir * s + ndir * t;
    Point bb = a.o + dir * s - ndir * t;
    double A = atan2(aa.y - a.o.y, aa.x - a.o.x);
    double B = atan2(bb.y - a.o.y, bb.x - a.o.x);
    events[eventCount++] = Event(bb, B, 1);
    events[eventCount++] = Event(aa, A, -1);
    if (B > A) cnt++;
}
//bool removed[maxn];
double cover[maxn];
int circleCount;

int main() {
    scanf("%d", &circleCount);
    for (int i = 0; i < circleCount; ++i) {
        scanf("%lf%lf%lf", &cir[i].o.x, &cir[i].o.y, &cir[i].r);
    }
    memset(cover, 0, sizeof cover);
    for (int i = 0; i < circleCount; ++i) {
        eventCount = 0; cnt = 1;
        for (int j = 0; j < circleCount; ++j) if (j != i && overlap(cir[j], cir[i])) cnt++;
        for (int j = 0; j < circleCount; ++j) if (i != j) circleIntersectCircle(cir[i], cir[j]);
        //cnt表示覆盖次数超过cnt
        if (eventCount == 0) cover[cnt] += pi * cir[i].r * cir[i].r;
        else {
            sort(events, events + eventCount);
            events[eventCount] = events[0];
            for (int j = 0; j < eventCount; ++j) {
                cnt += events[j].cnt; 
                cover[cnt] += det(events[j].p, events[j + 1].p) * .5;
                double theta = events[j + 1].deg - events[j].deg;
                if (theta < 0) theta += pi * 2.;
                cover[cnt] += theta * cir[i].r * cir[i].r * .5 - sin(theta) * cir[i].r * cir[i].r * .5;
            }
        }
    }
    double covers[2] = {0};
    for (int i = 1; i <= circleCount; ++i) {
        covers[i & 1] += cover[i] - cover[i + 1];
    }
    printf("%.15f %.15f\n", covers[1], covers[0]);
}

