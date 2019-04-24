#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

vector<int> kmp(string S) { // pi[i] = length of longest common prefix of S[0,i]
    vector<int> pi(S.size());
    for (int i = 1; i < S.size(); i++) {
        int g = pi[i - 1];
        while (g > 0 && S[i] != S[g])
            g = pi[g - 1];
        pi[i] = g + (S[i] == S[g]);
    }
    return pi;
}
vector<int> match(string S, const string &P) {
    vector<int> pi = kmp(P), res;
    int j = 0;
    for (int i = 0; i < S.size(); i++) {
        while (j > 0 && S[i] != P[j])
            j = pi[j - 1];
        j++;
        if (j == P.size()) {
            res.push_back(i - P.size() + 1);
            j = pi[j - 1];
        }
    }
    return res;
}
vector<int> Z(string S) {
    vector<int> z(S.size());
    for (int i = 1, l = -1, r = -1; i < S.size(); i++) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < S.size() && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// vi pi(const string &s) {
//     vi p(sz(s));
//     rep(i, 1, sz(s)) {
//         int g = p[i - 1];
//         while (g && s[i] != s[g])
//             g = p[g - 1];
//         p[i] = g + (s[i] == s[g]);
//     }
//     return p;
// }
// vi match(const string &s, const string &pat) {
//     vi p = pi(pat + '\0' + s), res;
//     rep(i, sz(p) - sz(s), sz(p)) {
//         cout << i << endl;
//         if (p[i] == sz(pat))
//             res.push_back(i - 2 * sz(pat));
//     }
//     return res;
// }

template <class F> void gen(string &s, int at, int alpha, F f) {
    if (at == sz(s))
        f();
    else {
        rep(i, 0, alpha) {
            s[at] = (char)('a' + i);
            gen(s, at + 1, alpha, f);
        }
    }
}

void test(const string &s) {
    int n = sz(s);
    vi found = Z(s);
    vi expected(n, 0);
    rep(i, 1, n) { // exclude index 0 (!)
        int j = 0;
        while (i + j < n && s[i + j] == s[j])
            j++;
        expected[i] = j;
    }
    assert(found == expected);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(n, 0, 13) {
        string s(n, 'x');
        gen(s, 0, 3, [&]() { test(s); });
    }
    // then ~4^10 strings
    rep(n, 0, 11) {
        string s(n, 'x');
        gen(s, 0, 4, [&]() { test(s); });
    }
    string S = "abacaba";
    auto res = Z(S);
    for (auto i : res)
        cout << i << ' ';
    cout << endl;
    // mykmp.set("aba");
    // mykmp.computePi();
    // for (int i = 0; i <= mykmp.n; i++)
    //     cout << mykmp.pi[i] << ' ';
    // cout << endl;
    // auto res = Z(S);
    // for (auto i : res)
    //     cout << i << endl;
}