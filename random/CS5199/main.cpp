#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

namespace test {
template <int maxn> struct FFT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFT() {
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

typedef complex<double> cpx;
typedef vector<cpx> Poly;
typedef vector<cpx> Eval;
Eval FFT(Poly P) {
    int n = P.size();
    if (n == 1)
        return P;
    Poly P_even(n / 2), P_odd(n / 2);
    for (int j = 0; j < n / 2; j++) {
        P_even[j] = P[j * 2];    // Put all the even terms (2*0, 2*1, 2*2,...) in one polynomial
        P_odd[j] = P[j * 2 + 1]; // odd terms in the other (2*0+1,2*1+1,2*2+1,...)
    }
    Eval eval_even = FFT(P_even); // Recursively evaluate the two polynomials
    Eval eval_odd = FFT(P_odd);
    cpx root_of_unity = exp(2i * M_PI / (double)n); // Generate our n-th root of unity
    Eval result(n);
    for (int j = 0; j < n; j++) {
        cpx j_root_of_unity = pow(root_of_unity, j); // Generates \omega^j
        if (j < n / 2)
            result[j] = eval_even[j] + j_root_of_unity * eval_odd[j];
        else // As (\omega^(j + n/2))^2 = (\omega^j)^2, we're reusing them here.
            result[j] = eval_even[j - (n / 2)] + j_root_of_unity * eval_odd[j - (n / 2)];
    }
    return result;
}
namespace ntt {
typedef long long ll;
typedef vector<ll> Poly;
typedef vector<ll> Eval;
Eval FTT(Poly P) {
    int n = P.size();
    if (n == 1)
        return P;
    Poly P_even(n / 2), P_odd(n / 2);
    for (int j = 0; j < n / 2; j++) {
        P_even[j] = P[j * 2];    // Put all the even terms (2*0, 2*1, 2*2,...) in one polynomial
        P_odd[j] = P[j * 2 + 1]; // odd terms in the other (2*0+1,2*1+1,2*2+1,...)
    }
    Eval eval_even = NTT(P_even); // Recursively evaluate the two polynomials
    Eval eval_odd = NTT(P_odd);
    ll root_of_unity = 3;
    Eval result(n);
    for (int j = 0; j < n; j++) {
        ll j_root_of_unity = pow(root_of_unity, j); // Generates \omega^j
        if (j < n / 2)
            result[j] = eval_even[j] + j_root_of_unity * eval_odd[j];
        else // As (\omega^(j + n/2))^2 = (\omega^j)^2, we're reusing them here.
            result[j] = eval_even[j - (n / 2)] + j_root_of_unity * eval_odd[j - (n / 2)];
    }
    return result;
}
} // namespace ntt

const int MAXN = 1 << 21;
test::FFT<2 * MAXN> fft;
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

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Poly P;

    for (int i = 0; i < MAXN; i++) {
        P.push_back(rand() % (int)100);
    }
    {
        timeit x("Simple");
        auto res = FFT(P);
        // cout << res[5] << endl;
        // for (auto i : res) {
        //     cout << i << ' ';
        // }
        // cout << endl;
    }
    {
        timeit x("Optimized");
        fft.fft(P.data(), P.size());
        // cout << P[5] << endl;
        // for (auto i : P) {
        //     cout << i << ' ';
        // }
        // cout << endl;
    }
}