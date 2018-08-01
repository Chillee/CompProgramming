#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
int N;
string nodeType[MAXN];
bool initVals[MAXN];
vector<int> children[MAXN];
int ans[MAXN];
bool finalResult;
bool calcInit(int cur) {
    vector<int> res;
    for (auto i : children[cur]) {
        res.push_back(calcInit(i));
    }
    bool returnVal = false;
    if (nodeType[cur] == "IN") {
        returnVal = initVals[cur];
    } else if (nodeType[cur] == "NOT") {
        returnVal = !res[0];
    } else if (nodeType[cur] == "AND") {
        returnVal = res[0] && res[1];
    } else if (nodeType[cur] == "OR") {
        returnVal = res[0] || res[1];
    } else if (nodeType[cur] == "XOR") {
        returnVal = res[0] ^ res[1];
    }
    initVals[cur] = returnVal;
    return initVals[cur];
}

void calcResult(int cur, bool matters) {
    if (nodeType[cur] == "IN") {
        if (matters) {
            ans[cur] = !finalResult;
        } else {
            ans[cur] = finalResult;
        }
        return;
    }
    if (!matters) {
        for (auto i : children[cur]) {
            calcResult(i, false);
        }
        return;
    }
    vector<pair<int, int>> res;
    for (auto i : children[cur]) {
        res.push_back({initVals[i], i});
    }
    if (nodeType[cur] == "AND") {
        calcResult(res[0].second, (!res[0].first && res[1].first) != initVals[cur]);
        calcResult(res[1].second, (res[0].first && !res[1].first) != initVals[cur]);
    } else if (nodeType[cur] == "OR") {
        calcResult(res[0].second, (!res[0].first || res[1].first) != initVals[cur]);
        calcResult(res[1].second, (res[0].first || !res[1].first) != initVals[cur]);
    } else if (nodeType[cur] == "XOR") {
        calcResult(res[0].second, (!res[0].first ^ res[1].first) != initVals[cur]);
        calcResult(res[1].second, (res[0].first ^ !res[1].first) != initVals[cur]);
    } else if (nodeType[cur] == "NOT") {
        calcResult(res[0].second, (res[0].first) != initVals[cur]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t;
        nodeType[i] = t;
        if (t == "IN") {
            int val;
            cin >> val;
            initVals[i] = val;
        } else if (t == "NOT") {
            int b;
            cin >> b;
            b--;
            children[i].push_back(b);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            children[i].push_back(l);
            children[i].push_back(r);
        }
    }
    calcInit(0);
    finalResult = initVals[0];
    calcResult(0, true);
    for (int i = 0; i < N; i++) {
        if (nodeType[i] == "IN") {
            cout << ans[i];
        }
    }
    cout << endl;
}