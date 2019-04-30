#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

const ll MAXN=1e5+5;
ll N;
ll cnt[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    for (ll i=0; i<N; i++) cin>>cnt[i];
    ll ans =1e10, idx=-1;
    for (ll i=0; i<N; i++) {
        ll curPos = (cnt[i]) % N;
        ll dist = (curPos <= i ? i - curPos : i-curPos+N);
        if (cnt[i] + dist < ans) {
            idx = i, ans = cnt[i]+dist;
        }
    }
    cout<<idx+1<<endl;
}