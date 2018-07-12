#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 55;
ll T, N, K, V;
string attractions[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 1; t <= T; t++) {
        cin >> N >> K >> V;
        vector<pair<ll, string>> ans;
        for (ll i = 0; i < N; i++) {
            cin >> attractions[i];
        }
        for (ll i = 0; i < K; i++) {
            ll rank = (i + K * (V - 1)) % N;
            ans.push_back({rank, attractions[rank]});
        }
        sort(ans.begin(), ans.end());
        cout << "Case #" << t << ": ";
        for (auto i : ans) {
            cout << i.second << ' ';
        }
        cout << endl;
    }
}