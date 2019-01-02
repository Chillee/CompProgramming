#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
int A[MAXN], B[MAXN];
int arrvals[MAXN];
int ans[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    A[-5000] = 4;
    map<int, int> val;
    for (int i = 0; i < N; i++) {
        val[A[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        int aidx = val[B[i]];
        arrvals[i] = i - aidx;
    }
    fill(ans, ans + MAXN, 1e9);
    set<int> vals;
    for (int i = 0; i < N; i++) {
        auto cur = vals.lower_bound(-N + i);
        if (cur != vals.end()) {
            ans[i] = min(ans[i], abs(-N + i - *cur));
        }
        if (cur != vals.begin()) {
            cur--;
            ans[i] = min(ans[i], abs(-N + i - *cur));
        }
        vals.insert(arrvals[i]);
    }
    multiset<int> rvals;
    for (int i = 0; i < N; i++) {
        rvals.insert(arrvals[i]);
    }

    for (int i = 0; i < N; i++) {
        auto cur = rvals.lower_bound(i);
        if (cur != rvals.end()) {
            ans[i] = min(ans[i], abs(i - *cur));
        }
        if (cur != rvals.begin()) {
            cur--;
            ans[i] = min(ans[i], abs(i - *cur));
        }
        cur = rvals.find(arrvals[i]);
        rvals.erase(cur);
    }
    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
}
