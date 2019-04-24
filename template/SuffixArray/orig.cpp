#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
namespace mine {
template <int MAXN, int lim = 256> struct SuffixArray {
    int n, alpha, sa[MAXN], lcp[MAXN], cur[MAXN], prv[MAXN];
    void cntSort() {
        vector<int> w(max(alpha, n));
        for (int i = 0; i < n; ++i) w[cur[prv[i]]]++;
        for (int i = 0; i < alpha - 1; ++i)
            w[i + 1] += w[i];
        for (int i = n - 1; i >= 0; --i)
            sa[--w[cur[prv[i]]]] = prv[i];
    }
    bool isEq(int a, int b, int l) {
        return (prv[a] == prv[b] &&
                prv[a + l] == prv[b + l]);
    }
    void process(vector<int> &a) {
        n = a.size(), alpha = lim;
        copy(&a[0], &a[0] + n, cur), iota(prv, prv + n, 0);
        cntSort();
        int nClass = 1;
        for (int l = 1; nClass < n;
             l <<= 1, alpha = nClass) {
            for (int i = 0; i < l; i++) prv[i] = i - l + n;
            for (int k = 0, p = l; k < n; ++k)
                if (sa[k] >= l)
                    prv[p++] = sa[k] - l;
            cntSort();
            swap(cur, prv), cur[sa[0]] = 0, nClass = 1;
            for (int i = 1; i < n; i++)
                cur[sa[i]] = isEq(sa[i - 1], sa[i], l)
                                 ? nClass - 1
                                 : nClass++;
        }
        // vector<int> c(n); // lcp
        // for (int i = 0; i < n; i++)
        //     c[sa[i]] = i;
        // for (int i = 0, j, k = 0; i < n; lcp[c[i++]] = k)
        // {
        //     if (c[i] > 0)
        //         for (k ? k-- : 0, j = sa[c[i] - 1]; a[i +
        //         k] == a[j + k]; k++)
        //             ;
        //     else
        //         k = 0;
        // }
    }
};
} // namespace mine
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
        while ((1 << q) < N) q++;
        for (int moc = 0;; moc++) {
            count_sort(
                b, q); // sort(all(b)) can be used as well
            a[b[0].second] = 0;
            for (int i = 1; i < N; i++)
                a[b[i].second] =
                    a[b[i - 1].second] +
                    (b[i - 1].first != b[i].first);

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
        for (int i = 0; i < n; i++) inv[a[i]] = i;
        for (int i = 0; i < n; i++)
            if (inv[i] > 0) {
                int p0 = a[inv[i] - 1];
                while (s[i + h] == s[p0 + h]) h++;
                res[inv[i]] = h;
                if (h > 0)
                    h--;
            }
        return res;
    }
};
} // namespace kactl
namespace MIT {
const int maxn = MAXN;
int wa[2 * maxn], wb[2 * maxn], wv[maxn], ws[maxn];
int sa[maxn];
int mx = 0;
int cmp(int *r, int a, int b, int l) { /// start-hash
    mx = max(mx, a + l), mx = max(mx, b + l);
    if (max(a + l, b + l) > MAXN)
        cout << a + l << ' ' << b + l << ' ' << MAXN
             << endl;
    return r[a] == r[b] && r[a + l] == r[b + l];
}
void da(int *r, int *sa, int n, int m) {
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) ws[i] = 0;
    for (i = 0; i < n; i++) ws[x[i] = r[i]]++;
    for (i = 1; i < m; i++) ws[i] += ws[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p) {
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < n; i++) wv[i] = x[y[i]];
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[wv[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0,
            i = 1;
             i < n; i++)
            x[sa[i]] =
                cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
} /// end-hash
} // namespace MIT

struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) {
        begin = chrono::high_resolution_clock::now();
    }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::milliseconds>(
                end - begin)
                .count();
        cerr << duration << "ms elapsed [" << label << "]"
             << endl;
    }
};
mine::SuffixArray<MAXN> mineSa;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> vS;
    string S;
    for (int i = 0; i < MAXN; i++) {
        int t = rand() % 1;
        vS.push_back(t);
        S.push_back(t + 'a');
    }

    // cout << S << endl;
    // {
    //     timeit x("mine");
    //     mineSa.process(vS);
    //     cout << mineSa.sa[100] << endl;
    // }
    // {
    //     timeit x("kactl");
    //     kactl::SuffixArray kactl(S);
    //     cout << kactl.a[101] << endl;
    // }
    {
        timeit x("MIT");
        MIT::da(vS.data(), MIT::sa, MAXN, 250);
        cout << MIT::sa[100] << endl;
        // cout << MIT::mx << ' ' << MAXN << endl;
    }
}