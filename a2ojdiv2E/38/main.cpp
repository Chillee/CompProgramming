#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll MAXBIT = 17;
const ll INF = 1e9;
ll N, M;
ll A[MAXN];
set<pair<ll, ll>> intervals[MAXBIT];
ll totCnt[MAXN];

void replace(pair<ll, ll> a, pair<ll, ll> b, ll bit) {
    ll dista = a.second - a.first;
    ll distb = b.second - b.first;
    intervals[bit].insert(b);
    intervals[bit].erase(a);
    totCnt[bit] -= dista * (dista + 1) / 2;
    totCnt[bit] += distb * (distb + 1) / 2;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (ll b = 0; b < MAXBIT; b++) {
        ll cnt = 0;
        ll curCnt = 0;
        bool inOne = false;
        for (ll i = 0; i < N; i++) {
            if ((A[i] & (1 << b)) != 0) {
                if (!inOne) {
                    inOne = true;
                }
                curCnt++;
            } else {
                if (inOne) {
                    intervals[b].insert({i - curCnt, i});
                    cnt += curCnt * (curCnt + 1) / 2;
                    curCnt = 0;
                    inOne = false;
                }
            }
        }
        if (inOne) {
            intervals[b].insert({N - curCnt, N});
            cnt += curCnt * (curCnt + 1) / 2;
        }
        totCnt[b] = cnt;
    }

    for (ll t = 0; t < M; t++) {
        ll p, v;
        cin >> p >> v;
        p--;
        A[p] = v;
        for (ll b = 0; b < MAXBIT; b++) {
            if ((A[p] & (1 << b)) != 0) {
                if (intervals[b].size() == 0) {
                    intervals[b].insert({p, p + 1});
                    totCnt[b] += 1;
                    continue;
                } else if (intervals[b].size() == 1) {
                    if (intervals[b].begin()->first == p + 1) {
                        replace(*intervals[b].begin(), {p, intervals[b].begin()->second}, b);
                    } else if (intervals[b].begin()->second == p) {
                        replace(*intervals[b].begin(), {intervals[b].begin()->first, p}, b);
                    } else {
                        intervals[b].insert({p, p + 1});
                        totCnt[b] += 1;
                    }
                    continue;
                }
                auto cur = intervals[b].lower_bound({p, INF});
                if (cur == intervals[b].begin()) {
                    if (cur->first == p + 1) {
                        replace(*cur, {p, cur->second}, b);
                    } else {
                        intervals[b].insert({p, p + 1});
                        totCnt[b] += 1;
                    }
                    continue;
                }
                cur--;
                auto nxt = next(cur);
                if (nxt == intervals[b].end()) {
                    if (cur->second == p) {
                        replace(*cur, {cur->first, p}, b);
                    } else {
                        intervals[b].insert({p, p + 1});
                        totCnt[b] += 1;
                    }
                } else if (nxt->first > p + 1 && cur->second < p) {
                    intervals[b].insert({p, p + 1});
                    totCnt[b] += 1;
                } else if (cur->first <= p && cur->second > p) {
                    continue;
                } else if (cur->second == p && nxt->first == p + 1) {
                    totCnt[b] -= (cur->second - cur->first) * (cur->second - cur->first + 1) / 2;
                    totCnt[b] -= (nxt->second - nxt->first) * (nxt->second - nxt->first + 1) / 2;
                    totCnt[b] += (nxt->second - cur->first) * (nxt->second - cur->first + 1) / 2;
                    intervals[b].insert({cur->first, nxt->second});
                    intervals[b].erase(cur);
                    intervals[b].erase(nxt);
                } else if (cur->second == p) {
                    replace(*cur, {cur->first, p + 1}, b);
                } else if (nxt->first == p + 1) {
                    replace(*nxt, {p, nxt->second}, b);
                }
            } else {
                if (intervals[b].size() == 0)
                    continue;
                auto cur = intervals[b].lower_bound({p, INF});
                if (cur != intervals[b].begin())
                    cur--;
                if (cur->first <= p && cur->second > p) {
                    totCnt[b] -= (cur->second - cur->first) * (cur->second - cur->first + 1) / 2;
                    totCnt[b] += (p - cur->first) * (p - cur->first + 1) / 2;
                    totCnt[b] += (cur->second - (p + 1)) * (cur->second - (p + 1) + 1) / 2;
                    if (p != cur->first)
                        intervals[b].insert({cur->first, p});
                    if (p + 1 != cur->second)
                        intervals[b].insert({p + 1, cur->second});
                    intervals[b].erase(cur);
                }
            }
        }
        // for (ll b = 0; b < 5; b++) {
        //     for (auto i : intervals[b]) {
        //         cout << "(" << i.first << "," << i.second << ") ";
        //     }
        //     cout << endl;
        // }

        ll ans = 0;
        for (ll b = 0; b < MAXBIT; b++) {
            ans += (totCnt[b] * (1 << b));
        }
        cout << ans << endl;
    }
}