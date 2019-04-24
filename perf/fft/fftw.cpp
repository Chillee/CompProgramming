#pragma GCC optimize("O3")
#include <fftw3.h>
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
namespace test {
template <int maxn> struct FFT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFT() {
        timeit x("roots");
        // int N = MAXN;
        // for (int i = 0; i < N / 2; i++) {
        //     double alp = M_PI * i * 2 / (double)N;
        //     rt[i + N / 2] = {cos(alp), sin(alp)};
        // }
        // for (int i = N / 2 - 1; i >= 1; i--)
        //     rt[i] = rt[2 * i];
        rt[1] = cpx{1, 0};
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z[] = {1, polar(1.0, M_PI / k)};
            for (int i = k; i < 2 * k; i++)
                rt[i] = rt[i / 2] * z[i & 1];
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
        fill(all(in), cpx{0, 0}), fill(all(out), cpx{0, 0});
        if (a.empty() || b.empty())
            return {};
        int sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        vector<double> res(sz);
        copy(all(a), begin(in));
        for (int i = 0; i < b.size(); i++)
            in[i].imag(b[i]);
        fft(in, n);
        for (int i = 0; i < n; i++)
            in[i] *= in[i];
        for (int i = 0; i < n; i++)
            out[i] = in[(n - i) & (n - 1)] - conj(in[i]);
        fft(out, n);
        for (int i = 0; i < sz; i++)
            res[i] = out[i].imag() / (4 * n);
        return res;
    }
};
} // namespace test

const int MAXN = (1 << 23);
test::FFT<MAXN> fft;
typedef complex<double> cpx;

fftw_complex in[MAXN], out[MAXN];
fftw_plan p, pi;
const int iters = 1;
vector<cpx> P[iters];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int t = 0; t < iters; t++) {
        for (int i = 0; i < MAXN; i++) {
            P[t].push_back(rand() % 10000000);
        }
    }
    p = fftw_plan_dft_1d(MAXN, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    pi = fftw_plan_dft_1d(MAXN, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    // fftw_print_plan(p);
    cout << fixed << setprecision(20);
    {
        timeit x("fftw");
        for (int t = 0; t < iters; t++) {
            for (int i = 0; i < MAXN; i++)
                in[i][0] = P[t][i].real();
            fftw_execute(p);
            fftw_execute(pi);
            double err = 0;
            for (int i = 0; i < MAXN; i++) {
                err = max(err, fabs(in[i][0] - round(in[i][0])));
                // err += fabs(in[i][0] - round(in[i][0]));
            }
            cout << err << endl;
        }
    }
    {
        timeit x("optimized");

        for (int t = 0; t < iters; t++) {
            fft.fft(P[t].data(), P[t].size());
            reverse(P[t].begin() + 1, P[t].end());
            fft.fft(P[t].data(), P[t].size());

            double err = 0;
            for (int i = 0; i < MAXN; i++) {
                err = max(err, fabs(P[t][i].real() - round(P[t][i].real())));
                // err += fabs(P[t][i].real() - round(P[t][i].real()));
            }
            cout << err << endl;
        }
    }
    int A[100], B[100];

    int MAXVALUE;
    int cntA[100], cntB[100];

    int cnt[2 * MAXVALUE];
    for (int i = 0; i < MAXVALUE; i++) {
        for (int j = 0; j < MAXVALUE; j++)
            cnt[i + j] += cntA[i] * cntB[j];
    }
}