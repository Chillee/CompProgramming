#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
string S;
vector<int> l, r;
void binSearch(ll idx) {
    if (idx == S.size())
        return;

    if (S[idx] == 'l') {
        r.push_back(idx);
        binSearch(idx + 1);
        return;
    } else {
        l.push_back(idx);
        binSearch(idx + 1);
        return;
    }
}
int ans[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    binSearch(0);
    // for (auto i : l) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    // for (auto i : r) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    // return 0;
    for (auto i : l) {
        cout << i + 1 << '\n';
    }
    // return 0;
    reverse(r.begin(), r.end());
    for (auto i : r) {
        cout << i + 1 << '\n';
    }
}