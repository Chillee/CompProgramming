#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
vector<pii> recs;
int N;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        recs.push_back({min(a, b), max(a, b)});
    }
    reverse(recs.begin(), recs.end());
    swap(recs[N - 1].first, recs[N - 1].second);
    for (int i = 1; i < N - 1; i++) {
        if (recs[i - 1].first < recs[i].first && recs[i].first < recs[i + 1].first) {
            continue;
        } else if (recs[i - 1].first > recs[i].first) {
            swap(recs[i].first, recs[i].second);
        }
    }
    for (int i = 1; i < N; i++) {
        if (recs[i].first < recs[i - 1].first) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}