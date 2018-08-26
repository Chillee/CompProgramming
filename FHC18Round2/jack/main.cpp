#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
ll T, N, M, A, B;
vector<ll> C;
ll par[MAXN];
vector<ll> child[MAXN];
ll depth[MAXN];
ll treeStart[MAXN];
ll treeEnd[MAXN];

ll seg[2 * MAXN];
void build() {
    for (ll i = N - 1; i >= 0; i--)
        seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
}

void modify(ll p, ll val) {
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = max(seg[p], seg[p ^ 1]);
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = max(seg[l++], res);
        if (r & 1)
            res = max(res, seg[--r]);
    }
    return res;
}

ll cnt;
void flatten(ll cur, ll curDepth) {
    treeStart[cur] = cnt;
    depth[cur] = curDepth;
    for (auto i : child[cur]) {
        cnt++;
        flatten(i, curDepth + 1);
    }
    treeEnd[cur] = cnt;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> T;
    for (ll t = 1; t <= T; t++) {
        fill(begin(treeStart), end(treeStart), 0);
        fill(begin(treeEnd), end(treeEnd), 0);
        fill(child, child + MAXN, vector<ll>());
        fill(seg, seg + 2 * MAXN, 0);
        C.clear();
        cin >> N >> M >> A >> B;
        vector<ll> Ms;
        for (ll i = 1; i < N; i++) {
            cin >> par[i];
        }
        for (ll i = 1; i < N; i++) {
            child[par[i]].push_back(i);
        }
        for (ll i = 0; i < M; i++) {
            Ms.push_back((A * i + B) % N);
        }
        cnt = 0;
        flatten(0, 0);
        for (ll i = 0; i < N; i++) {
            seg[treeStart[i] + N] = i;
        }
        build();
        ll ans = 0;
        sort(Ms.begin(), Ms.end(), [](ll a, ll b) { return depth[a] > depth[b]; });
        for (auto i : Ms) {
            ll res = query(treeStart[i], treeEnd[i] + 1);
            ans += res;
            modify(treeStart[res], 0);
            if (query(0, N) == 0)
                break;
        }
        cout << "Case #" << t << ": " << ans << endl;
    }
}