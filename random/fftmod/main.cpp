#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
// #define double long double
const ll LOGN = 20, MAXN = 1 << LOGN;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 1e5);
const ll MOD = 998244353;
const ll root = 3;
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
template <int maxn> struct NTT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    const static int MOD = 998244353;
    const static int root = 3;
    int rev[MAXN], rt[MAXN];

    inline int mul(const int a, const int b) { return (long long)a * b % MOD; }
    inline int sub(const int a, const int b) { return b > a ? a - b + MOD : a - b; }
    inline int add(const int a, const int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int binExp(int base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        int curL = (MOD - 1) >> 2;
        rt[1] = 1;
        for (int k = 2; k < MAXN; k *= 2) {
            int z = binExp(root, curL);
            curL >>= 1;
            for (int i = k / 2; i < k; i++) {
                rt[2 * i] = rt[i], rt[2 * i + 1] = mul(rt[i], z);
            }
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
        int n = 1 << lg2(a.size() + b.size());
        copy(a.begin(), a.end(), in[0]), copy(b.begin(), b.end(), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<int>(begin(in[0]), end(in[0]));
    }
};

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
    complex<float_t> operator*(const complex<float_t> &other) const { return {x * other.x - y * other.y, x * other.y + other.x * y}; }
    complex<float_t> operator/(const float_t &other) const { return {x / other, y / other}; }
};
template <typename float_t> complex<float_t> conj(const complex<float_t> &c) { return {c.x, -c.y}; }

template <typename float_t> complex<float_t> polar(float_t magnitude, float_t angle) { return {magnitude * cos(angle), magnitude * sin(angle)}; }
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
    return multiplier * complex<float_t>(values[index].real() + values[other].real() * sign, values[index].imag() - values[other].imag() * sign);
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

template <int maxn, int MOD> struct FFTMod {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFTMod() {
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

    cpx in[2][MAXN], out[2][MAXN];
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        int cut = sqrt(MOD);
        int n = 1 << lg2(a.size() + b.size());
        fill(in[0], in[0] + n, cpx{0, 0}), fill(in[1], in[1] + n, cpx{0, 0});
        for (int i = 0; i < a.size(); i++)
            in[0][i] = {a[i] / cut, a[i] % cut};
        for (int i = 0; i < b.size(); i++)
            in[1][i] = {b[i] / cut, b[i] % cut};
        fft(in[0], n), fft(in[1], n);
        for (int i = 0; i < n; i++) {
            int j = (n - i) & (n - 1);
            cpx fl = (in[0][i] + conj(in[0][j])) * cpx{0.5, 0}, fs = (in[0][i] - conj(in[0][j])) * cpx{0, -0.5},
                gl = (in[1][i] + conj(in[1][j])) * cpx{0.5, 0}, gs = (in[1][i] - conj(in[1][j])) * cpx{0, -0.5};
            out[0][i] = (fl * gl) + (fl * gs) * cpx{0, 1};
            out[1][i] = (fs * gl) + (fs * gs) * cpx{0, 1};
        }
        reverse(out[0] + 1, out[0] + n), reverse(out[1] + 1, out[1] + n);
        fft(out[0], n), fft(out[1], n);
        for (int i = 0; i < n; i++)
            out[0][i] /= n, out[1][i] /= n;
        vector<ll> res(n);
        for (int i = 0; i < n; i++) {
            ll av = round(out[0][i].real());
            ll bv = round(out[0][i].imag()) + round(out[1][i].real());
            ll cv = round(out[1][i].imag());
            av %= MOD, bv %= MOD, cv %= MOD;
            res[i] = av * cut * cut + bv * cut + cv;
            res[i] = (res[i] % MOD + MOD) % MOD;
        }
        return vector<int>(res.begin(), res.end());
    }
};

FFT<MAXN> fft;
FFTMod<MAXN, MOD> fftm;
NTT<MAXN> ntt;
vector<int> a, b;
vector<ll> al, bl;
vector<double> ad, bd;
signed main() {
    for (int i = 0; i < MAXN / 2; i++) {
        // a.push_back(1e4), b.push_back(1e4);
        a.push_back(uni(rng)), b.push_back(uni(rng));
        al.push_back(a.back()), bl.push_back(b.back());
        ad.push_back(a.back()), bd.push_back(b.back());
    }
    clock_t begin;
    begin = clock();
    auto res = fftm.multiply(a, b);
    cout << "fft-mod: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[a.size() / 2] << endl;
    begin = clock();
    auto res4 = FFTNeal::mod_multiply(al, bl, MOD, true);
    cout << "neal: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res4[a.size() / 2] << endl;
    begin = clock();
    auto res2 = ntt.multiply(a, b);
    cout << "ntt: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res2[a.size() / 2] << endl;
    begin = clock();
    auto res3 = fft.multiply(ad, bd);
    cout << "fft: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << (ll)round(res3[a.size() / 2]) % MOD << endl;
    // for (int i = 0; i < res.size(); i++) {
    //     assert(res[i] == res2[i]);
    //     assert(res[i] == ((ll)round(res3[i]) % MOD));
    // }
}