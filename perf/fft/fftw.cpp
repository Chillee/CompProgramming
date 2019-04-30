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
namespace kactl {
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<double> C;
typedef complex<long double> Cd;
typedef vector<double> vd;

void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	vi rev(n); static vector<C> rt(2, 1);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	// for (static int k = 2; k < n; k *= 2) {
	// 	rt.resize(n);
	// 	C z[] = {1, polar(1.0, M_PI / k)};
	// 	rep(i, k, 2 * k) rt[i] = C(rt[i / 2]) * z[i & 1];
	// }
	for (static int k = 2; k < n; k *= 2) {
		rt.resize(n);
		Cd z[] = {1, polar(1.0L, M_PIl / k)};
		rep(i, k, 2 * k) rt[i] = Cd(rt[i / 2]) * z[i & 1];
	}
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n), rt;
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	trav(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
typedef vector<ll> vl;
template <int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n), rt;
	rep(i,0,sz(a)) L[i] = Cd(a[i] / cut, a[i] % cut);
	rep(i,0,sz(b)) R[i] = Cd(b[i] / cut, b[i] % cut);
	fft(L), fft(R);
	rep(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i,0,sz(res)) {
		ll av = ll(outl[i].real()+.5), cv = ll(outs[i].imag()+.5);
		ll bv = ll(outl[i].imag()+.5) + ll(outs[i].real()+.5);
		res[i] = ((av % M * cut + bv % M) * cut + cv % M) % M;
	}
	return res;
}
}

const int MAXN = (1 << 20);
test::FFT<MAXN> fft;
typedef complex<double> cpx;

fftw_complex in[MAXN], out[MAXN];
fftw_plan p, pi;
const int iters = 5;
vector<cpx> P[iters];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    for (int t = 0; t < iters; t++) {
        for (int i = 0; i < MAXN; i++) {
            P[t].push_back(rand() % (int)7e4);
        }
    }
    p = fftw_plan_dft_1d(MAXN, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    pi = fftw_plan_dft_1d(MAXN, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    // fftw_print_plan(p);
    cout << fixed << setprecision(20);
    // {
    //     timeit x("fftw");
    //     double err = 0;
    //     for (int t = 0; t < iters; t++) {
    //         for (int i = 0; i < MAXN; i++)
    //             in[i][0] = P[t][i].real();
    //         cout<<in[0][0]<<endl;
    //         fftw_execute(p);
    //         fftw_execute(pi);
    //         cout<<in[0][0]<<endl;
    //         for (int i = 0; i < MAXN; i++) {
    //             err = max(err, fabs(in[i][0] - round(in[i][0])));
    //             // err += fabs(in[i][0] - round(in[i][0]));
    //         }
    //     }
    //     cout << err << endl;
    // }
    {
        timeit x("optimized");
        double err = 0;
        for (int t = 0; t < iters; t++) {
            vector<double> a(MAXN), b(MAXN);
            for (int i=0; i<MAXN; i++){
                a[i] = P[t][i].real(), b[i] = P[t][i].imag();
            }
            auto res = kactl::conv(a, b);
            for (int i = 0; i < MAXN; i++) {
                err = max(err, fabs(res[i] - round(res[i])));
                // err += fabs(P[t][i].real() - round(P[t][i].real()));
            }
            // cout << err << endl;
        }
        cout << err << endl;
    }
}