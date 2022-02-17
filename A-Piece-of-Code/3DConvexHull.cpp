#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);
const int maxn = 1024;
inline int sign(double x) { return x < -eps ? -1 : (x > eps ? 1 : 0); }
inline double mysqrt(double x) { return x < 0 ? 0 : sqrt(x); }
struct Point3 {
    double x, y, z;
    Point3(double x, double y, double z): x(x), y(y), z(z) {}
    Point3(): x(0), y(0), z(0) {}
    bool operator <(const Point3 &p) const { return x < p.x || x == p.x && y < p.y || x == p.x && y == p.y && z < p.z; }
    bool operator ==(const Point3 &p) const { return sign(x - p.x) == 0 && sign(y - p.y) == 0 && sign(z - p.z) == 0; }
    Point3 operator +(const Point3 &p) const { return Point3(x + p.x, y + p.y, z + p.z); }
    Point3 operator -(const Point3 &p) const { return Point3(x - p.x, y - p.y, z - p.z); }
    Point3 operator *(const double k) const { return Point3(x * k, y * k, z * k); }
    Point3 operator /(const double k) const { return Point3(x / k, y / k, z / k); }
    Point3 det(const Point3 &p) const { return Point3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
    double dot(const Point3 &p) const { return x * p.x + y * p.y + z * p.z; }
    double norm() { return dot(*this); }
    double len() { return mysqrt(norm()); }
};

inline istream& operator >>(istream& in, Point3 &p) {
    in >> p.x >> p.y >> p.z;
    return in;
}
inline ostream& operator <<(ostream& out, const Point3 &p) {
    out << p.x << ' ' << p.y << ' ' << p.z;
    return out;
}

struct Face {
    int a, b, c;
    Face() {}
    Face(int a, int b, int c): a(a), b(b), c(c) {}
    int &operator [](int k) { return k == 0 ? a : k == 1 ? b : c; }
};

vector<Point3> points;
vector<Face> faces;
int markCnt, mark[maxn][maxn];

inline double mix(const Point3 &a, const Point3 &b, const Point3 &c) { 
    return a.dot(b.det(c)); 
}
inline double surface_area(int a, int b, int c) { 
    return ((points[b] - points[a]).det(points[c] - points[a])).len(); 
}
inline double volume(int a, int b, int c, int d) { 
    return mix(points[b] - points[a], points[c] - points[a], points[d] - points[a]); 
}
inline void addF(int a, int b, int c) { 
    faces.push_back(Face(a, b, c));
}
inline void addV(int v) {
    vector<Face> cur;
    int a, b, c;
    markCnt++;
    for (int i = 0; i < faces.size(); ++i) {
        a = faces[i][0];
        b = faces[i][1];
        c = faces[i][2];
        if (sign(volume(v, a, b, c)) < 0) {
            mark[a][b] = mark[b][a] = mark[b][c] = markCnt;
            mark[c][b] = mark[c][a] = mark[a][c] = markCnt;
        } else {
            cur.push_back(faces[i]);
        }
    }
    faces = cur;
    for (int i = 0; i < cur.size(); ++i) {
        a = faces[i][0];
        b = faces[i][1];
        c = faces[i][2];
        if (mark[a][b] == markCnt) addF(b, a, v);
        if (mark[b][c] == markCnt) addF(c, b, v);
        if (mark[c][a] == markCnt) addF(a, c, v);
    }
}
bool find(vector<Point3> &points) {
    for (int i = 2; i < points.size(); ++i) {
        Point3 ndir = (points[0] - points[i]).det(points[1] - points[i]);
        if (ndir == Point3()) continue;
        swap(points[i], points[2]);
        for (int j = i + 1; j < points.size(); ++j) {
            if (sign(volume(0, 1, 2, j)) != 0) {
                swap(points[j], points[3]);
                addF(0, 1, 2);
                addF(0, 2, 1);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int tests, n;
    for (cin >> tests; tests-- > 0; ) {
        cin >> n;
        points.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i];
        }
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        random_shuffle(points.begin(), points.end());
        double resSur = 0, resVol = 0;
        faces.clear();
        if (find(points)) {
            memset(mark, 0, sizeof(mark));
            markCnt = 0;
            for (int i = 3; i < n; ++i) {
                addV(i);
            }
            int base = faces[0][0];
            for (Face f : faces) {
                resSur += surface_area(f[0], f[1], f[2]);
                resVol += fabs(volume(base, f[0], f[1], f[2]));
            }
        }
        printf("%.15f %.15f\n", resSur / 2, resVol / 6);
    }
}
