#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef complex<double> cpx;
const int LOGN = 4, MAXN = 1 << LOGN;

struct FFT {
    int rev[MAXN];
    cpx rt[MAXN];
    FFT() {
        rev[0] = 0;
        rt[1] = cpx(1, 0);
        for (int i = 0; i < MAXN; i++)
            rev[i] = (rev[i / 2] | (i & 1) << LOGN) / 2;
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z(cos(M_PI / k), sin(M_PI / k));
            for (int i = 0; i < k / 2; i += k)
                rt[2 * i] = rt[i], rt[2 * i + 1] = rt[i] * z;
        }
    }
    void fft(cpx *a) {
        for (int i = 0; i < MAXN; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < MAXN; k *= 2)
            for (int i = 0; i < MAXN; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    cpx t = rt[j + k] * a[i + j + k];
                    a[i + j + k] = a[i + j] - t;
                    a[i + j] += t;
                }
    }

    void multiply(cpx *a, cpx *b) {
        fft(a), fft(b);
        for (int i = 0; i < MAXN; i++)
            a[i] *= b[i] / (double)MAXN;
        reverse(a + 1, a + MAXN);
        fft(a);
    }
};
FFT fft;
cpx A[MAXN], B[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    A[0] = (0, 1);
    B[0] = (0, 1);
    // fft.fft(A);
    // reverse(A + 1, A + MAXN);
    // // fft.fft(A);
    // // B[0] = 1;
    fft.multiply(A, B);
    for (int i = 0; i < 5; i++)
        cout << A[i] << ' ';
    cout << endl;
}