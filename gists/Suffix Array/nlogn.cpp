struct SuffixArray {
    const static int MAXN = ::MAXN;
    int n, alpha;
    int sa[MAXN], lcp[MAXN];
    int cur[MAXN], prv[MAXN];

    void cntSort() {
        vector<int> w(max(alpha, n));
        for (int i = 0; i < n; ++i)
            w[cur[prv[i]]]++;
        for (int i = 0; i < alpha - 1; ++i)
            w[i + 1] += w[i];
        for (int i = n - 1; i >= 0; --i)
            sa[--w[cur[prv[i]]]] = prv[i];
    }

    bool isEq(int a, int b, int l) { return (prv[a] == prv[b] && prv[a + l] == prv[b + l]); }
    void process(vector<int> &a, int lim = 256) {
        n = a.size(), alpha = lim;
        for (int i = 0; i < n; ++i)
            cur[i] = a[i], prv[i] = i;
        cntSort();
        int nClass = 1;
        for (int l = 1; nClass < n; l <<= 1, alpha = nClass) {
            for (int i = 0; i < l; i++)
                prv[i] = i - l + n;
            for (int k = 0, p = l; k < n; ++k)
                if (sa[k] >= l)
                    prv[p++] = sa[k] - l;
            cntSort();
            swap(cur, prv), cur[sa[0]] = 0, nClass = 1;
            for (int i = 1; i < n; i++)
                cur[sa[i]] = isEq(sa[i - 1], sa[i], l) ? nClass - 1 : nClass++;
        }

        vector<int> c(n); // lcp
        for (int i = 0; i < n; i++)
            c[sa[i]] = i;
        for (int i = 0, j, k = 0; i < n; lcp[c[i++]] = k) {
            if (c[i] > 0)
                for (k ? k-- : 0, j = sa[c[i] - 1]; a[i + k] == a[j + k]; k++)
                    ;
            else
                k = 0;
        }
    }
};