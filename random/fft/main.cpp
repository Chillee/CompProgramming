#include <bits/stdc++.h>

using namespace std;

const int LOGN = 21, MAXN = 1 << LOGN;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 10);
template <int maxn> struct FFT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFT() {
        rt[1] = cpx{1, 0};
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z(cos(M_PI / k), sin(M_PI / k));
            for (int i = k / 2; i < k; i++)
                rt[2 * i] = rt[i], rt[2 * i + 1] = rt[i] * z;
        }
    }
    void fft(cpx *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
                    cpx z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }

    cpx in[MAXN], out[MAXN];
    vector<double> multiply(const vector<double> &a, const vector<double> &b) {
        int n = 1 << lg2(a.size() + b.size());
        fill(in, in + n, cpx{0, 0}), fill(out, out + n, cpx{0, 0});
        for (int i = 0; i < a.size(); i++)
            in[i].real(a[i]);
        for (int i = 0; i < b.size(); i++)
            in[i].imag(b[i]);
        fft(&in[0], n);
        for (int i = 0; i < n; i++) {
            int j = (n - i) & (n - 1);
            out[i] = (in[j] * in[j] - conj(in[i] * in[i])) * cpx{0, -0.25 / n};
        }
        fft(&out[0], n);
        vector<double> res(n);
        for (int i = 0; i < n; i++)
            res[i] = out[i].real();
        return res;
    }
};

FFT<MAXN> fft;
vector<double> a, b;
signed main() {
    for (int i = 0; i < MAXN / 2; i++) {
        a.push_back(uni(rng));
        b.push_back(uni(rng));
    }
    clock_t begin;
    begin = clock();
    vector<double> res;
    // for (int iter = 0; iter < 100; iter++) {
    res = fft.multiply(a, b);
    // }
    // for (auto i : res) {
    //     cout << i << " ";
    // }
    // cout << endl;
    cout << "kactl: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[a.size() / 2] << endl;
}