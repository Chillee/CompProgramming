#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

const int MAXN = 1e5 + 5;
int N;
double seg[2 * MAXN];
void build() {
    for (int i = N - 1; i >= 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void modify(int p, double val) {
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

double query(int l, int r) {
    double res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        double t;
        cin >> t;
        seg[i + N] = log2(t);
    }
    build();
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int t, a;
        cin >> t >> a;
        if (t == 1) {
            double b;
            cin >> b;
            a--;
            modify(a, log2(b));
        } else {
            a--;
            int b;
            cin >> b;
            double ans = query(a, b);
            if (ans >= 100) {
                cout << "INFINITE!" << endl;
            } else {
                cout << fixed << setprecision(20) << pow(2.0, ans) << endl;
            }
        }
    }
}