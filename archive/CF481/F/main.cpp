#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
typedef pair<int, int> pii;

int N, K;
int R[MAXN];
vector<pii> skills;
int ans[MAXN];

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> R[i];
        skills.push_back(pii(R[i], i));
    }
    sort(skills.begin(), skills.end());
    int curIdx = 1;
    int cur = 0;
    while (curIdx < N) {
        while (skills[curIdx].first == skills[curIdx - 1].first && curIdx < N) {
            ans[skills[curIdx].second] = cur;
            curIdx++;
        }
        if (curIdx == N) {
            break;
        }
        cur = curIdx;
        ans[skills[curIdx].second] = cur;
        curIdx++;
    }
    int cnt = 0;
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (R[x] > R[y]) {
            ans[x]--;
        } else if (R[y] > R[x]) {
            ans[y]--;
        }
    }
    for (int i = 0; i < N; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}