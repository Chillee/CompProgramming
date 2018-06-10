#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll MAXN = 1e5 + 5;
ll N, M;
ll A[MAXN];
ll orig[MAXN];

bool isPossible(ll curTime) {
    for (ll i = 0; i < N; i++) {
        A[i] = orig[i];
    }
    ll right = N - 1;
    for (ll m = 0; m < M; m++) {
        if (right == -1)
            return true;

        ll cur = curTime;
        while (A[right] == 0 && right >= 0)
            right--;
        cur -= right + 1;
        while (cur > 0 && right >= 0) {
            if (cur >= A[right]) {
                cur -= A[right];
                A[right] = 0;
                right--;
            } else {
                A[right] -= cur;
                cur = 0;
            }
        }
    }
    while (right >= 0 && A[right] == 0)
        right--;
    return (right < 0);
}

ll bin_search(ll l, ll r) {
    if (l == r - 1) {
        return r;
    }

    ll mid = (l + r) / 2;
    if (isPossible(mid)) {
        return bin_search(l, mid);
    } else {
        return bin_search(mid, r);
    }
}
int main() {
    cin >> N >> M;
    for (ll i = 0; i < N; i++) {
        cin >> orig[i];
    }
    cout << bin_search(0, 1e18) << endl;
}