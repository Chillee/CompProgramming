#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 3e5 + 5;
ll N;
string S[MAXN];
ll openLeft[MAXN];
ll openRight[MAXN];
ll closed;
int main() {
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> S[i];
    }

    for (ll i = 0; i < N; i++) {
        ll left = 0;
        ll right = 0;
        ll cur = 0;
        for (auto j : S[i]) {
            if (j == ')') {
                if (cur > 0)
                    cur--;
                else {
                    left++;
                }
            } else {
                cur++;
            }
        }
        right = cur;
        if (right > 0 && left > 0)
            continue;
        if (left > 0) {
            openLeft[left]++;
        } else if (right > 0) {
            openRight[right]++;
        } else {
            closed++;
        }
    }
    ll ans = 0;
    for (ll i = 0; i < MAXN; i++) {
        ans += openLeft[i] * openRight[i];
    }
    ans += closed * closed;
    cout << ans << endl;
}