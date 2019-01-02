#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
int N, M;
vector<pii> A;
vector<pii> B;

bool isPossible[10];
int matches(pii i, pii j) {
    int matches = 0;
    int matchVal = 0;
    if (i.first == j.first) {
        matches++;
        matchVal = i.first;
    } else if (i.first == j.second) {
        matches++;
        matchVal = i.first;
    }
    if (i.second == j.first) {
        matches++;
        matchVal = i.second;
    } else if (i.second == j.second) {
        matches++;
        matchVal = i.second;
    }
    if (matches == 1) {
        return matchVal;
    } else {
        return -1;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        A.push_back({min(a, b), max(a, b)});
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        B.push_back({min(a, b), max(a, b)});
    }
    fill(isPossible, isPossible + 10, false);
    for (auto i : A) {
        for (auto j : B) {
            int res = matches(i, j);
            if (res != -1) {
                isPossible[res] = true;
            }
        }
    }
    int cnt = -1;
    for (int i = 1; i < 10; i++) {
        if (isPossible[i] && cnt != -1) {
            cnt = -1;
            break;
        } else if (isPossible[i]) {
            cnt = i;
        }
    }
    if (cnt != -1) {
        cout << cnt << endl;
        return 0;
    }
    bool Aknows = false;
    bool Bknows = false;
    for (auto i : A) {
        fill(isPossible, isPossible + 10, false);
        for (auto j : B) {
            int matchVal = matches(i, j);
            if (matchVal != -1) {
                isPossible[matchVal] = true;
            }
        }
        int cnt = 0;
        for (int i = 1; i < 10; i++) {
            if (isPossible[i]) {
                cnt++;
            }
        }
        if (cnt == 1) {
            Aknows = true;
        } else if (cnt >= 1) {
            Aknows = false;
            break;
        }
    }
    for (auto i : B) {
        fill(isPossible, isPossible + 10, false);
        for (auto j : A) {
            int matchVal = matches(i, j);
            if (matchVal != -1) {
                isPossible[matchVal] = true;
            }
        }
        int cnt = 0;
        for (int i = 1; i < 10; i++) {
            if (isPossible[i]) {
                cnt++;
            }
        }
        if (cnt == 1) {
            Bknows = true;
        } else if (cnt >= 1) {
            Bknows = false;
            break;
        }
    }
    if (Aknows && Bknows) {
        cout << 0 << endl;
        return 0;
    }
    cout << -1 << endl;
}