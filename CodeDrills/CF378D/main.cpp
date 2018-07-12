#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int N;
vector<int> A, B, C;
map<pii, vector<pii>> hashed;
void addPair(int a, int b, int c, int idx) {
    if (hashed.find(pii(a, b)) == hashed.end()) {
        hashed[pii(a, b)] = {};
    }
    hashed[pii(a, b)].push_back({c, idx});
}
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        A.push_back(a), B.push_back(b), C.push_back(c);
    }
    for (int i = 0; i < N; i++) {
        vector<int> perms = {A[i], B[i], C[i]};
        do {
            addPair(perms[0], perms[1], perms[2], i);
        } while (next_permutation(perms.begin(), perms.end()));
    }
    int result = -1;
    pii resultIdx = {-1, -1};
    for (auto i : hashed) {
        sort(i.second.begin(), i.second.end(), greater<pii>());
        int valOne = i.second[0].first;
        int valTwo = -1;
        int idxTwo = -1;
        for (auto j : i.second) {
            if (j.second != i.second[0].second) {
                valTwo = j.first;
                idxTwo = j.second;
                break;
            }
        }
        if (i.second.size() == 1 || valTwo == -1) {
            int cur = min(i.second[0].first, min(i.first.first, i.first.second));
            if (cur > result) {
                result = cur;
                resultIdx = {i.second[0].second, -1};
            }
        } else {
            int third = valOne + valTwo;
            int cur = max(result, min(third, min(i.first.first, i.first.second)));
            if (cur > result) {
                result = cur;
                resultIdx = {i.second[0].second, idxTwo};
            }
        }
    }
    if (resultIdx.second == -1) {
        cout << 1 << endl;
        cout << resultIdx.first + 1 << endl;
    } else {
        cout << 2 << endl;
        cout << resultIdx.first + 1 << ' ' << resultIdx.second + 1 << endl;
    }
}