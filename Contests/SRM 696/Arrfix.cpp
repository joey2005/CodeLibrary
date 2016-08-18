#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()

template<typename T> inline bool checkmin(T &a, T b) { if (b < a) { a = b; return 1; } return 0; }
template<typename T> inline bool checkmax(T &a, T b) { if (b > a) { a = b; return 1; } return 0; }

typedef long long ll;

struct Arrfix {
    int mindiff(vector<int> A, vector<int> B, vector<int> F) {
        int na = A.size();
        int nb = B.size();
        int nf = F.size();
        vector<pair<int, int>> pos;
        for (int i = 0; i < nb; ++i) {
            pos.emplace_back(B[i] == A[i], i);
        }
        sort(pos.begin(), pos.end());
        int res = 0;
        vector<bool> vis(nb, false);
        vector<bool> found(nf, false);
        for (int i = 0; i < nf; ++i) {
            for (int j = 0; j < nb; ++j) {
                if (!vis[pos[j].second] && B[pos[j].second] == F[i]) {
                    vis[pos[j].second] = true;
                    found[i] = true;
                    break;
                }
            }
            if (found[i]) {
                res++;
            }
        }
        for (int i = 0; i < nf; ++i) {
            if (!found[i]) {
                for (int j = 0; j < nb; ++j) {
                    if (!vis[pos[j].second]) {
                        vis[pos[j].second] = true;
                        found[i] = true;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < nb; ++i) {
            if (!vis[i]) {
                res += B[i] == A[i];
            }
        }
        return na - res;
    }
};

// CUT begin
ifstream data("Arrfix.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> F, int __expected) {
    time_t startClock = clock();
    Arrfix *instance = new Arrfix();
    int __result = instance->mindiff(A, B, F);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> F;
        from_stream(F);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, F, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1471497100;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Arrfix (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
