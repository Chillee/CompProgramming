#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N;
vector<int> A;

map<int, int> cur;

int par[MAXN];
int depth[MAXN];
int mxdfs(int cur) {
    if (depth[cur] != 0) {
        return depth[cur];
    }
    if (par[cur] == -1) {
        return 1;
    }
    depth[cur] = 1 + mxdfs(par[cur]);
    return depth[cur];
}
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        A.push_back(t);
    }
    for (int i = 0; i < N; i++) {
        par[i] = -1;
    }
    for (int i = 0; i < N; i++) {
        cur[A[i]] = i;
        if (cur.count(A[i] - 1) != 0) {
            par[i] = cur[A[i] - 1];
        }
    }
    int res = 0;
    int resIdx = 0;
    for (int i = 0; i < N; i++) {
        int nxt = mxdfs(i);
        if (nxt > res) {
            res = nxt;
            resIdx = i;
        }
    }
    cout << res << endl;
    vector<int> resVec;
    resVec.push_back(resIdx);
    while (par[resIdx] != -1) {
        resIdx = par[resIdx];
        resVec.push_back(resIdx);
    }
    for (int i = resVec.size() - 1; i >= 0; i--) {
        cout << resVec[i] + 1 << ' ';
    }
    cout << endl;
}