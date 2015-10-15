#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int maxn = 210;
const int MOD = 1e9 + 7;
long long dp[maxn][maxn][maxn];

class BearCries {
    public:
    int count(string message) {
        int size = message.size();
        memset(dp, 0, sizeof(dp));
        if (message[0] == '_' || message[size - 1] == '_')
        {
            return 0;
        }
        dp[0][1][0] = 1;
        for (int i = 1; i < size; ++i)
        {
            for (int a = 0; a < size; ++a)
            {
                for (int b = 0; b < size; ++b)
                {
                    if (message[i] == ';')
                    {
                        if (a > 0)
                        {
                            dp[i][a][b] = dp[i - 1][a - 1][b];
                        }
                        dp[i][a][b] = (dp[i][a][b] + (b + 1) * dp[i- 1][a][b + 1]) % MOD;
                    }
                    else
                    {
                        if (b > 0)
                        {
                            dp[i][a][b] = (dp[i - 1][a + 1][b - 1] * (a + 1)) % MOD;
                        }
                        dp[i][a][b] = (dp[i][a][b] + dp[i - 1][a][b] * b) % MOD;
                    }
                }
            }
        }
        return dp[size - 1][0][0];
    }
};

// CUT begin
ifstream data("BearCries.sample");

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

bool do_test(string message, int __expected) {
    time_t startClock = clock();
    BearCries *instance = new BearCries();
    int __result = instance->count(message);
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
        string message;
        from_stream(message);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(message, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1444834804;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BearCries (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
