#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;

ull T, W, B;

ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>T>>W>>B;
    ll wbgcd = __gcd(W, B);
    ll wblcm = (B/wbgcd)*W;
    ll numOcc = T/wblcm;
    ll num = numOcc*min(W, B);
    ll mxVal = numOcc*wblcm;
    num += min(T+1 - mxVal, min(W,B));
    ll denom = T;
    num--;
    cout<<num/__gcd(num, denom)<<"/"<<denom/__gcd(num, denom)<<endl;
}