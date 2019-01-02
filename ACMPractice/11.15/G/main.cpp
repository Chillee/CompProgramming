#include <bits/stdc++.h>

using namespace std;

void printArr(array<int, 3> x) { cout << '(' << x[0] << ' ' << x[1] << ' ' << x[2] << ')'; }
bool isOdd(array<int, 3> x) { return (x[0] + x[1] + x[2]) & 1; }
array<int, 3> findClose(array<int, 3> cur, array<int, 3> neq) {
    cur[0]--;
    if (cur == neq) {
        cur[0] += 2;
    }
    return cur;
}
vector<array<int, 2>> findMove(array<int, 3> rob, array<int, 3> nend) {
    vector<array<int, 2>> diffs = {{abs(rob[0] - nend[0]), 0}, {abs(rob[1] - nend[1]), 1}, {abs(rob[2] - nend[2]), 2}};
    sort(diffs.begin(), diffs.end(), greater<array<int, 2>>());
    vector<array<int, 2>> res;
    for (int i = 0; i < 2; i++) {
        int idx = diffs[i][1];
        res.push_back({idx, nend[idx] - rob[idx] > 0 ? 1 : -1});
    }
    return res;
}
bool hasCollision(array<int, 3> rob1, array<int, 3> rob2, vector<array<int, 2>> moves1, vector<array<int, 2>> moves2) {
    for (int i = 0; i < moves1.size(); i++) {
        auto m1 = moves1[i];
        auto m2 = moves2[i];
        rob1[m1[0]] += m1[1];
        rob2[m2[0]] += m2[1];
        if (rob1 == rob2) {
            return true;
        }
    }
    return false;
}

array<int, 3> robe, robo;
array<int, 3> ende, endo;
array<int, 3> nende, nendo;
vector<array<int, 3>> pose, poso;
void updatePos() {
    pose.push_back(robe);
    poso.push_back(robo);
    // printArr(robe);
    // cout << ' ';
    // printArr(robo);
    // cout << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x0, y0, z0, xi, yi, zi;
    cin >> x0 >> y0 >> z0 >> xi >> yi >> zi;
    robe = {x0, y0, z0};
    ende = {xi, yi, zi};
    cin >> x0 >> y0 >> z0 >> xi >> yi >> zi;
    robo = {x0, y0, z0};
    endo = {xi, yi, zi};
    nende = ende;
    nendo = endo;
    updatePos();
    if (!isOdd(robo)) {
        robo = findClose(robo, robe);
    }
    if (isOdd(robe)) {
        robe = findClose(robe, robo);
    }
    if (!isOdd(nendo)) {
        nendo = findClose(nendo, nende);
    }
    if (isOdd(nende)) {
        nende = findClose(nende, nendo);
    }
    updatePos();
    // cout << "DONE" << endl;
    // cout << endl;
    while (robe != nende || robo != nendo) {
        vector<array<int, 2>> movese, moveso;
        for (int i = 0; i < 2; i++) {
            movese.push_back({0, 0});
            moveso.push_back({0, 0});
        }
        if (robe != nende) {
            auto moves = findMove(robe, nende);
            movese = moves;
        }
        if (robo != nendo) {
            auto moves = findMove(robo, nendo);
            moveso = moves;
        }
        if (hasCollision(robe, robo, movese, moveso)) {
            reverse(movese.begin(), movese.end());
        }
        if (hasCollision(robe, robo, movese, moveso)) {
            reverse(moveso.begin(), moveso.end());
        }
        for (int i = 0; i < movese.size(); i++) {
            auto me = movese.at(i), mo = moveso.at(i);
            robe[me[0]] += me[1];
            robo[mo[0]] += mo[1];
            updatePos();
        }
        // cout << endl;
    }
    robe = ende, robo = endo;
    updatePos();
    // return 0;
    // cout << pose.size() << endl;
    // return 0;
    for (int i = 0; i < pose.size(); i++) {
        printArr(pose[i]);
        cout << ' ';
        printArr(poso[i]);
        cout << endl;
    }
}
