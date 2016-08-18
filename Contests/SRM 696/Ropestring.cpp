#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()

template<typename T> inline bool checkmin(T &a, T b) { if (b < a) { a = b; return 1; } return 0; }
template<typename T> inline bool checkmax(T &a, T b) { if (b > a) { a = b; return 1; } return 0; }

typedef long long ll;

struct Ropestring {
    string makerope(string s) {
        vector<int> odd, even;
        int L = s.size();
        for (int i = 0; i < L; ++i) {
            if (s[i] == '-') {
                int j = i + 1;
                while (j < L && s[j] == '-') {
                    j++;
                }
                if (!((j - i) & 1)) {
                    odd.emplace_back(j - i);
                } else {
                    even.emplace_back(j - i);
                }
                i = j - 1;
            }
        }
        sort(ALL(odd), greater<int>());
        sort(ALL(even), greater<int>());
        string res = "";
        for (int i = 0; i < odd.size(); ++i) {
            if (res != "") {
                res += '.';
            }
            res += string(odd[i], '-');
        }
        for (int i = 0; i < even.size(); ++i) {
            if (res != "") {
                res += '.';
            }
            res += string(even[i], '-');
        }
        res += string(L - res.size(), '.');
        return res;
    }
};

// CUT begin
ifstream data("Ropestring.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string s, string __expected) {
    time_t startClock = clock();
    Ropestring *instance = new Ropestring();
    string __result = instance->makerope(s);
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
        string s;
        from_stream(s);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1471496761;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Ropestring (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
