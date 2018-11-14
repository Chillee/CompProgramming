#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e5 + 5;
ll N;
vector<array<ll, 2>> V[MAXN];
ll idxs[MAXN];

struct SuffixArray {
    int n, m;
    vector<int> SA, LCP, x, y;

    SuffixArray(vector<int> &a, int lim = 256) : n(a.size()), m(lim), SA(n), LCP(n), x(n), y(n) {
        for (int i = 0; i < n; ++i)
            x[i] = a[i], y[i] = i;
        rsort();
        for (int i, j = 1, p = 1; p < n; j <<= 1, m = p) {
            for (p = 0, i = n - j; i < n; i++)
                y[p++] = i;
            for (int k = 0; k < n; ++k)
                if (SA[k] >= j)
                    y[p++] = SA[k] - j;
            rsort();
            for (swap(x, y), p = 1, x[SA[0]] = 0, i = 1; i < n; ++i)
                x[SA[i]] = cmp(SA[i - 1], SA[i], j) ? p - 1 : p++;
        }

        vector<int> c(n); // lcp
        for (int i = 0; i < n; i++)
            c[SA[i]] = i;
        for (int i = 0, j, k = 0; i < n; LCP[c[i++]] = k) {
            if (c[i] > 0)
                for (k ? k-- : 0, j = SA[c[i] - 1]; a[i + k] == a[j + k]; k++)
                    ;
            else
                k = 0;
        }
    }

    void rsort() {
        vector<int> w(max(m, n));
        for (int i = 0; i < n; ++i)
            w[x[y[i]]]++;
        for (int i = 0; i < m - 1; ++i)
            w[i + 1] += w[i];
        for (int i = n - 1; i >= 0; --i)
            SA[--w[x[y[i]]]] = y[i];
    }
    inline bool cmp(const int a, const int b, const int l) { return (y[a] == y[b] && y[a + l] == y[b + l]); }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string t = "abcabcde";
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
    SuffixArray test = SuffixArray(combined, 305);
    // auto res = suffix_array(combined, 305);
    vector<ll> rank(combined.size());
    for (ll i = 0; i < test.n; i++) {
        // cout << test.SA[i] << " ";
        rank[test.SA[i]] = i;
    }
    // cout << endl;

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