#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef complex<double> cpx;
typedef complex<double> cd;
const int LOGN = 21, MAXN = 1 << LOGN;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 10);

// Emaxx's FFT
struct FFT1 {
    int breverse(int num, int lg_n) {
        int res = 0;
        for (int i = 0; i < lg_n; i++) {
            if (num & (1 << i))
                res |= 1 << (lg_n - 1 - i);
        }
        return res;
    }

    void emxfft(cd *a, bool invert) {
        // int n = a.size();
        int n = MAXN;
        int lg_n = LOGN;

        for (int i = 0; i < n; i++) {
            if (i < breverse(i, lg_n))
                swap(a[i], a[breverse(i, lg_n)]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * M_PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (int i = 0; i < MAXN; i++)
                a[i] /= MAXN;
        }
    }
    void emxMultiply(cd *a, cd *b) {
        emxfft(a, false), emxfft(b, false);
        for (int i = 0; i < MAXN; i++)
            a[i] *= b[i] / (double)MAXN;
        reverse(a + 1, a + MAXN);
        emxfft(a, false);
    }
};

// KACTL's FFT
struct FFT2 {
    int rev[MAXN];
    cpx rt[MAXN];
    FFT2() {
        rev[0] = 0;
        rt[1] = cpx(1, 0);
        for (int i = 0; i < MAXN; i++)
            rev[i] = (rev[i / 2] | (i & 1) << LOGN) / 2;
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z(cos(M_PI / k), sin(M_PI / k));
            for (int i = k / 2; i < k; i++)
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
                    cpx z = rt[j + k] * a[i + j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
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

// KACTL FFT + custom complex
struct FFT3 {
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

    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFT3() {
        rev[0] = 0;
        rt[1] = cpx(1, 0);
        for (int i = 0; i < MAXN; i++)
            rev[i] = (rev[i / 2] | (i & 1) << LOGN) / 2;
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z(cos(M_PI / k), sin(M_PI / k));
            for (int i = k / 2; i < k; i++)
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
                    cpx z = rt[j + k] * a[i + j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }

    void multiply(cpx *a, cpx *b) {
        fft(a), fft(b);
        for (int i = 0; i < MAXN; i++)
            a[i] = a[i] * b[i] / (double)MAXN;
        reverse(a + 1, a + MAXN);
        fft(a);
    }
};

// Neal Wu's FFT
namespace FFT4 {
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
} // namespace FFT4

// tfg
struct FFT6 {
    typedef double ld;

    FFT6() { initFFT(); }

    const ld PI = acos(-1);

    struct Complex {
        ld real, imag;
        Complex conj() { return Complex(real, -imag); }
        Complex(ld a = 0, ld b = 0) : real(a), imag(b) {}
        Complex operator+(const Complex &o) const { return Complex(real + o.real, imag + o.imag); }
        Complex operator-(const Complex &o) const { return Complex(real - o.real, imag - o.imag); }
        Complex operator*(const Complex &o) const { return Complex(real * o.real - imag * o.imag, real * o.imag + imag * o.real); }
        Complex operator/(ld o) const { return Complex(real / o, imag / o); }
        void operator*=(Complex o) { *this = *this * o; }
        void operator/=(ld o) { real /= o, imag /= o; }
    };

    typedef std::vector<Complex> CVector;

    int bits[MAXN];
    Complex root[MAXN];

    void initFFT() {
        root[1] = Complex(1);
        for (int len = 2; len < MAXN; len += len) {
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

    std::vector<long long> mod_mul(const std::vector<long long> &a, const std::vector<long long> &b, long long cut = 1 << 15) {
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
};

// TankEngineer's FFT
// struct FFT7 {
//     const int MOD = 1000003;
//     const double PI = acos(-1);
//     typedef complex<double> Complex;
//     const static int N = MAXN, L = LOGN, MASK = (1 << L) - 1;
//     Complex w[N];
//     void FFTInit() {
//         for (int i = 0; i < N; ++i) {
//             w[i] = Complex(cos(2 * i * PI / N), sin(2 * i * PI / N));
//         }
//     }
//     void FFT(Complex p[], int n) {
//         for (int i = 1, j = 0; i < n - 1; ++i) {
//             for (int s = n; j ^= s >>= 1, ~j & s;)
//                 ;
//             if (i < j) {
//                 swap(p[i], p[j]);
//             }
//         }
//         for (int d = 0; (1 << d) < n; ++d) {
//             int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
//             for (int i = 0; i < n; i += m2) {
//                 for (int j = 0; j < m; ++j) {
//                     Complex &p1 = p[i + j + m], &p2 = p[i + j];
//                     Complex t = w[rm * j] * p1;
//                     p1 = p2 - t;
//                     p2 = p2 + t;
//                 }
//             }
//         }
//     }
//     Complex A[N], B[N], C[N], D[N];
//     void mul(int a[N], int b[N]) {
//         for (int i = 0; i < N; ++i) {
//             A[i] = Complex(a[i] >> L, a[i] & MASK);
//             B[i] = Complex(b[i] >> L, b[i] & MASK);
//         }
//         FFT(A, N), FFT(B, N);
//         for (int i = 0; i < N; ++i) {
//             int j = (N - i) % N;
//             Complex da = (A[i] - conj(A[j])) * Complex(0, -0.5), db = (A[i] + conj(A[j])) * Complex(0.5, 0),
//                     dc = (B[i] - conj(B[j])) * Complex(0, -0.5), dd = (B[i] + conj(B[j])) * Complex(0.5, 0);
//             C[j] = da * dd + da * dc * Complex(0, 1);
//             D[j] = db * dd + db * dc * Complex(0, 1);
//         }
//         FFT(C, N), FFT(D, N);
//         for (int i = 0; i < N; ++i) {
//             long long da = (long long)(C[i].imag() / N + 0.5) % MOD, db = (long long)(C[i].real() / N + 0.5) % MOD,
//                       dc = (long long)(D[i].imag() / N + 0.5) % MOD, dd = (long long)(D[i].real() / N + 0.5) % MOD;
//             a[i] = ((dd << (L * 2)) + ((db + dc) << L) + da) % MOD;
//         }
//     }
// };

// Tmwilliamlin168
namespace FFT8 {
template <typename T> struct cp {
    T x, y;
    cp<T> operator+(const cp &o) const { return {x + o.x, y + o.y}; }
    cp<T> operator*(const cp &o) const { return {x * o.x - y * o.y, x * o.y + y * o.x}; }
};
template <typename T> struct fft {
    static const int mxN = MAXN;
    cp<T> rt[mxN];
    void fi(int n) {
        T PI = acos((T)-1);
        for (int i = 0; i < n / 2; ++i) {
            T an = 2 * PI * i / n;
            rt[i + n / 2] = {cos(an), sin(an)};
        }
        for (int i = n / 2; --i >= 1;)
            rt[i] = rt[2 * i];
    }
    void ac(vector<cp<T>> &a) {
        int n = a.size();
        for (int i = 0, j = 0; i < n; ++i) {
            if (i > j)
                swap(a[i], a[j]);
            for (int k = n / 2; (j ^= k) < k; k /= 2)
                ;
        }
        for (int st = 1; 2 * st <= n; st *= 2) {
            for (int i = 0; i < n; i += 2 * st) {
                for (int j = i; j < i + st; ++j) {
                    cp<T> z = rt[j - i + st] * a[j + st];
                    a[j + st] = a[j] + cp<T>{-1, 0} * z;
                    a[j] = a[j] + z;
                }
            }
        }
    }
    void mul(vector<cp<T>> &g, vector<cp<T>> &h) {
        int n = g.size();
        ac(g);
        for (int i = 0; i < n; ++i) {
            int j = (n - i) & (n - 1);
            cp<T> g2 = g[i] * g[i];
            g2.x = -g2.x;
            h[i] = (g[j] * g[j] + g2) * cp<T>{(T)0, (T)-1 / 4 / n};
        }
        ac(h);
    }
};
} // namespace FFT8

struct FFT9 {
    typedef valarray<complex<double>> carray;
    // typedef vector<double> vd;
    void fft(carray &x, carray &roots) {
        int N = x.size();
        if (N <= 1)
            return;
        carray even = x[slice(0, N / 2, 2)];
        carray odd = x[slice(1, N / 2, 2)];
        carray rs = roots[slice(0, N / 2, 2)];
        fft(even, rs);
        fft(odd, rs);
        for (int k = 0; k < N / 2; k++) {
            auto t = roots[k] * odd[k];
            x[k] = even[k] + t;
            x[k + N / 2] = even[k] - t;
        }
    }

    typedef vector<double> vd;
    vd conv(const vd &a, const vd &b) {
        int s = a.size() + b.size() - 1, L = 32 - __builtin_clz(s), n = 1 << L;
        if (s <= 0)
            return {};
        carray av(n), bv(n), roots(n);
        for (int i = 0; i < n; i++)
            roots[i] = polar(1.0, -2 * M_PI * i / n);
        copy(a.begin(), a.end(), begin(av));
        fft(av, roots);
        copy(b.begin(), b.end(), begin(bv));
        fft(bv, roots);
        roots = roots.apply(conj);
        carray cv = av * bv;
        fft(cv, roots);
        vd c(s);
        for (int i = 0; i < s; i++)
            c[i] = cv[i].real() / n;
        return c;
    }
};

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

FFT1 *fft1;
FFT2 fft2;
FFT3 fft3;
FFT<MAXN> fft5;
FFT6 fft6;
// FFT7 fft7;
FFT8::fft<double> fft8;
FFT9 fft9;
cpx A[MAXN], B[MAXN];
FFT3::complex<double> cA[MAXN], cB[MAXN];
vector<FFT8::cp<double>> c8A, c8B;
vector<double> vcA, vcB;
vector<int> Ao, Bo, viA, viB;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAXN / 2; i++) {
        Ao.push_back(uni(rng));
        Bo.push_back(uni(rng));
        // Ao.push_back(1), Bo.push_back(1);
    }
    vector<double> res;
    clock_t begin;
    /** EMaxx **/
    begin = clock();
    for (int i = 0; i < Ao.size(); i++) {
        A[i] = Ao[i], B[i] = Bo[i];
    }
    fft1->emxMultiply(A, B);
    cout << "emaxx: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << A[Ao.size() / 2] << endl;
    /** ----------- **/
    /** TankEngineer **/
    // viA.clear(), viB.clear();
    // for (int i = 0; i < Ao.size(); i++) {
    //     viA.push_back(Ao[i]), viB.push_back(Bo[i]);
    // }
    // viA.resize(MAXN, 0), viB.resize(MAXN, 0);
    // fft7.FFTInit();
    // begin = clock();
    // fft7.mul(&viA[0], &viB[0]);
    // cout << "TankEngineer: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << viA[Ao.size() / 2] << endl;
    /** ----------- **/

    /** KACTL Custom **/
    // fill(cA, cA + MAXN, 0), fill(cB, cB + MAXN, 0);
    // for (int i = 0; i < Ao.size(); i++) {
    //     cA[i] = Ao[i], cB[i] = Bo[i];
    // }
    // begin = clock();
    // fft3.multiply(cA, cB);
    // cout << "kactl custom: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << cA[Ao.size() / 2].x << endl;
    /** ----------- **/

    /** tmwilliamlin168 **/
    c8A.clear(), c8B.clear();
    for (int i = 0; i < Ao.size(); i++) {
        c8A.push_back({Ao[i], Bo[i]});
        // c8B.push_back({Bo[i], 0});
    }
    c8A.resize(MAXN, {0, 0}), c8B.resize(MAXN, {0, 0});
    begin = clock();
    fft8.fi(MAXN);
    fft8.mul(c8A, c8B);
    cout << "tmwilliamlin168: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << c8B[Ao.size() / 2].x << endl;
    /** ----------- **/

    /** KACTL 2-in-1 **/
    vcA.clear(), vcB.clear();
    for (int i = 0; i < Ao.size(); i++) {
        vcA.push_back(Ao[i]), vcB.push_back(Bo[i]);
    }
    // fft5.N = MAXN, fft5.LOGN = LOGN;
    // fft5.calcRoots();
    begin = clock();
    // res = fft5.multiply(vcA, vcB);
    res = fft5.multiply(vcA, vcB);
    cout << "2-in-1: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[Ao.size() / 2] << endl;
    /** ----------- **/

    /** Neal **/
    vcA.clear(), vcB.clear();
    for (int i = 0; i < Ao.size(); i++) {
        vcA.push_back(Ao[i]), vcB.push_back(Bo[i]);
    }
    begin = clock();
    res = FFT4::multiply<double, double>(vcA, vcB);
    cout << "neal: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[Ao.size() / 2] << endl;
    /** ----------- **/
    /** KACTL **/
    // fill(A, A + MAXN, 0);
    // fill(B, B + MAXN, 0);
    // for (int i = 0; i < Ao.size(); i++) {
    //     A[i] = Ao[i], B[i] = Bo[i];
    // }
    // begin = clock();
    // fft2.multiply(A, B);
    // cout << "kactl: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << A[Ao.size() / 2] << endl;
    /** ----------- **/
    /** tfg **/
    // viA.clear(), viB.clear();
    // for (int i = 0; i < Ao.size(); i++) {
    //     viA.push_back(Ao[i]), viB.push_back(Bo[i]);
    // }
    // begin = clock();
    // auto restfg = fft6.mul(viA, viB);
    // cout << "tfg: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << restfg[Ao.size() / 2] << endl;
    /** ----------- **/
    /** KACTL orig **/
    // vcA.clear(), vcB.clear();
    // for (int i = 0; i < Ao.size(); i++) {
    //     vcA.push_back(Ao[i]), vcB.push_back(Bo[i]);
    // }
    // begin = clock();
    // res = fft9.conv(vcA, vcB);
    // cout << "kactl orig: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[Ao.size() / 2] << endl;
    /** ----------- **/
}