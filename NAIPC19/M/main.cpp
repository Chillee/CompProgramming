#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 18;
const ll MAXV = 1 << MAXN;
const ll MOD = 1e9 + 7;
ll X[MAXV][MAXN];
ll M, N;
ll P[MAXV];
ll binExp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
struct Dsu {
    int par[MAXV * MAXN + 5], sz[MAXV * MAXN + 5];
    void init(int n) { iota(par, par + n, 0), fill(sz, sz + n, 1); }
    int root(int v) { return v == par[v] ? v : (par[v] = root(par[v])); }

    void merge(int a, int b) {
        if ((a = root(a)) == (b = root(b)))
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
};

Dsu dsu;
int getRootVal(int r, int c) {
    int root = dsu.root(r * MAXN + c);
    return X[root / MAXN][root % MAXN];
}
void setRootVal(int r, int c, int v) {
    int root = dsu.root(r * MAXN + c);
    X[root / MAXN][root % MAXN] = v;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 0; i < MAXV; i++)
        for (ll j = 0; j < MAXN; j++)
            X[i][j] = -1;
    cin >> M >> N;
    for (ll i = 0; i < (1 << M); i++) {
        cin >> P[i];
        P[i]--;
    }
    dsu.init(MAXV * MAXN + 5);
    vector<array<int, 2>> sm;
    for (ll i = 0; i < (1 << M); i++) {
        bitset<MAXN> mask(i);
        for (ll j = 0; j < M; j++) {
            if (!mask[j])
                continue;
            bitset<MAXN> tmp(mask.to_ulong());
            tmp[j] = 0;
            ll aIdx = P[tmp.to_ulong()], bIdx = P[mask.to_ulong()];
            if (aIdx != bIdx) {
                for (int k = j + 1; k < M; k++) {
                    int aRootVal = getRootVal(aIdx, k);
                    int bRootVal = getRootVal(bIdx, k);
                    if (aRootVal != bRootVal) {
                        if (aRootVal == -1 || bRootVal == -1) {
                            int res = max(aRootVal, bRootVal);
                            setRootVal(aIdx, k, res);
                            setRootVal(bIdx, k, res);
                        } else {
                            cout << "0" << endl;
                            return 0;
                        }
                    }
                    dsu.merge(aIdx * MAXN + k, bIdx * MAXN + k);
                }
                if (dsu.root(aIdx * MAXN + j) == dsu.root(bIdx * MAXN + j)) {
                    cout << "0" << endl;
                    return 0;
                }
                int rootA = dsu.root(aIdx * MAXN + j), rootB = dsu.root(bIdx * MAXN + j);
                X[rootA / MAXN][rootA % MAXN] = 1;
                X[rootB / MAXN][rootB % MAXN] = 0;
            }
        }
    }
    set<int> cnts;
    for (ll i = 0; i < N; i++) {
        for (ll j = M - 1; j >= 0; j--) {
            int root = dsu.root(i * MAXN + j);
            if (X[root / MAXN][root % MAXN] == -1) {
                cnts.insert(root);
            }
        }
        // cout << endl;
    }
    cout << binExp(2, cnts.size()) << endl;
}