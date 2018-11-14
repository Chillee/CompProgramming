#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

string A, B, C;
int N;
vector<int> differ;
array<pair<int, char>, 3> ans;
int search(int idx, array<int, 3> used, array<pair<int, char>, 3> changed) {
    if (used[0] > 1 || used[1] > 1 || used[2] > 1)
        return 0;
    if (idx == differ.size()) {
        ans = changed;
        // cout << ans[0].first << ' ' << ans[0].second << endl;
        // cout << ans[1].first << ' ' << ans[1].second << endl;
        // cout << ans[2].first << ' ' << ans[2].second << endl;
        // cout << endl;
        return 1;
    }
    if (used[0] > 0 && used[1] > 0 && used[2] > 0)
        return 0;
    int ans = 0;
    int cur = differ[idx];
    if (A[cur] != B[cur] && A[cur] != C[cur] && B[cur] != C[cur]) {
        ans += search(idx + 1, {used[0] + 1, used[1] + 1, used[2]}, {make_pair(differ[idx], C[cur]), make_pair(differ[idx], C[cur]), changed[2]});
        ans += search(idx + 1, {used[0], used[1] + 1, used[2] + 1}, {changed[0], make_pair(differ[idx], A[cur]), make_pair(differ[idx], A[cur])});
        ans += search(idx + 1, {used[0] + 1, used[1], used[2] + 1}, {make_pair(differ[idx], B[cur]), changed[1], make_pair(differ[idx], B[cur])});
    } else if (A[cur] == B[cur] && A[cur] != C[cur]) {
        ans += search(idx + 1, {used[0] + 1, used[1] + 1, used[2]}, {make_pair(differ[idx], C[cur]), make_pair(differ[idx], C[cur]), changed[2]});
        ans += search(idx + 1, {used[0], used[1], used[2] + 1}, {changed[0], changed[1], make_pair(differ[idx], A[cur])});
    } else if (A[cur] != B[cur] && B[cur] == C[cur]) {
        ans += search(idx + 1, {used[0], used[1] + 1, used[2] + 1}, {changed[0], make_pair(differ[idx], A[cur]), make_pair(differ[idx], A[cur])});
        ans += search(idx + 1, {used[0] + 1, used[1], used[2]}, {make_pair(differ[idx], B[cur]), changed[1], changed[2]});
    } else if (A[cur] == C[cur] && B[cur] != C[cur]) {
        ans += search(idx + 1, {used[0] + 1, used[1], used[2] + 1}, {make_pair(differ[idx], B[cur]), changed[1], make_pair(differ[idx], B[cur])});
        ans += search(idx + 1, {used[0], used[1] + 1, used[2]}, {changed[0], make_pair(differ[idx], A[cur]), changed[2]});
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> A >> B >> C;
    N = A.size();
    for (int i = 0; i < N; i++) {
        if (A[i] != B[i] || B[i] != C[i] || A[i] != C[i]) {
            differ.push_back(i);
        }
    }
    if (differ.size() > 3) {
        cout << "Impossible" << endl;
        return 0;
    } else if (differ.size() == 0) {
        cout << "Ambiguous" << endl;
        return 0;
    }
    array<pair<int, char>, 3> t = {make_pair(-1, 'a'), make_pair(-1, 'a'), make_pair(-1, 'a')};
    int res = search(0, {0, 0, 0}, t);
    // cout<<A<<endl;
    if (res > 1) {
        // A[ans[0].first] = ans[0].second;
        // B[ans[1].first] = ans[1].second;
        // C[ans[2].first] = ans[2].second;
        cout << "Ambiguous" << endl;
        return 0;
    } else if (res == 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    // cout << "HUH" << endl;
    if (ans[0].first != -1)
        A[ans[0].first] = ans[0].second;
    if (ans[1].first != -1)
        B[ans[1].first] = ans[1].second;
    if (ans[2].first != -1)
        C[ans[2].first] = ans[2].second;
    cout << A << endl;
}