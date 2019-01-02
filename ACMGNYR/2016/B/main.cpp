#include <bits/stdc++.h>

using namespace std;

int P, K;
string S;
map<char, char> mapping = {{'B', '8'}, {'G', 'C'}, {'I', '1'}, {'O', '0'}, {'Q', '0'}, {'S', '5'}, {'U', 'V'}, {'Y', 'V'}, {'Z', '2'}};
string baseVal = "0123456789ACDEFHJKLMNPRTVWX";
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int i = 0; i < P; i++) {
        cin >> K >> S;
        vector<int> res;
        for (auto &i : S) {
            if (mapping.count(i)) {
                i = mapping[i];
            }
            if (i >= '0' && i <= '9') {
                res.push_back(baseVal.find(i));
            } else {
                res.push_back(baseVal.find(i));
            }
        }
        int ans = 2 * res[0] + 4 * res[1] + 5 * res[2] + 7 * res[3] + 8 * res[4] + 10 * res[5] + 11 * res[6] + 13 * res[7];
        ans %= 27;
        if (ans != res[8]) {
            cout << K << ' ' << "Invalid" << endl;
        } else {
            // cout << S << endl;
            long long ans = 0;
            for (int i = 0; i < 8; i++) {
                ans = ans * 27 + baseVal.find(S[i]);
            }
            cout << K << ' ' << ans << endl;
        }
    }
}