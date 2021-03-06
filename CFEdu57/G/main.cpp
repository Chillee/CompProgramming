#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
ll N, K;

const ll MOD = 998244353;
template <int maxn> struct NTT {
    const static int MAXN = 1 << (32 - __builtin_clz(maxn - 1));
    const static int MOD = 998244353;
    const static int root = 3;
    int rev[MAXN], rt[MAXN];

    inline int mul(const int a, const int b) { return (long long)a * b % MOD; }
    inline int sub(const int a, const int b) { return b > a ? a - b + MOD : a - b; }
    inline int add(const int a, const int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int binExp(int base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        int curL = (MOD - 1) >> 2;
        rt[1] = 1;
        for (int k = 2; k < MAXN; k *= 2) {
            int z = binExp(root, curL);
            curL >>= 1;
            for (int i = k / 2; i < k; i++) {
                rt[2 * i] = rt[i], rt[2 * i + 1] = mul(rt[i], z);
            }
        }
    }
    void calcRev(int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << (32 - __builtin_clz(n - 1))) / 2;
    }
    void ntt(int *a, int n) {
        calcRev(n);
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    int z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }
    int rght[MAXN];
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        int s = a.size() + b.size() - 1;
        int logn = 32 - __builtin_clz(s), n = 1 << logn;
        vector<int> lft(n);
        fill(begin(lft), end(lft), 0), fill(begin(rght), end(rght), 0);
        copy(a.begin(), a.end(), begin(lft)), copy(b.begin(), b.end(), begin(rght));
        ntt(&lft[0], n), ntt(rght, n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            lft[i] = mul(mul(lft[i], rght[i]), invN);
        reverse(lft.begin() + 1, lft.begin() + n);
        ntt(&lft[0], n);
        return lft;
    }
};
NTT<10 * MAXN> ntt;
vector<int> fftExp(vector<int> a, ll pow) {
    vector<int> ans(1, 1);
    while (pow > 0) {
        if (pow & 1)
            ans = ntt.multiply(ans, a);
        a = ntt.multiply(a, a);
        pow >>= 1;
    }
    return ans;
}
vector<int> digits(10);
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < K; i++) {
        ll t;
        cin >> t;
        digits[t] = 1;
    }
    auto res = fftExp(digits, N / 2);
    ll ans = 0;
    for (auto i : res) {
        ans += ((ll)i * i) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}