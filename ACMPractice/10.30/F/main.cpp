#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
int seg[28][2 * MAXN];
void build(int ul) {
    for (int i = 1e6 - 1; i >= 0; i--)
        seg[ul][i] = seg[ul][i << 1] + seg[ul][i << 1 | 1];
}

void modify(int p, int val, int ul) {
    for (seg[ul][p += 1e6] = val; p > 0; p >>= 1)
        seg[ul][p >> 1] = seg[ul][p] + seg[ul][p ^ 1];
}

int query(int l, int r, int ul) {
    int res = 0;
    for (l += 1e6, r += 1e6; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[ul][l++];
        if (r & 1)
            res += seg[ul][--r];
    }
    return res;
}
array<int, 6> getDigits(int x) {
    array<int, 6> res;
    for (int i = 0; i < 6; i++) {
        res[i] = x % 10;
        x /= 10;
    }
    reverse(begin(res), end(res));
    return res;
}
int N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 10; b++) {
            for (int c = 0; c < 10; c++) {
                for (int d = 0; d < 10; d++) {
                    for (int e = 0; e < 10; e++) {
                        for (int f = 0; f < 10; f++) {
                            int ul = abs(a + b + c - d - e - f);
                            modify(1e5 * a + 1e4 * b + 1e3 * c + 1e2 * d + 1e1 * e + f, 1, ul);
                        }
                    }
                }
            }
        }
    }
    cin >> N;
    for (int i = 0; i < N; i++) {
        int q, cnt = 0;
        cin >> q;
        auto t = getDigits(q);
        int ul = abs(t[0] + t[1] + t[2] - t[3] - t[4] - t[5]);
        // cout << ul << endl;
        for (int j = 0; j < ul; j++) {
            // cout << q << ' ' <<  << endl;
            cnt += query(0, q, j);
            // cout << j << ": " << query(0, q, ul) << endl;
        }
        cout << cnt << endl;
    }
}