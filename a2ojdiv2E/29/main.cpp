#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
vector<char> S;
string t;
int pref[MAXN];
const int N = 4 * MAXN;
const int OFFSET = 2 * MAXN;
const int INF = 1e9;
int seg[2 * N];
void build() {
    for (int i = N - 1; i >= 0; i--)
        seg[i] = min(seg[i << 1], seg[i << 1 | 1]);
}

void modify(int p, int val) {
    p += (N + OFFSET);
    for (seg[p] = min(seg[p], val); p > 0; p >>= 1)
        seg[p >> 1] = min(seg[p], seg[p ^ 1]);
}

int query(int l, int r) {
    int res = INF;
    for (l += N + OFFSET, r += N + OFFSET; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = min(res, seg[l++]);
        if (r & 1)
            res = min(res, seg[--r]);
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    S.push_back('^');
    for (auto i : t) {
        if (i < 'a') {
            S.push_back((int)i + ('a' - 'A'));
        } else {
            S.push_back(i);
        }
    }
    set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 1; i < S.size(); i++) {
        if (vowels.find(S[i]) != vowels.end()) {
            pref[i] = pref[i - 1] - 1;
        } else {
            pref[i] = pref[i - 1] + 2;
        }
    }
    for (int i = 0; i < N; i++) {
        seg[i + N] = INF;
    }
    build();
    int mxLength = 0;
    int mxCnt = 0;
    for (int i = 0; i < S.size(); i++) {
        int curMin = query(-OFFSET, pref[i] + 1);
        modify(pref[i], i);
        if (i - curMin == mxLength) {
            mxCnt++;
        } else if (i - curMin > mxLength) {
            mxLength = i - curMin;
            mxCnt = 1;
        }
    }
    if (mxLength == 0) {
        cout << "No solution" << endl;
        return 0;
    }

    cout << mxLength << ' ' << mxCnt << endl;
}