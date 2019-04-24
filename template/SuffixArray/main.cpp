// #pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
#define all(x) x.begin(), x.end()

const int MAXN = 1e6;
namespace kactl {
typedef long long ll;
typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
    // this is just 3 times faster than stl sort for N=10^6
    int mask = (1 << bits) - 1;
    for (int it = 0; it < 2; it++) {
        int move = it * bits;
        vector<int> q(1 << bits), w((q).size() + 1);
        for (int i = 0; i < (b).size(); i++)
            q[(b[i].first >> move) & mask]++;
        partial_sum(q.begin(), q.end(), w.begin() + 1);
        vector<pli> res(b.size());
        for (int i = 0; i < (b).size(); i++)
            res[w[(b[i].first >> move) & mask]++] = b[i];
        swap(b, res);
    }
}
struct SuffixArray {
    vector<int> a;
    string s;
    SuffixArray(const string &_s) : s(_s + '\0') {
        int N = (s).size();
        vector<pli> b(N);
        a.resize(N);
        for (int i = 0; i < N; i++) {
            b[i].first = s[i];
            b[i].second = i;
        }

        int q = 8;
        while ((1 << q) < N)
            q++;
        for (int moc = 0;; moc++) {
            count_sort(b, q); // sort(all(b)) can be used as well
            a[b[0].second] = 0;
            for (int i = 1; i < N; i++)
                a[b[i].second] = a[b[i - 1].second] + (b[i - 1].first != b[i].first);

            if ((1 << moc) >= N)
                break;
            for (int i = 0; i < N; i++) {
                b[i].first = (ll)a[i] << q;
                if (i + (1 << moc) < N)
                    b[i].first += a[i + (1 << moc)];
                b[i].second = i;
            }
        }
        for (int i = 0; i < (a).size(); i++)
            a[i] = b[i].second;
    }
    vector<int> lcp() {
        // longest common prefixes: res[i] = lcp(a[i],
        // a[i-1])
        int n = (a).size(), h = 0;
        vector<int> inv(n), res(n);
        for (int i = 0; i < n; i++)
            inv[a[i]] = i;
        for (int i = 0; i < n; i++)
            if (inv[i] > 0) {
                int p0 = a[inv[i] - 1];
                while (s[i + h] == s[p0 + h])
                    h++;
                res[inv[i]] = h;
                if (h > 0)
                    h--;
            }
        return res;
    }
};
} // namespace kactl
namespace MIT {

struct SuffixArray { // sa[0] = n, sa[i] = i-th in sorted suffix array. O(n log n)
#define rep(i, a, b) for (int i = a; i < (b); i++)
    vector<int> sa, lcp;
    SuffixArray(string &s, int lim = 256) { // no null characters, use basic_string<int> to extend
        int n = s.size() + 1, k = 0, a, b;
        vector<int> x(all(s) + 1), y(n), ind(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            rep(i, 0, n) ind[i] = x[y[i]];
            fill(all(ws), 0);
            rep(i, 0, n) ws[ind[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;)
                sa[--ws[ind[i]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        } // lcp[0] = 0, lcp[i] = lcp(sa[i], sa[i-1])
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
                ;
    }
#undef rep
};
} // namespace MIT
namespace NewKACTL {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
struct SuffixArray {
    vi sa, lcp;
    template <class T> SuffixArray(basic_string<T> &s, int lim = 256) {
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s) + 1), y(n), ind(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            rep(i, 0, n) ind[i] = x[y[i]];
            fill(all(ws), 0);
            rep(i, 0, n) ws[ind[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;)
                sa[--ws[ind[i]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
                ;
    }
};
} // namespace NewKACTL
struct SuffixArray { // sa[0] = n, sa[i] = i-th in sorted suffix array. O(n log n)
#define rep(i, a, b) for (int i = a; i < (b); i++)
    vector<int> sa, lcp;
    SuffixArray(string &s, int lim = 256) { // no null characters, use basic_string<int> to extend
        int n = s.size() + 1, k = 0, a, b;
        vector<int> x(all(s) + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            partial_sum(all(ws), begin(ws));
            for (int i = n; i--;)
                sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        } // lcp[0] = 0, lcp[i] = lcp(sa[i], sa[i-1])
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
                ;
    }
#undef rep
};

namespace ChinaDC3 {
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x)*3 + 1 : ((x)-tb) * 3 + 2)

const int maxn = MAXN;
struct DC3 {
    int sa[2 * maxn];
    int wa[maxn], wb[maxn], wv[maxn], ws[maxn];
    int c0(int *r, int a, int b) { return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2]; }
    int c12(int k, int *r, int a, int b) {
        if (k == 2)
            return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
        else
            return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
    }
    void sort(int *r, int *a, int *b, int n, int m) {
        int i;
        for (i = 0; i < n; i++)
            wv[i] = r[a[i]];
        for (i = 0; i < m; i++)
            ws[i] = 0;
        for (i = 0; i < n; i++)
            ws[wv[i]]++;
        for (i = 1; i < m; i++)
            ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            b[--ws[wv[i]]] = a[i];
        return;
    }
    void dc3(int *r, int *sa, int n, int m) {
        int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; i++)
            if (i % 3 != 0)
                wa[tbc++] = i;
        sort(r + 2, wa, wb, tbc, m);
        sort(r + 1, wb, wa, tbc, m);
        sort(r, wa, wb, tbc, m);
        for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
            rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;

        if (p < tbc)
            dc3(rn, san, tbc, p);
        else
            for (i = 0; i < tbc; i++)
                san[rn[i]] = i;
        for (i = 0; i < tbc; i++)
            if (san[i] < tb)
                wb[ta++] = san[i] * 3;
        if (n % 3 == 1)
            wb[ta++] = n - 1;
        sort(r, wb, wa, ta, m);
        for (i = 0; i < tbc; i++)
            wv[wb[i] = G(san[i])] = i;
        for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
            sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
        for (; i < ta; p++)
            sa[p] = wa[i++];
        for (; j < tbc; p++)
            sa[p] = wb[j++];
        return;
    }
    int rank[3 * maxn];
    int height[3 * maxn];
    void calheight(int *r, int *sa, int n) {
        int i, j, k = 0;
        for (i = 1; i <= n; i++)
            rank[sa[i]] = i;
        for (i = 0; i < n; height[rank[i++]] = k)
            for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++)
                ;
        return;
    }
};

} // namespace ChinaDC3

struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(0);
    for (int iter = 0; iter < 1; iter++) {
        vector<int> vS;
        string S;

        for (int i = 0; i < MAXN; i++) {
            int t = rand() % 26 + 1;
            // int t = 0;
            // vS.push_back(t + 1);
            S.push_back(t);
        }
        vector<array<int, 2>> res;
        {
            timeit x("kactl");
            kactl::SuffixArray kactl(S);
            // cout << kactl.a[100] << endl;
            auto lcp = kactl.lcp();
            for (int i = 0; i <= vS.size(); i++)
                res.push_back({kactl.a[i], lcp[i]});
        }
        {
            timeit x("New KACTL");
            basic_string<int> t(vS.begin(), vS.end());
            NewKACTL::SuffixArray sa(S);
            // cout << sa.sa[100] << endl;
            for (int i = 0; i <= vS.size(); i++) {
                assert((res[i] == array<int, 2>{sa.sa[i], sa.lcp[i]}));
            }
        }
        {
            timeit x("MIT");
            MIT::SuffixArray sa(S, 27);
            for (int i = 0; i <= vS.size(); i++) {
                assert((res[i] == array<int, 2>{sa.sa[i], sa.lcp[i]}));
            }
        }
        // int r[3 * MAXN];
        // for (int i = 0; i < MAXN; i++) {
        //     r[i] = 'a' + (rand() % 2);
        // }
        // {
        //     timeit x("China DC3");
        //     ChinaDC3::DC3 dc3;
        //     vS.push_back(0);
        //     dc3.dc3(r, dc3.sa, MAXN, 256);
        //     // dc3.calheight(r, dc3.sa, vS.size() - 1);
        //     cout << dc3.sa[100] << endl;
        //     // for (int i = 0; i <= vS.size(); i++) {
        //     //     assert((res[i] == array<int, 2>{dc3.sa[i], dc3.height[i]}));
        //     // }
        // }
    }
}