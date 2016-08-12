#include <bits/stdc++.h>

using namespace std;

const int maxn = 110000;
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
} info[maxn];

double det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
double cross(const Point &a, const Point &b, const Point &c) { return det(b - a, c - a); }
double getAngle(const Point &a) { return atan2(a.y, a.x); }

double area2(Point pa, Point pb, double r) {
    if (pa.len() < pb.len()) swap(pa, pb);
    if (pb.len() < eps) return 0;
    double a, b, c, B, C, cosB, cosC, S, h, theta;
    a = pb.len(); b = pa.len(); c = (pb - pa).len();
    cosB = dot(pb, pb - pa) / a / c;
    B = acos(cosB);
    cosC = dot(pa, pb) / a / b;
    C = acos(cosC);
    if (a > r) {
        S = (C/2)*r*r;
        h = a*b*sin(C)/c;
        if (h < r && B < PI/2) S -= (acos(h/r)*r*r - h*sqrt(r*r-h*h));
    } else if (b > r) {
        theta = PI - B - asin(sin(B)/r*a);
        S = .5*a*r*sin(theta) + (C-theta)/2*r*r;
    } else {
        S = .5*sin(C)*a*b;
    }
    return S;
}

double area(int n, double r) {
    double S = 0;
    for (int i = 0; i < n; ++i) {
        S += area2(info[i], info[i + 1], r) * sign(det(info[i], info[i + 1]));
    }
    return fabs(S);
}

int main() {
}
