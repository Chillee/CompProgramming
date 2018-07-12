#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
int N;
int seg[2 * MAXN];

void build() {
    for (int i = N - 1; i > 0; --i)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void modify(int p, int value) {
    for (seg[p += N] = value; p > 1; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

int query(int l, int r) {
    int res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}

int A[MAXN];
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i]--;
    }
    int inversions = 0;
    for (int i = 0; i < N; i++) {
        int t = query(0, A[i]);
        modify(A[i], 1);
        inversions += A[i] - t;
    }
    if (N % 2 == 1) {
        if (inversions % 2 == 0) {
            cout << "Um_nik" << endl;
        } else {
            cout << "Petr" << endl;
        }
    } else {
        if (inversions % 2 == 0) {
            cout << "Petr" << endl;
        } else {
            cout << "Um_nik" << endl;
        }
    }
}