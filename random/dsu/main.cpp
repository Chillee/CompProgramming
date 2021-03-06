#include <bits/stdc++.h>

using namespace std;

int par[100];
int root(int v) { return par[v] < 0 ? v : (par[v] = root(par[v])); }
void merge(int x, int y) {
    if ((x = root(x)) == (y = root(y)))
        return;
    if (par[y] < par[x])
        swap(x, y);
    par[x] += par[y];
    par[y] = x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(par, par + 100, -1);
    merge(0, 1);
    merge(0, 2);
    merge(1, 3);
    for (int i = 0; i < 4; i++) {
        cout << par[i] << ' ';
    }
    cout << endl;
}