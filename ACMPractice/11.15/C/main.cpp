#include <bits/stdc++.h>

using namespace std;

map<string, int> mapping = {{"yellow", 2}, {"green", 3}, {"brown", 4}, {"blue", 5}, {"pink", 6}, {"black", 7}};
int N, numRed;
vector<int> vals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        if (s == "red") {
            numRed++;
        } else {
            vals.push_back(mapping[s]);
        }
    }
    sort(vals.begin(), vals.end(), greater<int>());
    int ans = 0;
    for (auto i : vals) {
        while (numRed > 0) {
            ans += i;
            ans += 1;
            numRed--;
        }
        ans += i;
    }
    ans += (numRed > 0);
    cout << ans << endl;
}