#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 2005;
string S;
vector<pii> pals;
int dp1[MAXN];
int dp2[MAXN];

int main() {
    cin >> S;
    for (int i = 0; i < S.size(); i++) {
        pals.push_back({i, i});
        for (int j = 1;; j++) {
            if (i - j < 0 || i + j >= S.size())
                break;
            if (S[i - j] != S[i + j])
                break;
            pals.push_back({i - j, i + j});
        }
        for (int j = 0;; j++) {
            if (i - j < 0 || i + j + 1 >= S.size())
                break;
            if (S[i - j] != S[i + j + 1])
                break;
            pals.push_back({i - j, i + j + 1});
        }
    }
    sort(pals.begin(), pals.end(), [](auto &a, auto &b) { return a.second < b.second; });
    int idx = 0;
    for (int i = 0; i < S.size(); i++) {
        while (pals[idx].second <= i && idx < pals.size())
            idx++;
        dp1[i] = idx;
    }
    sort(pals.begin(), pals.end(), greater<pii>());
    idx = 0;
    for (int i = S.size() - 1; i >= 0; i--) {
        while (pals[idx].first > i && idx < pals.size())
            idx++;
        dp2[i] = idx;
    }
    for (int i = 0; i < S.size(); i++) {
        cout << dp2[i] << " ";
    }
    cout << endl;
    int ans = 0;
    for (int i = 0; i < S.size(); i++) {
        ans += dp1[i] * dp2[i];
    }
    cout << ans << endl;
}