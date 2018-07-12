#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
typedef pair<int, char> pic;
typedef pair<int, int> pii;
string S;
stack<pic> cur;
vector<pii> ranges;
vector<pii> ranges2;
int prefSum[MAXN];

int main() {
    cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == ')' || S[i] == ']') {
            if (!cur.size())
                continue;
            pic curTop = pic(-1, 0);
            auto t = cur.top();
            if (t.second == '(' && S[i] == ')') {
                curTop = cur.top();
                cur.pop();
            } else if (t.second == '[' && S[i] == ']') {
                curTop = cur.top();
                cur.pop();
            } else {
                while (cur.size() > 0) {
                    cur.pop();
                }
                continue;
            }
            if (curTop.first == -1)
                continue;
            ranges.push_back(pii(curTop.first, i));
        } else {
            cur.push(pic(i, S[i]));
        }
    }
    for (int i = 1; i < S.size(); i++) {
        prefSum[i] = prefSum[i - 1];
        if (S[i - 1] == '[')
            prefSum[i]++;
    }
    sort(ranges.begin(), ranges.end());
    pii curRange = pii(0, -1);
    for (int i = 0; i < ranges.size(); i++) {
        if (ranges[i].first >= curRange.first && ranges[i].second <= curRange.second) {
            continue;
        } else if (ranges[i].first == curRange.second + 1) {
            curRange = pii(curRange.first, ranges[i].second);
        } else {
            curRange = ranges[i];
        }
        ranges2.push_back(curRange);
    }

    int mxCount = 0;
    pii mxRange = pii(0, -1);
    for (auto i : ranges2) {
        int curCount = prefSum[i.second] - prefSum[i.first];
        if (curCount > mxCount) {
            mxCount = curCount;
            mxRange = i;
        }
    }
    cout << mxCount << endl;
    cout << S.substr(mxRange.first, mxRange.second - mxRange.first + 1) << endl;
}