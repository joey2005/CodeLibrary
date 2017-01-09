/***
  * URAL 1132
  * Author: Joey2005
  */
#include <bits/stdc++.h>

using namespace std;

namespace Quadratic_residue {
    inline long long mulmod(long long a, long long b, long long mod) {
        return a * b % mod;
    }

    inline long long powmod(long long a, long long n, long long mod) {
        long long res = 1, POW = a;
        while (n > 0) {
            if (n & 1) {
                res = mulmod(res, POW, mod);
            }
            POW = mulmod(POW, POW, mod);
            n /= 2;
        }
        return res;
    }

    // solve equation x^2 mod p = a
    bool solve(int a, int p, int &x, int &y) {
        if (p == 2) {
            x = y = 1;
            return true;
        }
        int p2 = p / 2;
        int tmp = powmod(a, p2, p);
        if (tmp == p - 1) return false;
        if ((p + 1) % 4 == 0) {
            x = powmod(a, (p + 1) / 4, p);
            y = p - x;
        } else {
            int b, pb;
            int t = __builtin_ctz(p - 1);
            int h = (p - 1) >> t;
            if (t >= 2) {
                do {
                    b = rand() % (p - 2) + 2;
                } while (powmod(b, p2, p) != p - 1);
                pb = powmod(b, h, p);
            }
            long long s = powmod(a, h / 2, p);
            for (int step = 2; step <= t; ++step) {
                long long ss = mulmod(mulmod(s, s, p), a, p);
                for (int i = 0; i < t - step; ++i) ss = mulmod(ss, ss, p);
                if (ss + 1 == p) s = mulmod(s, pb, p);
                pb = mulmod(pb, pb, p);
            }
            x = mulmod(s, a, p);
            y = p - x;
        }
        return true;
    }
};

int main() {
    int testCount;
    cin >> testCount;
    for (int testNumber = 1; testNumber <= testCount; ++testNumber) {
        int a, n, ans_x, ans_y;
        cin >> a >> n;
        if (Quadratic_residue::solve(a, n, ans_x, ans_y)) {
            if (ans_x > ans_y) {
                cout << ans_y << ' ' << ans_x << endl;
            } else if (ans_x < ans_y) {
                cout << ans_x << ' ' << ans_y << endl;
            } else {
                cout << ans_x << endl;
            }
        } else {
            cout << "No root" << endl;
        }
    }
}
