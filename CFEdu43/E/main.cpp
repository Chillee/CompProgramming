#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll MAXN = 200005;
ll N, A, B;
ll hp[MAXN];
ll atk[MAXN];
bool used[MAXN];
ll minIdx = -1;
vector<pii> diffs;
int main() {
    ios::sync_with_stdio(false);
    cin >> N >> A >> B;
    for (ll i = 0; i < N; i++) {
        cin >> hp[i] >> atk[i];
    }
    for (ll i = 0; i < N; i++) {
        diffs.push_back(pii(hp[i] - atk[i], i));
    }
    sort(diffs.begin(), diffs.end());
    ll numUsed = 0;
    for (ll i = diffs.size() - 1; i >= max(0LL, N - B); i--) {
        auto cur = diffs[i];
        if (hp[cur.second] > atk[cur.second]) {
            used[cur.second] = true;
            numUsed++;
            minIdx = cur.second;
        } else {
            break;
        }
    }
    ll sum = 0;
    for (ll i = 0; i < N; i++) {
        if (used[i]) {
            sum += hp[i];
        } else {
            sum += atk[i];
        }
    }
    ll res = sum;
    if (A == 0 || B == 0) {
        cout << res << endl;
        return 0;
    }
    // cout << res << endl;
    for (ll i = 0; i < N; i++) {
        ll newHP = (hp[i] << A);
        ll t = sum;
        // cout << i << ": " << hp[i] << ' ' << (used[i] ? "used" : "not used") << ' ' << newHP << endl;
        if (newHP <= atk[i]) {
            continue;
        }
        if (used[i]) {
            // cout << "first" << endl;
            t -= hp[i];
            t += newHP;
        } else if (!used[i] && numUsed < B) {
            // cout << "second" << endl;
            t -= atk[i];
            t += newHP;
        } else if (!used[i] && numUsed >= B) {
            t -= hp[minIdx];
            t += atk[minIdx];
            t -= atk[i];
            t += newHP;
        }
        // cout << t << endl;
        res = max(t, res);
    }
    cout << res << endl;
}
