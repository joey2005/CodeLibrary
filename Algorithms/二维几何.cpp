#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1.0);

int sign(double x) {return x < -eps ? -1: x > eps; }
int zero(double x) { return fabs(x) <= eps; }
double sqr(double x) { return x * x; }
double mysqrt(double x) { return x < 0 ? 0 : sqrt(x); }
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
double det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
double cross(const Point &a, const Point &b, const Point &c) { return det(b - a, c - a); }
double getAngle(const Point &a) { return atan2(a.y, a.x); }
//====================点在线段上=============================================//
bool onLine(const Point &p, const Point &a, const Point &b) {
    return zero(cross(a, b, p)) && sign(dot(a - p, b - p)) <= 0;
}
//====================点在多边形内===========================================//
int inPolygon(const Point &p, Point a[], int n) {
    int i, k, d1, d2, wn = 0;
    a[n] = a[0];
    for (i = 0; i < n; ++i) {
        if (onLine(p, a[i], a[i + 1])) return 2;
        k = sign(cross(a[i], a[i + 1], p));
        d1 = sign(a[i].y - p.y);
        d2 = sign(a[i + 1].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return wn != 0;
}
//====================两圆求交点=============================================//
bool intersect(const Point &a, double r1, const Point &b, double r2, Point &cp1, Point &cp2) {
    double l = (b - a).len2(), ll = (b - a).len();
    if (ll < fabs(r1 - r2) + eps || ll > r1 + r2 + eps) return false;
    double s = ((r1 - r2) * (r1 + r2) / l + 1) * .5;
    double t = (-(l - sqr(r1 - r2)) * (l - sqr(r1 + r2)) / (l * l * 4));
    Point dir = b - a, ndir = Point(a.y - b.y, b.x - a.x);
    cp1 = a + dir * s + ndir * t;
    cp2 = a + dir * s - ndir * t;
}
//====================圆和直线的交点=========================================//
bool intersect(const Point &a, const Point &b, const Point &o, double r, Point &cp1, Point &cp2) {
    double d = fabs(cross(a, b, o)) / (a - b).len();
    if (d - eps >= r) return false;
    double delta = sqrt(r * r - d * d);
    Point dir = (b - a) / (b - a).len();
    Point foot = zero(cross(a, b, o)) ? o : a + dir * dot(o - a, dir);
    cp1 = foot - dir * delta;
    cp2 = foot + dir * delta;
    return true;
}
//====================nlogn半平面交==========================================//
const int maxn = 20000 + 10;
struct Plane {
    Point a, b;
    double arg;
    Plane() {}
    Plane(const Point &a, const Point &b): a(a), b(b) { arg = atan2(b.y - a.y, b.x - a.x); }
};
bool intersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &cp) {
    double k1 = cross(a, b, c), k2 = cross(a, b, d);
    if (zero(k1 - k2)) return 0;
    cp = (d * k1 - c * k2) / (k1 - k2);
    return 1;
}
Point intersect(const Plane &a, const Plane &b) {
    Point cp;
    intersect(a.a, a.b, b.a, b.b, cp);
    return cp;
}
int satisfy(const Point &p, const Plane &pl) {
    return sign(cross(pl.a, pl.b, p)) > 0;
}
int check(const Plane &a, const Plane &b, const Plane &c) {
    Point cp = intersect(b, c);
    return satisfy(cp, a);
}
double check(Plane pl[], int N) {
    static Plane Q[maxn];
    int front = 1, back = 1;
    for (int i = 0; i < N; ++i) {
        for (; back - front > 1 && !check(Q[back - 2], Q[back - 1], pl[i]); ) --back;
        for (; back - front > 1 && !check(pl[i], Q[front], Q[front + 1]); ) ++front;
        Q[back++] = pl[i];
    }
    for (; back - front > 2 && !check(Q[back - 2], Q[back - 1], Q[front]); ) --back;
    for (; back - front > 2 && !check(Q[back - 1], Q[front], Q[front + 1]); ) ++front;
    if (back - front < 3) return 0;
    double area = 0;
    Q[front - 1] = Q[back - 1];
    Q[back] = Q[front];
    for (int i = front; i < back; ++i) {
        area += det(intersect(Q[i - 1], Q[i]), intersect(Q[i], Q[i + 1]));
    }
    return fabs(area) * .5;
}
bool operator < (const Plane &a, const Plane &b) {
    int cmp = sign(a.arg - b.arg);
    return cmp == 0 ? satisfy(a.a, b) : cmp < 0;
}
bool operator == (const Plane &a, const Plane &b) {
    return zero(getAngle(a.b - a.a) - getAngle(b.b - b.a));
}

int main() {
}

