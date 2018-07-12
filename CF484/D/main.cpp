#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
int A[MAXN];
int origA[MAXN];

typedef pair<int, int> pii;
set<pii> intervals;
int counts[MAXN];
map<int, int> compToIdx;
map<int, int> origToComp;

pii insert(pii x) {
    counts[x.second - x.first + 1]++;
    intervals.insert(x);
    return x;
}

pii erase(pii x) {
    counts[x.second - x.first + 1]--;
    intervals.erase(x);
    return x;
}

int main() {
    cin >> N;
    vector<pii> compression;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        origA[i] = A[i];
        compression.push_back({A[i], i});
    }
    sort(compression.begin(), compression.end());
    for (int i = 0; i < N; i++) {
        origToComp[compression[i].first] = i;
        compToIdx[i] = compression[i].second;
    }
    for (int i = 0; i < N; i++) {
        A[i] = origToComp[A[i]];
    }
    pii resInt;
    int mxInts = -1;
    int mxIdx = -1;
    for (int i = 0; i < N; i++) {
        int pos = compToIdx[i];
        auto lower = intervals.lower_bound({pos, pos});
        if (lower != intervals.begin())
            lower--;
        auto upper = intervals.upper_bound({pos, pos});
        if (lower == intervals.end()) {
            auto upper = intervals.begin();
            if (intervals.size() > 0 && upper->first == pos + 1) {
                auto t = *upper;
                resInt = insert({pos, upper->second});
                erase(t);
            } else {
                insert({pos, pos});
            }
        } else if (upper == intervals.end()) {
            auto lower = intervals.rbegin();
            if (intervals.size() > 0 && lower->second == pos - 1) {
                auto t = *lower;
                resInt = insert({lower->first, pos});
                erase(t);
            } else {
                insert({pos, pos});
            }
        } else {
            if (lower->second + 1 == pos && upper->first - 1 == pos) {
                auto lt = *lower;
                auto ut = *upper;
                resInt = insert({lower->first, upper->second});
                erase(lt);
                erase(ut);
            } else if (lower->second + 1 == pos) {
                auto t = *lower;
                resInt = insert({lower->first, pos});
                erase(t);
            } else if (upper->first - 1 == pos) {
                auto t = *upper;
                resInt = insert({pos, upper->second});
                erase(t);
            } else {
                resInt = insert({pos, pos});
            }
        }
        int width = resInt.second - resInt.first + 1;
        if (counts[width] == intervals.size()) {
            if (counts[width] > mxInts) {
                mxInts = counts[width];
                mxIdx = i;
            }
        }
    }
    cout << origA[compression[mxIdx].second] + 1 << endl;
}