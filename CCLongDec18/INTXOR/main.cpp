#include <bits/stdc++.h>

using namespace std;

const int MAXB = 5;
int T, N;
int cnt = 0;
int query(int a, int b, int c) {
    cnt++;
    // return (a + 1) ^ (b + 1) ^ (c + 1);
    cout << 1 << ' ' << a + 1 << ' ' << b + 1 << ' ' << c + 1 << endl;
    int t;
    cin >> t;
    return t;
}
const int MAXN = 1e5 + 5;
int A[MAXN];
int a3[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // T = 15;
    cin >> T;
    for (int t = 0; t < T; t++) {
        fill(begin(A), end(A), 0);
        fill(begin(a3), end(a3), 0);
        // N = t + 1;
        cin >> N;
        if (N % 3 == 1 || N % 3 == 2) {
            for (int i = 0; i < N; i++) {
                a3[i] = query(i, (i + 1) % N, (i + 2) % N);
            }
            int total = 0;
            for (int i = 0; i < N; i++)
                total ^= a3[i];
            if (N % 3 == 1) {
                for (int i = 0; i < 3; i++) {
                    int cur = 0;
                    for (int j = 0; j < N - 1; j += 3) {
                        cur ^= a3[(i + j) % N];
                    }
                    A[(i - 1 + N) % N] = total ^ cur;
                    for (int j = 0; j < N - 1; j += 3) {
                        cur ^= a3[(i + N - 1 + j) % N] ^ a3[(i + j) % N];
                        A[(i + 2 + j + N) % N] = total ^ cur;
                    }
                }
            } else if (N % 3 == 2) {
                for (int i = 0; i < 3; i++) {
                    int cur = 0;
                    for (int j = 0; j < N; j += 3) {
                        cur ^= a3[(i + j) % N];
                    }
                    A[(i + N) % N] = total ^ cur;
                    for (int j = 0; j < N; j += 3) {
                        cur ^= a3[(i + j + 1) % N] ^ a3[(i + j) % N];
                        A[(i + j + 3) % N] = total ^ cur;
                    }
                }
            }
        } else if (N % 6 == 0) {
            for (int i = 0; i < N; i += 6) {
                for (int j = 0; j < 6; j++) {
                    a3[i + j] = query(i + j, i + ((j + 2) % 6), i + ((j + 3) % 6));
                }
            }
            for (int i = 0; i < N; i += 6) {
                for (int j = 0; j < 6; j++) {
                    A[i + j] = a3[i + ((j + 2) % 6)] ^ a3[i + ((j + 4) % 6)] ^ a3[i + ((j + 5) % 6)];
                }
            }
        } else if (N % 9 == 0) {
            for (int i = 0; i < N; i += 9) {
                for (int j = 0; j < 9; j++) {
                    a3[i + j] = query(i + j, i + ((j + 1) % 9), i + ((j + 3) % 9));
                }
            }
            for (int i = 0; i < N; i += 9) {
                for (int j = 0; j < 9; j++) {
                    vector<int> offsets = {0, 3, 4, 7, 5};
                    for (auto k : offsets) {
                        A[i + j] ^= a3[i + ((j + k) % 9)];
                    }
                }
            }
        } else if (N % 6 == 3) {
            for (int i = 0; i < N; i++) {
                a3[i] = query(i, (i + 3) % N, (i + 6) % N);
            }
            int curN = N / 3;
            if (curN % 3 == 1) {
                for (int k = 0; k < 3; k++) {
                    int total = 0;
                    for (int i = 0; i < curN; i++) {
                        total ^= a3[i * 3 + k];
                    }
                    for (int i = 0; i < 3; i++) {
                        int cur = 0;
                        for (int j = 0; j < curN - 1; j += 3) {
                            cur ^= a3[((i + j) % curN) * 3 + k];
                        }
                        A[((i - 1 + curN) % curN) * 3 + k] = total ^ cur;
                        for (int j = 0; j < curN - 1; j += 3) {
                            cur ^= a3[((i + curN - 1 + j) % curN) * 3 + k] ^ a3[((i + j) % curN) * 3 + k];
                            A[((i + 2 + j + curN) % curN) * 3 + k] = total ^ cur;
                        }
                    }
                }
            } else if (curN % 3 == 2) {
                for (int k = 0; k < 3; k++) {
                    int total = 0;
                    for (int i = 0; i < curN; i++) {
                        total ^= a3[i * 3 + k];
                    }

                    for (int i = 0; i < 3; i++) {
                        int cur = 0;
                        for (int j = 0; j < curN; j += 3) {
                            cur ^= a3[((i + j) % curN) * 3 + k];
                        }
                        A[((i + curN) % curN) * 3 + k] = total ^ cur;
                        for (int j = 0; j < curN; j += 3) {
                            cur ^= a3[((i + j + 1) % curN) * 3 + k] ^ a3[((i + j) % curN) * 3 + k];
                            A[((i + j + 3) % curN) * 3 + k] = total ^ cur;
                        }
                    }
                }
            }
        }
        cout << 2 << endl;
        for (int i = 0; i < N; i++) {
            cout << A[i] << ' ';
        }
        cout << endl;

        int res;
        cin >> res;
        if (res == -1) {
            exit(0);
        }
    }
}