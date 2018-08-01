#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 1e6 + 5;
int N;
bool used[MAXN];
vector<pii> res;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 3; i <= N / 2; i++) {
        if (used[i] || i % 2 == 0)
            continue;
        vector<int> possible;
        for (int j = i; j <= N; j += i) {
            if (!used[j])
                possible.push_back(j);
        }
        for (int j = 2; j + 1 < possible.size(); j += 2) {
            res.push_back({possible[j], possible[j + 1]});
            used[possible[j]] = true;
            used[possible[j + 1]] = true;
        }
        if (possible.size() % 2 == 0) {
            res.push_back({possible[0], possible[1]});
            used[possible[0]] = true;
            used[possible[1]] = true;
        } else {
            res.push_back({possible[0], *possible.rbegin()});
            used[possible[0]] = true;
            used[*possible.rbegin()] = true;
        }
    }
    vector<int> possible;
    for (int i = 2; i <= N; i += 2) {
        if (!used[i])
            possible.push_back(i);
    }
    for (int j = 0; j + 1 < possible.size(); j += 2) {
        res.push_back({possible[j], possible[j + 1]});
    }
    cout << res.size() << endl;
    for (auto i : res) {
        cout << i.first << ' ' << i.second << endl;
    }
}