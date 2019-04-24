#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N;
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    vector<int> ans;
    for (int i = 0; i < N; i++) {
        auto it = upper_bound(ans.begin(), ans.end(), A[i]);
        if (it == ans.end())
            ans.push_back(A[i]);
        else
            *it = A[i];
    }
    cout << ans.size() << endl;
}