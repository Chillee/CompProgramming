#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> interval;
typedef pair<int, int> endpoint;

const int MAXN = 3 * 1e5;
int N;
vector<interval> intervals;
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        intervals.push_back(interval(a, -b, i));
    }
    sort(intervals.begin(), intervals.end());
    for (int i = 0; i < intervals.size(); i++) {
        intervals[i] = interval(get<0>(intervals[i]), -get<1>(intervals[i]), get<2>(intervals[i]));
    }
    // priority_queue<endpoint, vector<endpoint>, less<endpoint>> curQ;
    priority_queue<endpoint> curQ;
    for (auto i : intervals) {
        while (!curQ.empty() && curQ.top().first < get<0>(i)) {
            curQ.pop();
        }
        if (!curQ.empty() && curQ.top().first >= get<1>(i)) {
            cout << get<2>(i) + 1 << ' ' << curQ.top().second + 1 << endl;
            return 0;
        }
        curQ.push(endpoint(get<1>(i), get<2>(i)));
    }
    cout << "-1 -1" << endl;
}