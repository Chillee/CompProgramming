
#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x); }
};
const int MAXN = 1e6 + 5;
struct KMP {
    const static int MAXN = ::MAXN;
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
string S;
KMP kmp;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    kmp.set(S);
    kmp.computePi(), kmp.computeZ();
    int mxPre = 0;
    for (int i = 0; i < kmp.n; i++) {
        mxPre = max(mxPre, min(kmp.z[i], kmp.n - i - 1));
    }
    int cur = kmp.n;
    while (kmp.pi[cur] != 0) {
        if (kmp.pi[cur] <= mxPre) {
            for (int i = 0; i < kmp.pi[cur]; i++)
                cout << S[i];
            cout << endl;
            return 0;
        }
        cur = kmp.pi[cur];
    }
    cout << "Just a legend" << endl;
}