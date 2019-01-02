#include <bits/stdc++.h>

using namespace std;

#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define forn(i, n) fore(i, 0, n)

#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()

#define mp make_pair
#define pb push_back

#define x first
#define y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template <class A, class B> ostream &operator<<(ostream &out, const pair<A, B> &p) { return out << "(" << p.x << ", " << p.y << ")"; }

template <class A> ostream &operator<<(ostream &out, const vector<A> &v) {
    out << "[";
    forn(i, sz(v)) {
        if (i)
            out << ", ";
        out << v[i];
    }
    return out << "]";
}

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9;

const int N = 2500 * 1000 + 555;
const int LOGN = 22;

const int MOD = 998244353;
int g = 3;

inline int mul(int a, int b) { return int(a * 1ll * b % MOD); }

inline int norm(int a) {
    if (a >= MOD)
        a -= MOD;
    if (a < 0)
        a += MOD;
    return a;
}

inline int binPow(int a, int k) {
    int ans = 1;
    while (k > 0) {
        if (k & 1)
            ans = mul(ans, a);
        a = mul(a, a);
        k >>= 1;
    }
    return ans;
}

inline int inv(int a) { return binPow(a, MOD - 2); }

vector<int> w[LOGN];
vector<int> rv[LOGN];

void precalc() {
    int wb = binPow(g, (MOD - 1) / (1 << LOGN));

    for (int st = 0; st < LOGN - 1; st++) {
        w[st].assign(1 << st, 1);

        int bw = binPow(wb, 1 << (LOGN - st - 1));
        int cw = 1;

        for (int k = 0; k < (1 << st); k++) {
            w[st][k] = cw;
            cw = mul(cw, bw);
        }
    }
    for (int st = 0; st < LOGN; st++) {
        rv[st].assign(1 << st, 0);

        if (st == 0) {
            rv[st][0] = 0;
            continue;
        }
        int h = (1 << (st - 1));
        for (int k = 0; k < (1 << st); k++)
            rv[st][k] = (rv[st - 1][k & (h - 1)] << 1) | (k >= h);
    }
}

inline void fft(int a[N], int n, bool inverse) {
    int ln = 0;
    while ((1 << ln) < n)
        ln++;

    assert((1 << ln) < N);
    n = (1 << ln);

    forn(i, n) {
        int ni = rv[ln][i];
        if (i < ni)
            swap(a[i], a[ni]);
    }

    for (int st = 0; (1 << st) < n; st++) {
        int len = (1 << st);
        for (int k = 0; k < n; k += (len << 1)) {
            for (int pos = k; pos < k + len; pos++) {
                int l = a[pos];
                int r = mul(a[pos + len], w[st][pos - k]);

                a[pos] = norm(l + r);
                a[pos + len] = norm(l - r);
            }
        }
    }

    if (inverse) {
        int in = inv(n);
        forn(i, n) a[i] = mul(a[i], in);
        reverse(a + 1, a + n);
    }
}

int aa[N], bb[N], cc[N];

inline vector<int> multiply(const vector<int> a, const vector<int> b) {
    int ln = 1;
    while (ln < (sz(a) + sz(b)))
        ln <<= 1;

    forn(i, ln) aa[i] = (i < sz(a) ? a[i] : 0);

    forn(i, ln) bb[i] = (i < sz(b) ? b[i] : 0);

    fft(aa, ln, false);
    fft(bb, ln, false);

    forn(i, ln) cc[i] = mul(aa[i], bb[i]);

    fft(cc, ln, true);

    vector<int> c(ln, 0);
    forn(i, sz(c)) c[i] = cc[i];

    while (sz(c) > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

int n, k, a[11];

inline bool read() {
    if (!(cin >> n >> k))
        return false;
    forn(i, k) cin >> a[i];
    return true;
}

inline void solve() {
    sort(a, a + k);

    vector<int> ans(1, 1);
    vector<int> f(10, 0);
    forn(i, k) f[a[i]] = 1;

    precalc();

    int pw = n / 2;
    while (pw > 0) {
        if (pw & 1)
            ans = multiply(ans, f);
        f = multiply(f, f);
        cout << f.size() << endl;
        pw >>= 1;
    }

    int res = 0;
    forn(i, sz(ans)) res = norm(res + mul(ans[i], ans[i]));
    cout << res << endl;
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    int tt = clock();
#endif
    cout << fixed << setprecision(15);

    if (read()) {
        solve();

#ifdef _DEBUG
        cerr << "TIME = " << clock() - tt << endl;
        tt = clock();
#endif
    }
    return 0;
}