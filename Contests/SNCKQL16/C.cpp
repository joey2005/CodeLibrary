#include <bits/stdc++.h>

using namespace std;

const int mul[] = {2, 2, 1, 3};

int calcsg(long long n) {
    if (n == 0) return 0;
    int i = 1;
    long long l = 1;
    while (n > l) {//cerr << i << ' ' << l << endl;
        n -= l;
        l *= mul[i];
        i = (i + 1) % 4;
    }
    return i;
}

int main() {
    int testCount;
    cin >> testCount;
    for (int testId = 1; testId <= testCount; ++testId) {
        int n;
        cin >> n;
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            long long A;
            cin >> A;
            ret ^= calcsg(A);
        }
        puts(ret ? "Henry" : "Derek");
    }
}
