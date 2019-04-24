#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

const int MOD = (119 << 23) + 1;
// const int MOD = 1e5 + 7;
namespace mine {
template <int maxn, int MOD> struct FFTMod {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFTMod() {
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

    cpx in[2][MAXN], out[2][MAXN];
    vector<ll> multiply(const vector<int> &a, const vector<int> &b) {
        fill(all(in[0]), cpx{0, 0}), fill(all(in[1]), cpx{0, 0});
        int cut = sqrt(MOD), sz = a.size() + b.size() - 1;
        int n = 1 << lg2(sz);
        vector<ll> res(sz);
        for (int i = 0; i < a.size(); i++)
            in[0][i] = {a[i] / cut, a[i] % cut};
        for (int i = 0; i < b.size(); i++)
            in[1][i] = {b[i] / cut, b[i] % cut};
        fft(in[0], n), fft(in[1], n);
        for (int i = 0; i < n; i++) {
            int j = (n - i) & (n - 1);
            cpx fl = (in[0][i] + conj(in[0][j])) * cpx{0.5, 0}, fs = (in[0][i] - conj(in[0][j])) * cpx{0, -0.5},
                gl = (in[1][i] + conj(in[1][j])) * cpx{0.5, 0}, gs = (in[1][i] - conj(in[1][j])) * cpx{0, -0.5};
            out[0][-i & (n - i)] = (fl * gl) + (fl * gs) * cpx{0, 1};
            out[1][-i & (n - i)] = (fs * gl) + (fs * gs) * cpx{0, 1};
        }
        fft(out[0], n), fft(out[1], n);
        for (int i = 0; i < sz; i++) {
            out[0][i] /= n, out[1][i] /= n;
            ll av = round(out[0][i].real());
            ll bv = round(out[0][i].imag()) + round(out[1][i].real());
            ll cv = round(out[1][i].imag());
            av %= MOD, bv %= MOD, cv %= MOD;
            res[i] = (av * cut * cut + bv * cut + cv) % MOD;
        }
        return res;
    }
};
} // namespace mine
namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<double> C;
typedef vector<double> vd;
typedef complex<double> C;
void fft(vector<C> &a, vector<C> &rt, vi &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k]; /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vd conv(const vd &a, const vd &b) {
    if (a.empty() || b.empty())
        return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1];
    }
    copy(all(a), begin(in));
    rep(i, 0, sz(b)) in[i].imag(b[i]);
    fft(in, rt, rev, n);
    trav(x, in) x *= x;
    rep(i, 0, n) out[i] = in[(n - i) & (n - 1)] - conj(in[i]);
    fft(out, rt, rev, n);
    rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

template <int MOD> vector<ll> convMod(const vi &a, const vi &b) {
    if (a.empty() || b.empty())
        return {};
    vector<ll> res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L, cut = sqrt(MOD);
    vector<C> inl(n), inr(n), outs(n), outl(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1];
    }
    rep(i, 0, a.size()) inl[i] = {a[i] / cut, a[i] % cut};
    rep(i, 0, b.size()) inr[i] = {b[i] / cut, b[i] % cut};
    fft(inl, rt, rev, n), fft(inr, rt, rev, n);
    rep(i, 0, n) {
        int j = (n - i) & (n - 1);
        C fl = (inl[i] + conj(inl[j])) * C{0.5, 0}, fs = (inl[i] - conj(inl[j])) * C{0, -0.5},
          gl = (inr[i] + conj(inr[j])) * C{0.5, 0}, gs = (inr[i] - conj(inr[j])) * C{0, -0.5};
        outl[-i & (n - i)] = fl * (gl + gs) * C{0, 1};
        outs[-i & (n - i)] = fs * (gl + gs) * C{0, 1};
    }
    fft(outl, rt, rev, n), fft(outs, rt, rev, n);
    rep(i, 0, sz(res)) {
        outl[i] /= n, outs[i] /= n;
        ll av = round(outl[i].real());
        ll bv = round(outl[i].imag()) + round(outs[i].real());
        ll cv = round(outs[i].imag());
        av %= MOD, bv %= MOD, cv %= MOD;
        res[i] = (av * cut * cut + bv * cut + cv) % MOD;
    }
    return res;
}
} // namespace kactl
namespace NTT {
template <int maxn> struct NTT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn), MOD = (119 << 23) + 1, root = 3;
    int rev[MAXN], rt[MAXN];

    int mul(int a, int b) { return (long long)a * b % MOD; }
    int sub(int a, int b) { return b > a ? a - b + MOD : a - b; }
    int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int binExp(int base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        rt[1] = 1;
        for (int k = 1; k < lg2(MAXN); k++) {
            int z[] = {1, binExp(root, (MOD - 1) >> (k + 1))};
            for (int i = (1 << k); i < 2 << k; i++)
                rt[i] = mul(rt[i / 2], z[i & 1]);
        }
    }
    void ntt(int *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    int z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }
    int in[2][MAXN];
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        fill(all(in[0]), 0), fill(all(in[1]), 0);
        if (a.empty() || b.empty())
            return {};
        int sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        copy(all(a), in[0]), copy(all(b), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<int>(in[0], in[0] + sz);
    }
};
} // namespace NTT
namespace tfg {
typedef double ld;

const ld PI = acos(-1);

struct Complex {
    ld real, imag;
    Complex conj() { return Complex(real, -imag); }
    Complex(ld a = 0, ld b = 0) : real(a), imag(b) {}
    Complex operator+(const Complex &o) const { return Complex(real + o.real, imag + o.imag); }
    Complex operator-(const Complex &o) const { return Complex(real - o.real, imag - o.imag); }
    Complex operator*(const Complex &o) const {
        return Complex(real * o.real - imag * o.imag, real * o.imag + imag * o.real);
    }
    Complex operator/(ld o) const { return Complex(real / o, imag / o); }
    void operator*=(Complex o) { *this = *this * o; }
    void operator/=(ld o) { real /= o, imag /= o; }
};

typedef std::vector<Complex> CVector;

const int ms = 1 << 22;

int bits[ms];
Complex root[ms];

void initFFT() {
    root[1] = Complex(1);
    for (int len = 2; len < ms; len += len) {
        Complex z(cos(PI / len), sin(PI / len));
        for (int i = len / 2; i < len; i++) {
            root[2 * i] = root[i];
            root[2 * i + 1] = root[i] * z;
        }
    }
}

void pre(int n) {
    int LOG = 0;
    while (1 << (LOG + 1) < n) {
        LOG++;
    }
    for (int i = 1; i < n; i++) {
        bits[i] = (bits[i >> 1] >> 1) | ((i & 1) << LOG);
    }
}

CVector fft(CVector a, bool inv = false) {
    int n = a.size();
    pre(n);
    if (inv) {
        std::reverse(a.begin() + 1, a.end());
    }
    for (int i = 0; i < n; i++) {
        int to = bits[i];
        if (to > i) {
            std::swap(a[to], a[i]);
        }
    }
    for (int len = 1; len < n; len *= 2) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                Complex u = a[i + j], v = a[i + j + len] * root[len + j];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
    return a;
}

void fft2in1(CVector &a, CVector &b) {
    int n = (int)a.size();
    for (int i = 0; i < n; i++) {
        a[i] = Complex(a[i].real, b[i].real);
    }
    auto c = fft(a);
    for (int i = 0; i < n; i++) {
        a[i] = (c[i] + c[(n - i) % n].conj()) * Complex(0.5, 0);
        b[i] = (c[i] - c[(n - i) % n].conj()) * Complex(0, -0.5);
    }
}

void ifft2in1(CVector &a, CVector &b) {
    int n = (int)a.size();
    for (int i = 0; i < n; i++) {
        a[i] = a[i] + b[i] * Complex(0, 1);
    }
    a = fft(a, true);
    for (int i = 0; i < n; i++) {
        b[i] = Complex(a[i].imag, 0);
        a[i] = Complex(a[i].real, 0);
    }
}

std::vector<long long> mod_mul(const std::vector<long long> &a, const std::vector<long long> &b,
                               long long cut = 1 << 15) {
    // TODO cut memory here by /2
    int n = (int)a.size();
    CVector C[4];
    for (int i = 0; i < 4; i++) {
        C[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        C[0][i] = a[i] % cut;
        C[1][i] = a[i] / cut;
        C[2][i] = b[i] % cut;
        C[3][i] = b[i] / cut;
    }
    fft2in1(C[0], C[1]);
    fft2in1(C[2], C[3]);
    for (int i = 0; i < n; i++) {
        // 00, 01, 10, 11
        Complex cur[4];
        for (int j = 0; j < 4; j++)
            cur[j] = C[j / 2 + 2][i] * C[j % 2][i];
        for (int j = 0; j < 4; j++)
            C[j][i] = cur[j];
    }
    ifft2in1(C[0], C[1]);
    ifft2in1(C[2], C[3]);
    std::vector<long long> ans(n, 0);
    for (int i = 0; i < n; i++) {
        // if there are negative values, care with rounding
        ans[i] += (long long)(C[0][i].real + 0.5);
        ans[i] += (long long)(C[1][i].real + C[2][i].real + 0.5) * cut;
        ans[i] += (long long)(C[3][i].real + 0.5) * cut * cut;
    }
    return ans;
}

std::vector<int> mul(const std::vector<int> &a, const std::vector<int> &b) {
    int n = 1;
    while (n - 1 < (int)a.size() + (int)b.size() - 2)
        n += n;
    CVector poly(n);
    for (int i = 0; i < n; i++) {
        if (i < (int)a.size()) {
            poly[i].real = a[i];
        }
        if (i < (int)b.size()) {
            poly[i].imag = b[i];
        }
    }
    poly = fft(poly);
    for (int i = 0; i < n; i++) {
        poly[i] *= poly[i];
    }
    poly = fft(poly, true);
    std::vector<int> c(n, 0);
    for (int i = 0; i < n; i++) {
        c[i] = (int)(poly[i].imag / 2 + 0.5);
    }
    while (c.size() > 0 && c.back() == 0)
        c.pop_back();
    return c;
}
} // namespace tfg
namespace FFTNeal {
template <typename float_t> struct complex {
    float_t x, y;
    complex<float_t>(float_t _x = 0, float_t _y = 0) : x(_x), y(_y) {}
    float_t real() const { return x; }
    void real(float_t _x) { x = _x; }
    float_t imag() const { return y; }
    void imag(float_t _y) { y = _y; }
    complex<float_t> &operator+=(const complex<float_t> &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    complex<float_t> &operator-=(const complex<float_t> &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    complex<float_t> operator+(const complex<float_t> &other) const { return complex<float_t>(*this) += other; }
    complex<float_t> operator-(const complex<float_t> &other) const { return complex<float_t>(*this) -= other; }
    complex<float_t> operator*(const complex<float_t> &other) const {
        return {x * other.x - y * other.y, x * other.y + other.x * y};
    }
    complex<float_t> operator/(const float_t &other) const { return {x / other, y / other}; }
};
template <typename float_t> complex<float_t> conj(const complex<float_t> &c) { return {c.x, -c.y}; }

template <typename float_t> complex<float_t> polar(float_t magnitude, float_t angle) {
    return {magnitude * cos(angle), magnitude * sin(angle)};
}
typedef double float_t;
const float_t ONE = 1;
const float_t PI = acos(-ONE);

vector<complex<float_t>> roots;
vector<int> bit_reverse;

bool is_power_of_two(int n) { return (n & (n - 1)) == 0; }

int round_up_power_two(int n) {
    assert(n > 0);

    while (n & (n - 1))
        n = (n | (n - 1)) + 1;

    return n;
}

// Given n (a power of two), finds k such that n == 1 << k.
int get_length(int n) {
    assert(is_power_of_two(n));
    return __builtin_ctz(n);
}

// Rearranges the indices to be sorted by lowest bit first, then second lowest, etc., rather than highest bit first.
// This makes even-odd div-conquer much easier.
template <typename complex_array> void bit_reorder(int n, complex_array &&values) {
    if ((int)bit_reverse.size() != n) {
        bit_reverse.assign(n, 0);
        int length = get_length(n);

        for (int i = 0; i < n; i++)
            bit_reverse[i] = (bit_reverse[i >> 1] >> 1) + ((i & 1) << (length - 1));
    }

    for (int i = 0; i < n; i++)
        if (i < bit_reverse[i])
            swap(values[i], values[bit_reverse[i]]);
}

void prepare_roots(int n) {
    if ((int)roots.size() >= n)
        return;

    if (roots.empty())
        roots = {{0, 0}, {1, 0}};

    int length = get_length(roots.size());
    roots.resize(n);

    // The roots array is set up such that for a given power of two n >= 2, roots[n / 2] through roots[n - 1] are
    // the first half of the n-th roots of unity.
    while (1 << length < n) {
        double min_angle = 2 * PI / (1 << (length + 1));

        for (int i = 0; i < 1 << (length - 1); i++) {
            int index = (1 << (length - 1)) + i;
            roots[2 * index] = roots[index];
            roots[2 * index + 1] = polar(ONE, min_angle * (2 * i + 1));
        }

        length++;
    }
}

template <typename complex_array> void fft_recursive(int n, complex_array &&values, int depth = 0) {
    if (n <= 1)
        return;

    if (depth == 0) {
        assert(is_power_of_two(n));
        prepare_roots(n);
        bit_reorder(n, values);
    }

    n /= 2;
    fft_recursive(n, values, depth + 1);
    fft_recursive(n, values + n, depth + 1);

    for (int i = 0; i < n; i++) {
        const complex<float_t> &even = values[i];
        complex<float_t> odd = values[n + i] * roots[n + i];
        values[n + i] = even - odd;
        values[i] = even + odd;
    }
}

// Iterative version of fft_recursive above.
template <typename complex_array> void fft_iterative(int N, complex_array &&values) {
    assert(is_power_of_two(N));
    prepare_roots(N);
    bit_reorder(N, values);

    for (int n = 1; n < N; n *= 2)
        for (int start = 0; start < N; start += 2 * n)
            for (int i = 0; i < n; i++) {
                const complex<float_t> &even = values[start + i];
                complex<float_t> odd = values[start + n + i] * roots[n + i];
                values[start + n + i] = even - odd;
                values[start + i] = even + odd;
            }
}

inline complex<float_t> extract(int N, const vector<complex<float_t>> &values, int index, int side) {
    if (side == -1) {
        // Return the product of 0 and 1.
        int other = (N - index) & (N - 1);
        return (conj(values[other] * values[other]) - values[index] * values[index]) * complex<float_t>(0, 0.25);
    }

    int other = (N - index) & (N - 1);
    int sign = side == 0 ? +1 : -1;
    complex<float_t> multiplier = side == 0 ? complex<float_t>(0.5, 0) : complex<float_t>(0, -0.5);
    return multiplier * complex<float_t>(values[index].real() + values[other].real() * sign,
                                         values[index].imag() - values[other].imag() * sign);
}

void invert_fft(int N, vector<complex<float_t>> &values) {
    assert(N >= 2);

    for (int i = 0; i < N; i++)
        values[i] = conj(values[i]) * (ONE / N);

    for (int i = 0; i < N / 2; i++) {
        complex<float_t> first = values[i] + values[N / 2 + i];
        complex<float_t> second = (values[i] - values[N / 2 + i]) * roots[N / 2 + i];
        values[i] = first + second * complex<float_t>(0, 1);
    }

    fft_recursive(N / 2, values.begin());

    for (int i = N - 1; i >= 0; i--)
        values[i] = i % 2 == 0 ? values[i / 2].real() : values[i / 2].imag();
}

const int FFT_CUTOFF = 150;
const double SPLIT_CUTOFF = 2e15;
const int SPLIT_BASE = 1 << 15;

template <typename T_out, typename T_in> vector<T_out> square(const vector<T_in> &input) {
    int n = input.size();

#ifdef NEAL
    // Sanity check to make sure I'm not forgetting to split.
    double max_value = *max_element(input.begin(), input.end());
    assert(n * max_value * max_value < SPLIT_CUTOFF);
#endif

    // Brute force when n is small enough.
    if (n < 1.5 * FFT_CUTOFF) {
        vector<T_out> result(2 * n - 1);

        for (int i = 0; i < n; i++) {
            result[2 * i] += (T_out)input[i] * input[i];

            for (int j = i + 1; j < n; j++)
                result[i + j] += (T_out)2 * input[i] * input[j];
        }

        return result;
    }

    int N = round_up_power_two(n);
    assert(N >= 2);
    prepare_roots(2 * N);
    vector<complex<float_t>> values(N, 0);

    for (int i = 0; i < n; i += 2)
        values[i / 2] = complex<float_t>(input[i], i + 1 < n ? input[i + 1] : 0);

    fft_iterative(N, values.begin());

    for (int i = 0; i <= N / 2; i++) {
        int j = (N - i) & (N - 1);
        complex<float_t> even = extract(N, values, i, 0);
        complex<float_t> odd = extract(N, values, i, 1);
        complex<float_t> aux = even * even + odd * odd * roots[N + i] * roots[N + i];
        complex<float_t> tmp = even * odd;
        values[i] = aux - complex<float_t>(0, 2) * tmp;
        values[j] = conj(aux) - complex<float_t>(0, 2) * conj(tmp);
    }

    for (int i = 0; i < N; i++)
        values[i] = conj(values[i]) * (ONE / N);

    fft_recursive(N, values.begin());
    vector<T_out> result(2 * n - 1);

    for (int i = 0; i < (int)result.size(); i++) {
        float_t value = i % 2 == 0 ? values[i / 2].real() : values[i / 2].imag();
        result[i] = is_integral<T_out>::value ? round(value) : value;
    }

    return result;
}

template <typename T_out, typename T_in> vector<T_out> multiply(const vector<T_in> &left, const vector<T_in> &right) {
    if (left == right)
        return square<T_out>(left);

    int n = left.size();
    int m = right.size();

#ifdef NEAL
    // Sanity check to make sure I'm not forgetting to split.
    double max_left = *max_element(left.begin(), left.end());
    double max_right = *max_element(right.begin(), right.end());
    assert(max(n, m) * max_left * max_right < SPLIT_CUTOFF);
#endif

    // Brute force when either n or m is small enough.
    if (min(n, m) < FFT_CUTOFF) {
        vector<T_out> result(n + m - 1);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                result[i + j] += (T_out)left[i] * right[j];

        return result;
    }

    int N = round_up_power_two(n + m - 1);
    vector<complex<float_t>> values(N, 0);

    for (int i = 0; i < n; i++)
        values[i].real(left[i]);

    for (int i = 0; i < m; i++)
        values[i].imag(right[i]);

    fft_iterative(N, values.begin());

    for (int i = 0; i <= N / 2; i++) {
        int j = (N - i) & (N - 1);
        complex<float_t> product_i = extract(N, values, i, -1);
        values[i] = product_i;
        values[j] = conj(product_i);
    }

    invert_fft(N, values);
    vector<T_out> result(n + m - 1);

    for (int i = 0; i < (int)result.size(); i++)
        result[i] = is_integral<T_out>::value ? round(values[i].real()) : values[i].real();

    return result;
}

template <typename T> vector<T> mod_multiply(const vector<T> &left, const vector<T> &right, T mod, bool split = false) {
    int n = left.size();
    int m = right.size();

    for (int i = 0; i < n; i++)
        assert(0 <= left[i] && left[i] < mod);

    for (int i = 0; i < m; i++)
        assert(0 <= right[i] && right[i] < mod);

#ifdef NEAL
    // Sanity check to make sure I'm not forgetting to split.
    assert(split || (double)max(n, m) * mod * mod < SPLIT_CUTOFF);
#endif

    // Brute force when either n or m is small enough. Brute force up to higher values when split = true.
    if (min(n, m) < (split ? 2 : 1) * FFT_CUTOFF) {
        const uint64_t ULL_BOUND = numeric_limits<uint64_t>::max() - (uint64_t)mod * mod;
        vector<uint64_t> result(n + m - 1);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                result[i + j] += (uint64_t)left[i] * right[j];

                if (result[i + j] > ULL_BOUND)
                    result[i + j] %= mod;
            }

        for (int i = 0; i < (int)result.size(); i++)
            if (result[i] >= (uint64_t)mod)
                result[i] %= mod;

        return vector<T>(result.begin(), result.end());
    }

    if (!split) {
        const vector<uint64_t> &product = multiply<uint64_t>(left, right);
        vector<T> result(n + m - 1);

        for (int i = 0; i < (int)result.size(); i++)
            result[i] = product[i] % mod;

        return result;
    }

    int N = round_up_power_two(n + m - 1);
    vector<complex<float_t>> left_fft(N, 0), right_fft(N, 0);

    for (int i = 0; i < n; i++) {
        left_fft[i].real(left[i] % SPLIT_BASE);
        left_fft[i].imag(left[i] / SPLIT_BASE);
    }

    fft_iterative(N, left_fft.begin());

    if (left == right) {
        copy(left_fft.begin(), left_fft.end(), right_fft.begin());
    } else {
        for (int i = 0; i < m; i++) {
            right_fft[i].real(right[i] % SPLIT_BASE);
            right_fft[i].imag(right[i] / SPLIT_BASE);
        }

        fft_iterative(N, right_fft.begin());
    }

    vector<complex<float_t>> product(N);
    vector<T> result(n + m - 1);

    for (int exponent = 0; exponent <= 2; exponent++) {
        uint64_t multiplier = 1;

        for (int k = 0; k < exponent; k++)
            multiplier = multiplier * SPLIT_BASE % mod;

        fill(product.begin(), product.end(), 0);

        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
                if (x + y == exponent)
                    for (int i = 0; i < N; i++)
                        product[i] += extract(N, left_fft, i, x) * extract(N, right_fft, i, y);

        invert_fft(N, product);

        for (int i = 0; i < (int)result.size(); i++) {
            uint64_t value = round(product[i].real());
            result[i] = (result[i] + value % mod * multiplier) % mod;
        }
    }

    return result;
}
} // namespace FFTNeal

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
const int MAXN = 1 << 10;
mine::FFTMod<2 * MAXN, MOD> myfft;
NTT::NTT<2 * MAXN> myntt;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> a, b;
    for (int i = 0; i < MAXN; i++) {
        a.push_back(MOD - 1);
        b.push_back(MOD - 1);
    }
    vector<int> correct(2 * a.size() - 1);
    if (MOD == (119 << 23) + 1) {
        correct = myntt.multiply(a, b);
    } else if (MAXN < 1e4) {
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                correct[i + j] = (correct[i + j] + (ll)a[i] * b[j]) % MOD;
            }
        }
    } else {
        auto res = myfft.multiply(a, b);
        for (int i = 0; i < res.size(); i++)
            correct[i] = res[i];
    }
    {
        timeit x("neal");
        vector<ll> al, bl;
        for (int i = 0; i < MAXN; i++)
            al.push_back(a[i]), bl.push_back(b[i]);
        auto res = FFTNeal::mod_multiply(a, b, MOD, true);
        for (int i = 0; i < res.size(); i++) {
            if (res[i] != correct[i])
                cout << res[i] << ' ' << correct[i] << endl;
            assert(res[i] == correct[i]);
        }
        cout << endl;
    }
    {
        timeit x("mine");
        auto res = myfft.multiply(a, b);
        for (int i = 0; i < res.size(); i++) {
            if (res[i] != correct[i])
                cout << res[i] << ' ' << correct[i] << endl;
            assert(res[i] == correct[i]);
        }
    }
    // {
    //     timeit x("kactl fft mod");
    //     auto res = kactl::convMod<MOD>(a, b);
    //     for (int i = 0; i < res.size(); i++) {
    //         if (res[i] != correct[i])
    //             cout << res[i] << ' ' << correct[i] << endl;
    //         assert(res[i] == correct[i]);
    //     }
    // }
    {
        timeit x("my ntt");
        auto res = myntt.multiply(a, b);
        for (int i = 0; i < res.size(); i++) {
            assert(res[i] == correct[i]);
        }
    }
    // {
    //     timeit x("kactl fft");
    //     vector<double> ad(MAXN), bd(MAXN);
    //     for (int i = 0; i < MAXN; i++)
    //         ad[i] = a[i], bd[i] = b[i];
    //     auto res = kactl::conv(ad, bd);
    //     for (int i = 0; i < res.size(); i++) {
    //         // res[i] = (ll)round(res[i]) % MOD;
    //         int v = (ll)round(res[i]) % MOD;
    //         if (v != correct[i]) {
    //             cout << v << ' ' << correct[i] << ' ' << res[i] << endl;
    //             assert(v == correct[i]);
    //         }
    //     }
    // }
}