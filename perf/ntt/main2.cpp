#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll LOGN = 21, MAXN = 1 << 21;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 10);
const ll MOD = 998244353;
const ll root = 3;

struct NTT1 {
    typedef long long ll;
    ll N, LOGN;
    vector<ll> rev;
    vector<ll> rt;
    ll mod_pow(ll a, ll p, ll m = MOD) {
        ll result = 1;
        while (p > 0) {
            if (p & 1)
                result = result * a % m;

            a = a * a % m;
            p >>= 1;
        }
        return result;
    }
    void calcRoots() {
        rev.resize(N), rt.resize(N);
        rev[0] = 0, rt[1] = 1;
        for (ll i = 0; i < N; i++)
            rev[i] = (rev[i / 2] | (i & 1) << LOGN) / 2;
        int curL = (MOD - 1) >> 2;
        for (int k = 2; k < N; k *= 2) {
            int z = mod_pow(root, curL);
            curL >>= 1;
            for (int i = k / 2; i < k; i++) {
                rt[2 * i] = rt[i], rt[2 * i + 1] = (rt[i] * z) % MOD;
            }
        }
    }
    void ntt(ll *a) {
        for (ll i = 0; i < N; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (ll k = 1; k < N; k *= 2)
            for (ll i = 0; i < N; i += 2 * k)
                for (ll j = 0; j < k; j++) {
                    ll z = (rt[j + k] * a[i + j + k]) % MOD;
                    a[i + j + k] = (a[i + j] - z + MOD) % MOD;
                    a[i + j] = (a[i + j] + z) % MOD;
                }
    }

    vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        ll s = a.size() + b.size() - 1;
        LOGN = 32 - __builtin_clz(s), N = 1 << LOGN;
        calcRoots();
        vector<ll> lft = a, rght = b;
        lft.resize(N), rght.resize(N);
        ntt(&lft[0]);
        ntt(&rght[0]);
        ll invN = mod_pow(N, MOD - 2);
        for (ll i = 0; i < N; i++)
            lft[i] = (((lft[i] * rght[i]) % MOD) * invN) % MOD;
        reverse(lft.begin() + 1, lft.begin() + N);
        ntt(&lft[0]);
        return lft;
    }
};
struct NTT2 {
    // For p < 2ˆ30 there is also e.g. (5 << 25, 3) , (7 << 26, 3),
    // (479 << 21, 3) and (483 << 21, 5). The last two are > 10ˆ9.
    const ll MOD = (119 << 23) + 1, root = 3; // = 998244353
    ll binExp(ll base, ll exp) {
        if (exp == 0)
            return 1;
        return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
    }
    void ntt(ll *x, ll *temp, ll *roots, int N, int skip) {
        if (N == 1)
            return;
        int n2 = N / 2;
        ntt(x, temp, roots, n2, skip * 2);
        ntt(x + skip, temp, roots, n2, skip * 2);
        for (int i = 0; i < N; i++)
            temp[i] = x[i * skip];
        for (int i = 0; i < n2; i++) {
            ll s = temp[2 * i], t = temp[2 * i + 1] * roots[skip * i];
            x[skip * i] = (s + t) % MOD;
            x[skip * (i + n2)] = (s - t) % MOD;
        }
    }
    void ntt(vector<ll> &x, bool inv = false) {
        ll e = binExp(root, (MOD - 1) / x.size());
        if (inv)
            e = binExp(e, MOD - 2);
        vector<ll> roots(x.size(), 1), temp = roots;
        for (int i = 1; i < x.size(); i++)
            roots[i] = roots[i - 1] * e % MOD;
        ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
    }
    vector<ll> conv(vector<ll> a, vector<ll> b) {
        int s = a.size() + b.size() - 1;
        if (s <= 0)
            return {};
        int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
        if (s <= 200) {
            vector<ll> c(s);
            for (int i = 0; i < a.size(); i++)
                for (int j = 0; j < b.size(); j++)
                    c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
            return c;
        }
        a.resize(n);
        ntt(a);
        b.resize(n);
        ntt(b);
        ll d = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            a[i] = a[i] * b[i] % MOD * d % MOD;
        ntt(a, true);
        a.resize(s);
        for (auto &i : a)
            i = i < 0 ? i + MOD : i;
        return a;
    }
};
NTT1 ntt1;
NTT2 ntt2;
vector<ll> a, b;
signed main() {
    for (int i = 0; i < MAXN; i++) {
        a.push_back(uni(rng)), b.push_back(uni(rng));
    }
    clock_t begin;
    begin = clock();
    auto res = ntt1.multiply(a, b);
    cout << "custom: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[a.size() / 2] << endl;
    begin = clock();
    res = ntt2.conv(a, b);
    cout << "kactl: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[a.size() / 2] << endl;
}