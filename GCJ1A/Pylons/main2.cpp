#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

vector<array<int, 2>> genEven(int C, int lowR) { // R=2, C>=5
    vector<array<int, 2>> ans;
    for (int i = 0; i < C; i++) {
        ans.push_back({lowR, i});
        ans.push_back({lowR + 1, (i + 3) % C});
    }
    return ans;
}
vector<array<int, 2>> genThree(int C, int lowR) { // R=3, C>=4
    vector<array<int, 2>> ans;
    for (int i = 0; i < C; i++) {
        ans.push_back({lowR, i});
        ans.push_back({lowR + 1, (i + 2) % C});
        ans.push_back({lowR + 2, i % C});
    }
    return ans;
}
vector<array<int, 2>> genFourFour() {
    vector<array<int, 2>> ans = {{0, 0}, {1, 2}, {3, 1}, {2, 3}, {3, 0}, {0, 2}, {2, 1}, {3, 3},
                                 {1, 0}, {2, 2}, {0, 3}, {1, 1}, {3, 2}, {1, 3}, {0, 1}, {2, 0}};
    return ans;
}
void pArr(array<int, 2> x) { cout << x[0] << ' ' << x[1] << ' ' << endl; }
bool isValid(array<int, 2> a, array<int, 2> b) { return (a[0] != b[0] && a[1] != b[1] && a[0] + a[1] != b[0] + b[1] && a[0] - a[1] != b[0] - b[1]); }
bool impossible(int r, int c) {
    if (r > c)
        swap(r, c);
    return (r <= 3 && c <= 3) || (r == 1) || (c == 1) || (r == 2 && c == 4);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    int success = 0, failed = 0;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int R, C;
        int origR, origC;
        cin >> R >> C;
        origR = R, origC = C;
        if (impossible(R, C)) {
            cout << "Case #" << t + 1 << ": "
                 << "IMPOSSIBLE" << endl;
            success++;
            continue;
        }
        bool swapped = false;
        if (R % 2 == 1 && C % 2 == 0) {
            swap(R, C);
            swapped = true;
        } else if (R % 2 == 0 && C % 2 == 0 && R > C) {
            swap(R, C);
            swapped = true;
        }
        vector<array<int, 2>> ans;
        if (min(R, C) == 3 && max(R, C) >= 4) {
            if (R > C) {
                swap(R, C);
                swapped = !swapped;
            }
            ans = genThree(C, 0);
        } else if (R == 4 && C == 4) {
            ans = genFourFour();
        } else {
            int i = 0;
            if (R % 2 == 1) {
                auto c = genThree(C, i);
                for (auto j : c)
                    ans.push_back(j);
                i += 3;
            }
            for (; i < R; i += 2) {
                auto c = genEven(C, i);
                for (auto j : c)
                    ans.push_back(j);
            }
        }
        if (swapped) {
            for (auto &i : ans) {
                swap(i[0], i[1]);
            }
        }
        if (ans.size() != R * C) {
            cout << R << ' ' << C << ' ' << R * C << ' ' << ans.size() << endl;
            assert(false);
        }
        assert(ans.size() == R * C);
        for (int i = 1; i < ans.size(); i++) {
            // cout << "f:";
            // pArr(ans[i - 1]);
            // cout << "s: ";
            // pArr(ans[i]);
            assert(ans[i][0] >= 0 && ans[i][0] < origR);
            assert(ans[i][1] >= 0 && ans[i][1] < origC);
            if (!isValid(ans[i - 1], ans[i])) {
                cout << R << ' ' << C << endl;
                assert(false);
            }
        }
        success++;
        cout << "Case #" << t + 1 << ": "
             << "POSSIBLE" << endl;
        for (auto i : ans) {
            cout << i[0] + 1 << ' ' << i[1] + 1 << endl;
        }
    }
    // cout << success << ' ' << failed << ' ' << success + failed << endl;
}