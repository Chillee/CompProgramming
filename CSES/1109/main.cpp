#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

template <int MAXN> struct KMP {
    int pi[MAXN], z[MAXN], n;
    string p;
    void set(string _p) { p = _p, n = p.size(); }
    void computePi() {
        int j = -1;
        pi[0] = -1;
        for (int i = 0; i < n; i++) {
            while (j >= 0 && p[i] != p[j])
                j = pi[j];
            j++;
            pi[i + 1] = j;
        }
    }
    void computeZ() {
        for (int i = 1, l = -1, r = -1; i < n; ++i) {
            z[i] = i >= r ? 0 : min(r - i, z[i - l]);
            while (i + z[i] < n && p[i + z[i]] == p[z[i]])
                z[i]++;
            if (i + z[i] > r)
                l = i, r = i + z[i];
        }
    }
    vector<int> search(string s) {
        vector<int> res;
        int j = 0;
        for (int i = 0; i < s.size(); i++) {
            while (j >= 0 && s[i] != p[j])
                j = pi[j];
            j++;
            if (j == p.size()) {
                res.push_back(i - n + 1);
                j = pi[j];
            }
        }
        return res;
    }
};
const int MAXN = 1e6 + 5;
KMP<MAXN> kmp;
string S;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    kmp.set(S);
    kmp.computePi();
    cout << S.substr(0, kmp.pi[kmp.n - 1] + 1) << endl;
}