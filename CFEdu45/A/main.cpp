#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N, M, A, B;
int main() {
    cin >> N >> M >> A >> B;
    ll ans1 = abs((N / M) * M - N) * B;
    ll ans2 = abs(((N + M - 1) / M) * M - N) * A;
    cout << min(ans1, ans2) << endl;
}