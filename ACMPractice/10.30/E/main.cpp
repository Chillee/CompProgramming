#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;
int N, M;
int A[MAXN];
set<array<int, 3>> regions;
vector<int> lColor[MAXN], rColor[MAXN];
int lidx[MAXN], ridx[MAXN];
array<int, 3> merge(array<int, 3> over, array<int, 3> under) { return {over[0], under[1], over[2]}; }
auto query(int x) {
    array<int, 3> val = {x, MAXN, MAXN};
    auto res = regions.lower_bound(val);
    res--;
    return res;
}
set<int> vals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        vals.insert(A[i]);
    }
    for (int i = 0; i < N; i++) {
        rColor[A[i]].push_back(i);
    }
    for (int i = N - 1; i >= 0; i--) {
        lColor[A[i]].push_back(i);
    }
    for (auto i : vals) {
        reverse(lColor[i].begin(), lColor[i].end());
        reverse(rColor[i].begin(), rColor[i].end());
    }
    int lft = 0;
    int curColor = A[0];
    for (int i = 0; i < N; i++) {
        if (curColor != A[i]) {
            regions.insert({lft, i - 1, A[i - 1]});
            lft = i;
            curColor = A[i];
        }
    }
    regions.insert({lft, N - 1, A[N - 1]});
    cin >> M;
    for (int i = 0; i < M; i++) {
        int color;
        cin >> color;
        set<array<int, 3>>::iterator lft, rght;
        while (lColor[color].size() > lidx[color]) {
            lft = query(lColor[color][lidx[color]]);
            if ((*lft)[2] == color)
                break;
            lidx[color]++;
        }
        if (lColor[color].size() <= lidx[color])
            continue;
        while (rColor[color].size() > ridx[color]) {
            rght = query(rColor[color][ridx[color]]);
            if ((*rght)[2] == color)
                break;
            ridx[color]++;
        }
        if (rColor[color].size() <= ridx[color])
            continue;
        if (lft == rght)
            continue;
        auto lp = *lft;
        auto rp = *rght;
        while (lft != rght) {
            lft = regions.erase(lft);
        }
        regions.erase(rght);
        regions.insert({lp[0], rp[1], lp[2]});
    }
    for (auto i : regions) {
        for (int j = i[0]; j <= i[1]; j++) {
            cout << i[2] << ' ';
        }
    }
    cout << endl;
}