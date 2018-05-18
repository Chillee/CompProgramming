#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
ll N, M, K;
ll A[MAXN];
ll L[MAXN], R[MAXN], D[MAXN];
ll X[MAXN], Y[MAXN];
ll cnt[MAXN], queryCnt[MAXN];
ll seg[MAXN * 2];
void modify(ll l, ll r, ll val) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            seg[l++] += val;
        if (r & 1) {
            seg[--r] += val;
        }
    }
}

ll query(ll p) {
    ll res = 0;
    for (p += N; p > 0; p >>= 1) {
        res += seg[p];
    }
    return res;
}
void push() {
    for (ll i = 1; i < N; i++) {
        seg[i << 1] += seg[i];
        seg[i << 1 | 1] += seg[i];
        seg[i] = 0;
    }
}

int main() {
    cin >> N >> M >> K;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (ll i = 0; i < M; i++) {
        cin >> L[i] >> R[i] >> D[i];
        L[i]--, R[i]--;
    }
    for (ll i = 0; i < K; i++) {
        cin >> X[i] >> Y[i];
        X[i]--;
        cnt[X[i]]++;
        cnt[Y[i]]--;
    }
    ll cur = 0;
    for (ll i = 0; i < M; i++) {
        cur += cnt[i];
        queryCnt[i] = cur;
    }
    for (ll i = 0; i < N; i++) {
        seg[i + N] = A[i];
    }
    for (ll i = 0; i < M; i++) {
        modify(L[i], R[i] + 1, queryCnt[i] * D[i]);
    }
    push();
    for (ll i = N; i < 2 * N; i++) {
        cout << seg[i] << ' ';
    }
    cout << endl;
}