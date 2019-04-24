#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
int ans[MAXN];
typedef long long ll;

const int MOD = 1e9 + 7;
int binExp(int b, int pw) {
    if (pw == 0)
        return 1;
    return binExp(b * b % MOD, pw / 2) * (pw & 1 ? b : 1) % MOD;
}
vector<ll> BerlekampMassey(vector<ll> s) {
    int n = s.size(), L = 0, m = 0;
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;

    ll b = 1;
    for (int i = 0; i < n; i++) {
        ++m;
        ll d = s[i] % MOD;
        for (int j = 1; j < L + 1; j++)
            d = (d + C[j] * s[i - j]) % MOD;
        if (!d)
            continue;
        T = C;
        ll coef = d * binExp(b, MOD - 2) % MOD;
        for (int j = m; j < n; j++)
            C[j] = (C[j] - coef * B[j - m]) % MOD;
        if (2 * L > i)
            continue;
        L = i + 1 - L;
        B = T;
        b = d;
        m = 0;
    }
    C.resize(L + 1);
    C.erase(C.begin());
    for (auto &x : C)
        x = (MOD - x) % MOD;
    return C;
}
typedef vector<ll> Poly;
ll linearRec(Poly S, Poly tr, ll k) {
    int n = S.size();
    auto combine = [&](Poly a, Poly b) {
        Poly res(n * 2 + 1);
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < n + 1; j++)
                res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
        for (int i = 2 * n; i > n; --i)
            for (int j = 0; j < n; j++)
                res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % MOD;
        res.resize(n + 1);
        return res;
    };
    Poly pol(n + 1), e(pol);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2)
            pol = combine(pol, e);
        e = combine(e, e);
    }
    ll res = 0;
    for (int i = 0; i < n; i++)
        res = (res + pol[i + 1] * S[i]) % MOD;
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ans[0] = 1;
    ans[1] = 1;
    for (int i = 2; i < 20; i++) {
        for (int j = max(i - 6, 0); j < i; j++) {
            ans[i] += ans[j];
        }
    }
    vector<ll> x;
    for (int i = 0; i < 20; i++) {
        x.push_back(ans[i]);
    }
    auto res = BerlekampMassey(x);
    x.resize(res.size());
    long long N;
    cin >> N;
    cout << linearRec(x, res, N) << endl;
}
