#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll R, G, B;
vector<ll> vals;
int main() {
    cin >> R >> G >> B;
    vals.push_back(R);
    vals.push_back(G);
    vals.push_back(B);
    sort(vals.begin(), vals.end(), greater<ll>());
    vals[0] = min(vals[0], (vals[1] + vals[2]) * 2);
    cout << (vals[0] + vals[1] + vals[2]) / 3 << endl;
}