#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXL = 1e5 + 5;
int L, W;

int A[MAXL];
priority_queue<pii, vector<pii>, greater<pii>> cur;
int main() {
    cin >> L >> W;
    for (int i = 1; i < L; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= W; i++) {
        if (A[i] > 0) {
            cur.push({i, A[i]});
        }
    }
    for (int i = W + 1; i < L; i++) {
        if (A[i] == 0) {
            continue;
        }
        // cout << "i: " << i << ' ' << cur.size() << endl;
        int curCnt = A[i];
        while (!cur.empty() && i - cur.top().first > W) {
            cur.pop();
        }
        vector<pair<int, int>> reAdd;
        int total = 0;
        while (curCnt > 0 && !cur.empty()) {
            auto curVal = cur.top();
            // cout << i << ' ' << curVal.first << ' ' << curVal.second << endl;
            cur.pop();
            if (curVal.second > curCnt) {
                reAdd.push_back({curVal.first, curVal.second - curCnt});
                total += curCnt;
            } else {
                total += curVal.second;
            }
            curCnt -= curVal.second;
        }
        for (auto i : reAdd) {
            cur.push(i);
        }
        cur.push({i, total});
    }
    int res = 0;
    while (!cur.empty()) {
        auto i = cur.top();
        res += i.second;
        cur.pop();
    }
    cout << res << endl;
}
