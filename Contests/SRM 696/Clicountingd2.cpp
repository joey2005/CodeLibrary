#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()

template<typename T> inline bool checkmin(T &a, T b) { if (b < a) { a = b; return 1; } return 0; }
template<typename T> inline bool checkmax(T &a, T b) { if (b > a) { a = b; return 1; } return 0; }

typedef long long ll;

const int maxn = 21;

int id[maxn][maxn], dp[1 << maxn];

struct Clicountingd2 {
    int count(vector<string> g) {
        int n = g.size();
        memset(id, -1, sizeof id);
        int ID = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                switch (g[i][j]) {
                case '0':
                    id[i][j] = -1;
                    break;
                case '1':
                    id[i][j] = 0;
                    break;
                case '?':
                    id[i][j] = ++ID;
                    break;
                }
            }
        }
        memset(dp, 0, sizeof dp);
        for (int mask = 0; mask < 1 << n; ++mask) {
            int id_mask = 0;
            bool ok = true;
            for (int i = 0; i < n; ++i) if (mask >> i & 1) {
                for (int j = i + 1; j < n; ++j) if (mask >> j & 1) {
                    if (id[i][j] < 0) {
                        ok = false;
                    } else if (id[i][j] > 0) {
                        id_mask |= 1 << (id[i][j] - 1);
                    }
                }
            }
            if (ok) {
                dp[id_mask] = max(dp[id_mask], __builtin_popcount(mask));
            }
        }
        int res = 0;
        for (int mask = 0; mask < 1 << ID; ++mask) {
            for (int i = 0; i < ID; ++i) {
                if (!(mask >> i & 1)) {
                    dp[mask | 1 << i] = max(dp[mask | 1 << i], dp[mask]);
                }
            }
            res += dp[mask];
        }
        return res;
    }
};

// CUT begin
ifstream data("Clicountingd2.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<string> g, int __expected) {
    time_t startClock = clock();
    Clicountingd2 *instance = new Clicountingd2();
    int __result = instance->count(g);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<string> g;
        from_stream(g);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(g, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1471498639;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "Clicountingd2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
