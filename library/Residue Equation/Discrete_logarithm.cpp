/***
  * SGU 261
  * Author: Joey2005
  */
#include <bits/stdc++.h>

using namespace std;

namespace Discrete_logarithm {
    inline long long mulmod(long long a, long long b, long long mod) { return a * b % mod; }

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

    int primitive_roots(int p) {
        if (p == 2) {
            return 3;
        }
        vector<int> D;
        int Phi = p - 1;
        int t = Phi;
        for (int i = 2; (long long) i * i <= t; ++i) {
            if (t % i == 0) {
                D.push_back(i);
                for (; t % i == 0; t /= i);
            }
        }
        if (t > 1) D.push_back(t);
        for (int g = 1; ; ++g) {
            bool good = true;
            for (int i = 0; i < D.size(); ++i) {
                if (powmod(g, Phi / D[i], p) == 1) {
                    good = false;
                    break;
                }
            }
            if (good) {
                return g;
            }
        }
    }

    // return y such that x^y mod P = n
    long long logmod(int x, int n, int P) {
        map<long long, int> rec;
        int s = (int) sqrt(P);
        for (; (long long) s * s <= P; ) s++;
        long long cur = 1;
        for (int i = 0; i < s; ++i) {
            rec[cur] = i;
            cur = mulmod(cur, x, P);
        }
        long long mul = cur;
        cur = 1;
        for (int i = 0; i < s; ++i) {
            long long more = mulmod(n, powmod(cur, P - 2, P), P); // more = n * cur ^ -1
            if (rec.count(more)) {
                return i * s + rec[more];
            }
            cur = mulmod(cur, mul, P);
        }
        return -1;
    }

    long long extended_euclids(long long a, long long b, long long &x, long long &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        long long ret = extended_euclids(b, a % b, x, y);
        long long t = x;
        x = y;
        y = t - (a / b) * y;
        return ret;
    }

    // solve x^N mod P = a
    vector<int> solve(int P, int N, int a) {
        int g = primitive_roots(P);
        long long m = logmod(g, a, P);
        vector<int> ret;
        if (a == 0) {
            ret.push_back(0);
            return ret;
        }
        if (m == -1) {
            return ret;
        }
        long long A = N, B = P - 1, C = m, x, y;
        long long d = extended_euclids(A, B, x, y);
        if (C % d != 0) return ret;
        x = x * (C / d) % B; // g^B mod P = g^(P-1) mod P = 1
        long long delta = B / d;
        for (int i = 0; i < d; ++i) {
            x = ((x + delta) % B + B) % B;
            ret.push_back((int) powmod(g, x, P));
        }
        sort(ret.begin(), ret.end());
        ret.erase(unique(ret.begin(), ret.end()), ret.end());
        return ret;
    }
}

int main() {
    int P, K, A;
    cin >> P >> K >> A;
    vector<int> res = Discrete_logarithm::solve(P, K, A);
    cout << res.size() << endl;
    for (int result : res) {
        cout << result << endl;
    }
}

