#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
typedef struct pos {
    ll fifty;
    ll hundred;
    ll fiftyCrossed;
    ll hundredCrossed;
    ll dist;
    ll cnt;
    bool operator<(pos a) const {
        if (a.fifty != fifty)
            return fifty < a.fifty;
        return hundred < a.hundred;
    }
} pos;
const ll MAXN = 55;
const ll INF = 1e9;
const ll MOD = 1e9 + 7;
ll N, K;
ll vis[MAXN][MAXN];
// ll bestWeight[MAXN * MAXN];
ll numFifty, numHundred;
ll factorial[MAXN];
ll invfac[MAXN];
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }

ll nCr(ll n, ll k) {
    if (k < 0 || n < k)
        return 0;
    ll num = factorial[n];
    ll denom = invfac[k] * invfac[n - k] % MOD;
    return (num * denom) % MOD;
}
pos curdp[MAXN][MAXN];
pos otherdp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // fill(bestWeight, bestWeight + MAXN * MAXN, INF);
    factorial[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    for (ll i = 0; i < MAXN; i++) {
        invfac[i] = mod_inv(factorial[i]);
    }
    for (ll i = 0; i < MAXN; i++) {
        for (ll j = 0; j < MAXN; j++) {
            vis[i][j] = INF;
        }
    }
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        ll t;
        cin >> t;
        if (t == 50)
            numFifty++;
        else
            numHundred++;
    }
    otherdp[numFifty][numHundred] = {numFifty, numHundred, 0, 0, 0, 1};
    ll bestDist = INF;

    for (int t = 0; t < 100; t++) {
        vector<pos> collapsedPos;
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if (otherdp[i][j].cnt != 0)
                    collapsedPos.push_back(otherdp[i][j]);
                otherdp[i][j] = {0, 0, 0, 0, 0};
            }
        }
        for (auto cur : collapsedPos) {
            if (cur.cnt == 0)
                continue;
            assert(cur.fifty + cur.fiftyCrossed == numFifty);
            assert(cur.hundred + cur.hundredCrossed == numHundred);
            vis[cur.fifty][cur.hundred] = cur.dist;
            ll fiftyFit = min(K / 50, cur.fifty);
            ll hundredFit = min(K / 100, cur.hundred);
#define FIRSTPROCESS                                                                                                   \
    {                                                                                                                  \
        cur.fifty - leave50, cur.hundred - leave100, cur.fiftyCrossed + leave50, cur.hundredCrossed + leave100,        \
            cur.dist + 1, (cur.cnt * nCr(cur.fifty, leave50)) % MOD *nCr(cur.hundred, leave100) % MOD                  \
    }
            for (ll leave50 = 0; leave50 * 50 <= K && leave50 <= cur.fifty; leave50++) {
                for (ll leave100 = 0; leave100 * 100 + leave50 * 50 <= K && leave100 <= cur.hundred; leave100++) {
                    pos res = FIRSTPROCESS;
                    if (res.cnt == 0)
                        continue;
                    if (leave50 == 0 && leave100 == 0)
                        continue;
                    swap(curdp[res.fifty][res.hundred], res);
                    curdp[res.fifty][res.hundred].cnt = (res.cnt + curdp[res.fifty][res.hundred].cnt) % MOD;
                }
            }
        }
        collapsedPos.clear();
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if (curdp[i][j].cnt != 0)
                    collapsedPos.push_back(curdp[i][j]);
                curdp[i][j] = {0, 0, 0, 0, 0};
            }
        }
        for (auto cur : collapsedPos) {
            if (cur.hundred == 0 && cur.fifty == 0) {
                cout << cur.dist << endl;
                cout << cur.cnt << endl;
                exit(0);
            }
            if (cur.cnt == 0)
                continue;
            // cout << cur.fifty << ' ' << cur.hundred << ' ' << cur.dist << ' ' << cur.cnt << endl;
            assert(cur.fifty + cur.fiftyCrossed == numFifty);
            assert(cur.hundred + cur.hundredCrossed == numHundred);
            // cout << cur.fifty << ' ' << cur.hundred << ' ' << cur.dist << ' ' << cur.cnt << endl;
#define SECONDPROCESS                                                                                                  \
    {                                                                                                                  \
        cur.fifty + leave50, cur.hundred + leave100, cur.fiftyCrossed - leave50, cur.hundredCrossed - leave100,        \
            cur.dist + 1, (cur.cnt * nCr(cur.fiftyCrossed, leave50)) % MOD *nCr(cur.hundredCrossed, leave100) % MOD    \
    }
            for (ll leave50 = 0; leave50 * 50 <= K && leave50 <= cur.fiftyCrossed; leave50++) {
                for (ll leave100 = 0; leave100 * 100 + leave50 * 50 <= K && leave100 <= cur.hundredCrossed;
                     leave100++) {
                    pos res = SECONDPROCESS;
                    if (res.cnt == 0)
                        continue;
                    if (leave50 == 0 && leave100 == 0)
                        continue;
                    // cout << "res: " << res.fifty << ' ' << res.hundred << ' ' << res.cnt << endl;
                    swap(otherdp[res.fifty][res.hundred], res);
                    otherdp[res.fifty][res.hundred].cnt = (res.cnt + otherdp[res.fifty][res.hundred].cnt) % MOD;
                }
            }
        }
    }
    cout << -1 << endl;
    cout << 0 << endl;
    return 0;
}