#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct absCompare {
    bool operator()(const ll &lhs, const ll &rhs) { return abs(lhs) < abs(rhs); }
};
priority_queue<ll, vector<ll>, absCompare> cur;
const ll MAXN = 1e3 + 5;
ll N;
ll A[MAXN], B[MAXN];
ll K1, K2;

int main() {
    cin >> N >> K1 >> K2;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (ll i = 0; i < N; i++) {
        cin >> B[i];
    }
    for (ll i = 0; i < N; i++) {
        cur.push(A[i] - B[i]);
    }
    for (ll i = 0; i < K1 + K2; i++) {
        ll t = cur.top();
        cur.pop();
        if (t < 0) {
            t++;
        } else {
            t--;
        }
        cur.push(t);
    }
    long long res = 0;
    while (!cur.empty()) {
        ll i = cur.top();
        res += i * i;
        cur.pop();
    }
    cout << res << endl;
}