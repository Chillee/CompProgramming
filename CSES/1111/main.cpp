#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

array<vector<int>, 2> manacher(string &s) { // (even, odd)
    int n = s.size();
    array<vector<int>, 2> p = {vector<int>(n), vector<int>(n)};
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0)
        for (int i = 0; i < n; i++) {
            if (i < r)
                p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    return p;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string S;
    cin >> S;
    auto res = manacher(S);
    int eans = 0;
    for (int i = 0; i < res[0].size(); i++)
        if (res[0][i] > res[0][eans])
            eans = i;

    int oans = 0;
    for (int i = 0; i < res[1].size(); i++)
        if (res[1][i] > res[1][oans])
            oans = i;
    if (eans * 2 > oans * 2 + 1) {
        cout << S.substr(eans - res[0][eans], 2 * res[0][eans]) << endl;
    } else
        cout << S.substr(oans - res[1][oans], res[1][oans] * 2 + 1) << endl;
}