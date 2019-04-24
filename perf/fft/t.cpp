#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef complex<double> cpx;
typedef complex<double> cd;
const int LOGN = 22, MAXN = 1 << LOGN;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 10);

namespace FFT10 {
template <typename dataType> struct Complex {
    dataType re, im;
    Complex() : re(0), im(0) {}
    Complex(const dataType &a, const dataType &b) : re(a), im(b) {}
    Complex(const complex<dataType> &c) : re(c.real()), im(c.imag()) {}
    Complex &operator=(const complex<dataType> &c) {
        this->re = c.real();
        this->im = c.imag();
        return *this;
    }
    dataType real() const { return this->re; }
    dataType imag() const { return this->im; }
    void real(dataType const &r) { this->re = r; }
    void imag(dataType const &i) { this->im = i; }
    void polar(const dataType &rho, const dataType &theta = 0) {
        this->re = rho * cos(theta);
        this->im = rho * sin(theta);
    }
    Complex conj() const { return Complex(this->re, -this->im); }
    dataType norm() const { return sqrt(this->re * this->re + this->im * this->im); }
    dataType normSquared() const { return this->re * this->re + this->im * this->im; }
    Complex inverse() const { return this->conj() / this->normSquared(); }
    Complex operator+(const Complex<dataType> &c) const { return Complex(this->re + c.re, this->im + c.im); }
    Complex &operator+=(const Complex<dataType> &c) { return *this = *this + c; }
    Complex operator-(const Complex<dataType> &c) const { return Complex(this->re - c.re, this->im - c.im); }
    Complex &operator-=(const Complex<dataType> &c) { return *this = *this + c; }
    Complex operator*(const Complex<dataType> &c) const {
        return Complex(this->re * c.real() - this->im * c.imag(), this->re * c.imag() + this->im * c.real());
    }
    Complex &operator*=(const Complex<dataType> &c) { return *this = *this * c; }
    Complex operator*(const dataType &c) const { return Complex(this->re * c, this->im * c); }
    Complex &operator*=(const dataType &c) { return *this = *this * c; }
    Complex operator/(const Complex<dataType> &c) const { return *this * c.inverse(); }
    Complex &operator/=(const Complex<dataType> &c) { return *this = *this / c; }
    Complex operator/(const dataType &c) const { return Complex(this->re / c, this->im / c); }
    Complex &operator/=(const dataType &c) { return *this = *this / c; }
    friend istream &operator>>(istream &stream, Complex &C) { return stream >> C.re >> C.im; }
    friend ostream &operator<<(ostream &stream, const Complex &C) {
        return stream << "(" << C.re << "," << C.im << ")";
    }
};

using FFT_t = Complex<double>;
int log2i(unsigned long long a) { return __builtin_clzll(1) - __builtin_clzll(a); }
int get_size(int n) { return 1 << (log2i(n) + 1); }
bool ispow2(int a) { return (a & -a) == a; }
vector<FFT_t> roots;
// pre-calculate complex roots, log(N) calls to sin/cos
void gen_roots(int N) {
    if ((int)roots.size() != N) {
        roots.clear();
        roots.resize(N);
        for (int i = 0; i < N; ++i) {
            if ((i & -i) == i) {
                roots[i] = polar(1.0, 2.0 * 3.1415926535897932384626 * i / N);
            } else {
                roots[i] = roots[i & -i] * roots[i - (i & -i)];
            }
        }
    }
}
void fft(FFT_t *a, int n, bool isInv = false) {
    for (int i = 1, j = 0; i < n; ++i) {
        int m = n >> 1;
        for (; j >= m; m >>= 1)
            j -= m;
        j += m;
        if (i < j)
            swap(a[i], a[j]);
    }
    gen_roots(n);
    assert((int)roots.size() == n);
    for (int iter = 1, sh = log2i(n) - 1; iter < n; iter *= 2, --sh) {
        for (int x = 0; x < n; x += 2 * iter) {
            for (int y = 0; y < iter; ++y) {
                FFT_t ome = roots[y << sh];
                if (isInv)
                    ome = ome.conj();
                FFT_t v = a[x + y], w = a[x + y + iter];
                a[x + y] = v + ome * w;
                a[x + y + iter] = v - ome * w;
            }
        }
    }
}
void fft(vector<FFT_t> &v, bool isInv = false) {
    assert(ispow2(v.size()));
    fft(v.data(), v.size(), isInv);
}
vector<FFT_t> conv(vector<long long> const &v, int n) {
    assert(ispow2(n));
    vector<FFT_t> a(n);
    for (size_t i = 0; i < v.size(); ++i) {
        a[i].real(v[i]);
    }
    fft(a, false);
    return a;
}
vector<long long> convmul(vector<FFT_t> a, vector<FFT_t> const &b) {
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] *= b[i];
    }
    fft(a, true);
    vector<long long> ret(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        ret[i] = llround(a[i].real() / (int)a.size());
    }
    return ret;
}
vector<long long> poly_mul(vector<long long> const &a, vector<long long> const &b) {
    int n = get_size(a.size() + b.size() - 1);
    vector<FFT_t> x = conv(a, n);
    vector<FFT_t> y = conv(b, n);
    vector<long long> ret = convmul(x, y);
    ret.resize(a.size() + b.size() - 1);
    return ret;
}
vector<long long> blockify(vector<long long> const &a) {
    vector<long long> ret(3 * a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        ret[3 * i] = a[i] % 30000;
        ret[3 * i + 1] = a[i] / 30000;
    }
    return ret;
}
vector<long long> unblockify(vector<long long> const &a, long long const &mod) {
    assert(a.size() % 3 == 0);
    vector<long long> ret(a.size() / 3);
    for (size_t i = 0; i < ret.size(); ++i) {
        ret[i] = (((a[3 * i + 2]) % mod * 30000 + a[3 * i + 1]) % mod * 30000 + a[3 * i]) % mod;
    }
    return ret;
}
vector<long long> poly_mul_block(vector<long long> const &a, vector<long long> const &b, long long const &mod) {
    vector<long long> c = blockify(a), d = blockify(b);
    int n = get_size(c.size() + d.size() - 1);
    vector<FFT_t> x = conv(c, n);
    vector<FFT_t> y = conv(d, n);
    vector<long long> ret = convmul(x, y);
    ret.resize(3 * (a.size() + b.size() - 1));
    vector<long long> r = unblockify(ret, mod);
    return r;
}
} // namespace FFT10

// 2-in-1 KACTL
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
        int n = 1 << lg2(a.size() + b.size() - 1);
        fill(in, in + n, cpx{0, 0}), fill(out, out + n, cpx{0, 0});
        copy(a.begin(), a.end(), begin(in));
        for (int i = 0; i < b.size(); i++)
            in[i].imag(b[i]);
        fft(in, n);
        for (int i = 0; i < n; i++)
            in[i] *= in[i];
        for (int i = 0; i < n; i++)
            out[i] = in[(n - i) & (n - 1)] - conj(in[i]);
        fft(out, n);
        vector<double> res(n);
        for (int i = 0; i < n; i++)
            res[i] = out[i].imag() / (4 * n);
        return res;
    }
};

FFT<MAXN> fft5;
vector<double> vcA, vcB;
vector<int> Ao, Bo, viA, viB;
vector<ll> vlA, vlB;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAXN / 2; i++) {
        Ao.push_back(uni(rng));
        Bo.push_back(uni(rng));
    }
    vector<double> res;
    clock_t begin;

    /** KACTL 2-in-1 **/
    vcA.clear(), vcB.clear();
    for (int i = 0; i < Ao.size(); i++) {
        vcA.push_back(Ao[i]), vcB.push_back(Bo[i]);
    }
    begin = clock();
    // res = fft5.multiply(vcA, vcB);
    res = fft5.multiply(vcA, vcB);
    vector<ll> res2(res.size());
    for (int i = 0; i < res.size(); i++)
        res2[i] = res[i] + 0.5;
    cout << "2-in-1: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res2[Ao.size() / 2] << endl;
    /** ----------- **/
    /** Dacin **/
    vlA.clear(), vlB.clear();
    for (int i = 0; i < Ao.size(); i++) {
        vlA.push_back(Ao[i]), vlB.push_back(Bo[i]);
    }
    begin = clock();
    vector<ll> resl = FFT10::poly_mul(vlA, vlB);
    cout << "Dacin: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << resl[Ao.size() / 2] << endl;
    /** ----------- **/
    for (int i = 0; i < res2.size(); i++) {
        assert(res2[i] == resl[i]);
    }
}