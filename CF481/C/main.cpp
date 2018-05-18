#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, M;
vector<ll> A;
vector<ll> sum;
int main() {
    cin >> N >> M;
    for (ll i = 0; i < N; i++) {
        ll t;
        cin >> t;
        A.push_back(t);
    }
    ll curRoom = 0;
    ll curIdx = 0;
    for (ll i = 0; i < M; i++) {
        ll b;
        cin >> b;
        while (b > curRoom + A[curIdx]) {
            curRoom += A[curIdx];
            curIdx++;
        }
        cout << curIdx + 1 << ' ' << b - curRoom << endl;
    }
}
