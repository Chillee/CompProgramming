#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> pos;
int main() {
    cin >> N;
    for (int i = 0; i < N / 2; i++) {
        int t;
        cin >> t;
        t--;
        pos.push_back(t);
    }
    sort(pos.begin(), pos.end());
    int ans = 100000;
    int cur = 0;
    for (int i = 0; i < pos.size(); i++) {
        cur += abs(pos[i] - i * 2);
    }
    ans = min(ans, cur);
    cur = 0;
    for (int i = 0; i < pos.size(); i++) {
        cur += abs(pos[i] - (i * 2 + 1));
    }
    ans = min(ans, cur);
    cout << ans << endl;
}