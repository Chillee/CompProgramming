#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;

ll N;
ll A[MAXN];
pair<double, int> Fs[MAXN], Fe[MAXN];
double D[MAXN];
double calc(pair<double, ll> x, ll curIdx) { return x.first / (abs(x.second - curIdx) + 1); }
double f(vector<pair<double, ll>> &vals, ll idx, ll curIdx) {
    if (idx < 0 || idx >= vals.size())
        return 1e10;
    return calc(vals[idx], curIdx);
}
pair<double, int> getMx(vector<pair<double, ll>> vals, ll curIdx) {
    double res = 0;
    int idx = 0;
    for (int i = 0; i < vals.size(); i++) {
        if (calc(vals[i], curIdx) > res) {
            res = calc(vals[i], curIdx);
            idx = vals[i].second;
        }
    }
    return {res, idx};
}
double p(int r, int l) {
    if (l == 0)
        return 0;
    else if (r < l)
        return 1 - p(l, r);
    int d = r - l;
    int f1d = (d / l) + 2;
    int f2d = (d / l) + 3;
    int wa = l - (d % l);
    int wb = l - wa;
    // cout << d << endl;
    // cout << f1d << ' ' << f2d << ' ' << wa << ' ' << wb << endl;
    return l / (wa * f1d + wb * f2d + 0.0);
}
int seg[2 * MAXN];
void build() {
    for (int i = N - 1; i >= 0; i--)
        seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
}

void modify(int p, int val) {
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = max(seg[p], seg[p ^ 1]);
}

int query(int l, int r) {
    int res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = max(seg[l++], res);
        if (r & 1)
            res = max(res, seg[--r]);
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << p(7, 4) << endl;
    return 0;
    freopen("balance.in", "r", stdin);
    // freopen("balance.out", "w", stdout);
    cin >> N;
    for (ll i = 1; i <= N; i++) {
        cin >> A[i];
        seg[i - 1 + N] = A[i];
    }
    vector<pair<double, ll>> curVals;
    curVals.push_back({A[N], N});
    for (ll i = N - 1; i > 0; i--) {
        ll l = 0, r = curVals.size();
        while (abs(r - l) > 5) {
            ll mid = (r + l) / 2;
            double fl = f(curVals, mid - 1, i);
            double fm = f(curVals, mid, i);
            double fr = f(curVals, mid + 1, i);
            if (fr < fm && fm > fr)
                break;
            if (fl < fm && fm < fr) {
                l = mid - 1;
            } else {
                r = mid + 1;
            }
        }
        vector<pair<double, ll>> t;
        for (ll j = l; j < r; j++) {
            t.push_back(curVals[j]);
        }
        Fs[i] = getMx(t, i);
        while (!curVals.empty() && A[i] >= curVals.back().first)
            curVals.pop_back();
        curVals.push_back({A[i], i});
    }

    curVals.clear();
    curVals.push_back({A[0], 0});
    for (ll i = 1; i <= N; i++) {
        ll l = 0, r = curVals.size();
        while (abs(r - l) > 5) {
            ll mid = (r + l) / 2;
            double fl = f(curVals, mid - 1, i);
            double fm = f(curVals, mid, i);
            double fr = f(curVals, mid + 1, i);
            if (fr < fm && fm > fr)
                break;
            if (fl < fm && fm < fr) {
                l = mid - 1;
            } else {
                r = mid + 1;
            }
        }
        vector<pair<double, ll>> t;
        for (ll j = l; j < r; j++) {
            t.push_back(curVals[j]);
        }
        Fe[i] = getMx(t, i);
        while (!curVals.empty() && A[i] >= curVals.back().first)
            curVals.pop_back();
        curVals.push_back({A[i], i});
    }
    multiset<array<ll, 2>> s, e;
    for (int i = 1; i <= N; i++) {
        e.insert({A[i], i});
    }
    for (int i = 1; i <= N; i++) {
        s.insert({A[i], i});
        int idx1 = (*s.rbegin())[1];
        int idx2 = (*e.rbegin())[1];
        double p1 = p(abs(idx1 - i), abs(idx2 - i));
        // cout << i << endl;
        // cout << p1 << endl;
        // cout << endl;
        D[i] = max(A[i] + 0., p1 * A[idx1] + (1 - p1) * A[idx2]);
        e.erase({A[i], i});
    }
    // for (ll i = 1; i <= N; i++) {
    //     cout << Fs[i].first << ' ';
    // }
    // cout << endl;
    // for (ll i = 1; i <= N; i++) {
    //     cout << Fe[i].first << ' ';
    // }
    // cout << endl;
    // for (ll i = 1; i <= N; i++) {
    //     cout << D[i] << ' ';
    // }
    // cout << endl;
    for (ll i = 1; i <= N; i++) {
        cout << (ll)floor(D[i] * 100000) << endl;
    }
}