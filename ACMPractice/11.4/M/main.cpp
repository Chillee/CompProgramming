#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 4.1e5 + 5;
ll N;
vector<array<ll, 2>> V[MAXN];
ll idxs[MAXN];

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

SuffixArray test;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    vector<int> combined;
    for (ll i = 0; i < N; i++) {
        ll K;
        cin >> K;
        for (ll j = 0; j < K; j++) {
            ll t;
            cin >> t;
            V[i].push_back({t, -1});
            combined.push_back(t);
        }
        combined.push_back(301);
    }
    test.process(combined, 305);
    vector<ll> rank(combined.size());
    for (ll i = 0; i < test.n; i++) {
        rank[test.sa[i]] = i;
    }

    ll idx = 0;
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < V[i].size(); j++) {
            V[i][j][1] = rank[idx];
            idx++;
        }
        idx++;
    }
    set<array<ll, 3>> cur;
    for (ll i = 0; i < N; i++) {
        cur.insert({V[i][idxs[i]][1], V[i][idxs[i]][0], i});
        idxs[i]++;
    }
    vector<ll> ans;
    while (cur.size() > 0) {
        auto top = *cur.begin();
        cur.erase(top);
        if (idxs[top[2]] < V[top[2]].size())
            cur.insert({V[top[2]][idxs[top[2]]][1], V[top[2]][idxs[top[2]]][0], top[2]});
        idxs[top[2]]++;

        ans.push_back(top[1]);
    }
    ll fans = 0;
    ll pw = 365;
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        fans += i * pw;
        fans %= MOD;
        pw *= 365;
        pw %= MOD;
    }
    cout << fans << endl;
}