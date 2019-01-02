#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
ll N;
ll A[MAXN];
ll lmx[MAXN], rmx[MAXN], lmn[MAXN], rmn[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    ll ans = 0;
    stack<ll> cur;
    for (ll i = 0; i < N; i++) {
        while (cur.size() && A[i] >= A[cur.top()]) {
            cur.pop();
        }
        ll cidx = cur.size() ? cur.top() + 1 : 0;
        cur.push(i);
        lmx[i] = cidx;
    }
    stack<ll>().swap(cur);
    for (ll i = N - 1; i >= 0; i--) {
        while (cur.size() && A[i] > A[cur.top()]) {
            cur.pop();
        }
        ll cidx = cur.size() ? cur.top() : N;
        cur.push(i);
        rmx[i] = cidx;
    }
    for (ll i = 0; i < N; i++) {
        ll cnt1 = (i - lmx[i] + 1) * (rmx[i] - i);
        ans += A[i] * cnt1;
    }
    for (int i = 0; i < N; i++)
        A[i] = -A[i];
    stack<ll>().swap(cur);
    for (ll i = 0; i < N; i++) {
        while (cur.size() && A[i] >= A[cur.top()]) {
            cur.pop();
        }
        ll cidx = cur.size() ? cur.top() + 1 : 0;
        cur.push(i);
        lmx[i] = cidx;
    }
    stack<ll>().swap(cur);
    for (ll i = N - 1; i >= 0; i--) {
        while (cur.size() && A[i] > A[cur.top()]) {
            cur.pop();
        }
        ll cidx = cur.size() ? cur.top() : N;
        cur.push(i);
        rmx[i] = cidx;
    }
    for (ll i = 0; i < N; i++) {
        ll cnt1 = (i - lmx[i] + 1) * (rmx[i] - i);
        ans += A[i] * cnt1;
    }
    cout << ans << endl;
}