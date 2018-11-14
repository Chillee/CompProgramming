#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll T, A, B;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> A >> B;
        ll res = A * B;
        vector<string> ans;
        ll pw = 0;
        while (res != 0) {
            if (res % 10 != 0) {
                if (ans.size() != 0) {
                    ans.push_back(" + ");
                }
                ans.push_back(to_string(res % 10));
                if (pw == 0) {
                    ans.push_back(" x 1");
                } else if (pw < 9) {
                    for (ll i = 0; i < pw; i++) {
                        ans.push_back("0");
                    }
                    ans.push_back(" x 1");
                } else if (pw == 18 && abs(res) == 1) {
                    for (ll i = 0; i < 9; i++) {
                        ans.push_back("0");
                    }
                    ans.push_back(" x 1");
                    for (ll i = 9; i < pw; i++) {
                        ans.push_back("0");
                    }
                } else if (pw >= 9) {
                    for (ll i = 0; i < 8; i++) {
                        ans.push_back("0");
                    }
                    ans.push_back(" x 1");
                    for (ll i = 8; i < pw; i++) {
                        ans.push_back("0");
                    }
                }
            }
            res /= 10;
            pw++;
        }
        for (auto i : ans) {
            cout << i;
        }
        cout << endl;
    }
}