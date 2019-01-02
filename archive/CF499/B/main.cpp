#include <bits/stdc++.h>

using namespace std;

int N, M;
int cnt[105];
priority_queue<int> cur;
bool f(int x) {
    while (cur.size()) {
        cur.pop();
    }
    for (int i = 0; i < 100; i++) {
        cur.push(cnt[i]);
    }
    for (int i = 0; i < N; i++) {
        int t = cur.top();
        cur.pop();
        if (t < x)
            return false;
        t -= x;
        cur.push(t);
    }
    return true;
}
int binSearch(int l, int r) {
    if (l == r - 1)
        return l;
    int mid = (l + r) / 2;
    if (f(mid)) {
        return binSearch(mid, r);
    } else {
        return binSearch(l, mid);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int t;
        cin >> t;
        t--;
        cnt[t]++;
    }
    cout << binSearch(0, 1000) << endl;
}