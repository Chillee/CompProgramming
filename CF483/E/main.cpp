#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int N;
int A[MAXN];
int B[MAXN];
vector<int> employees[9];

int cnt = 0;
struct state {
    int elevPos;
    int numEntered;
    multiset<int> inside;
    int depth;
    state(int elevPos, int numEntered, multiset<int> curInside, int depth)
        : elevPos(elevPos), numEntered(numEntered), inside(curInside), depth(depth) {}
    bool operator<(const state &x) const {
        if (elevPos != x.elevPos) {
            return elevPos < x.elevPos;
        }
        if (numEntered != x.numEntered) {
            return numEntered < x.numEntered;
        }
        return inside < x.inside;
    }
};
set<state> vis;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
        employees[A[i]].push_back(i);
    }
    queue<state> curQ;
    curQ.push(state(0, 0, multiset<int>{-1, -1, -1, -1}, 0));
    int res = 0;
    while (!curQ.empty()) {
        state cur = curQ.front();
        curQ.pop();
        if (cur.numEntered == N && *max_element(cur.inside.begin(), cur.inside.end()) == -1) {
            res = cur.depth;
            break;
        }
        if (vis.count(cur) != 0) {
            continue;
        }
        vis.insert(cur);
        cur.depth++;
        int cnt = 0;
        auto find = cur.inside.find(cur.elevPos);
        if (find != cur.inside.end()) {
            int orig = *find;
            cur.inside.erase(find);
            cur.inside.insert(-1);
            curQ.push(state(cur.elevPos, cur.numEntered, cur.inside, cur.depth));
            cur.inside.insert(orig);
            cur.inside.erase(-1);
        }
        if (cur.elevPos > 0) {
            cur.elevPos--;
            curQ.push(cur);
            cur.elevPos++;
        }
        if (cur.elevPos < 8) {
            cur.elevPos++;
            curQ.push(cur);
            cur.elevPos--;
        }
        auto emptySpace = cur.inside.find(-1);
        if (emptySpace != cur.inside.end()) {
            auto lb = lower_bound(employees[cur.elevPos].begin(), employees[cur.elevPos].end(), cur.numEntered);
            if (lb != employees[cur.elevPos].end() && *lb == cur.numEntered) {
                cur.numEntered++;
                cur.inside.erase(emptySpace);
                cur.inside.insert(B[*lb]);
                curQ.push(cur);
            }
        }
    }
    cout << res << endl;
}