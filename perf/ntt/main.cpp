// #pragma GCC optimize("O2")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
using namespace std;

typedef long long ll;
const ll LOGN = 23, MAXN = 1 << LOGN;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 9);
const ll MOD = 998244353;
const ll root = 3;

struct NTT2 {
    // For p < 2ˆ30 there is also e.g. (5 << 25, 3) , (7 << 26, 3),
    // (479 << 21, 3) and (483 << 21, 5). The last two are > 10ˆ9.
    const static ll MOD = (119 << 23) + 1, root = 3; // = 998244353
    ll binExp(ll base, ll exp) {
        if (exp == 0)
            return 1;
        return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
    }
    void ntt(ll *x, ll *temp, ll *roots, int N, int skip) {
        if (N == 1)
            return;
        int n2 = N / 2;
        ntt(x, temp, roots, n2, skip * 2);
        ntt(x + skip, temp, roots, n2, skip * 2);
        for (int i = 0; i < N; i++)
            temp[i] = x[i * skip];
        for (int i = 0; i < n2; i++) {
            ll s = temp[2 * i], t = temp[2 * i + 1] * roots[skip * i];
            x[skip * i] = (s + t) % MOD;
            x[skip * (i + n2)] = (s - t) % MOD;
        }
    }
    void ntt(vector<ll> &x, bool inv = false) {
        ll e = binExp(root, (MOD - 1) / x.size());
        if (inv)
            e = binExp(e, MOD - 2);
        vector<ll> roots(x.size(), 1), temp = roots;
        for (int i = 1; i < x.size(); i++)
            roots[i] = roots[i - 1] * e % MOD;
        ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
    }
    vector<ll> conv(vector<ll> a, vector<ll> b) {
        int s = a.size() + b.size() - 1;
        if (s <= 0)
            return {};
        int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
        if (s <= 200) {
            vector<ll> c(s);
            for (int i = 0; i < a.size(); i++)
                for (int j = 0; j < b.size(); j++)
                    c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
            return c;
        }
        a.resize(n);
        ntt(a);
        b.resize(n);
        ntt(b);
        ll d = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            a[i] = a[i] * b[i] % MOD * d % MOD;
        ntt(a, true);
        a.resize(s);
        for (auto &i : a)
            i = i < 0 ? i + MOD : i;
        return a;
    }
};
struct NTT3 {
    typedef long long ll;
    ll N, LOGN;
    vector<ll> rev;
    vector<ll> rt;
    ll mod_pow(ll a, ll p, ll m = MOD) {
        ll result = 1;
        while (p > 0) {
            if (p & 1)
                result = result * a % m;

            a = a * a % m;
            p >>= 1;
        }
        return result;
    }
    void calcRoots() {
        rev.resize(N), rt.resize(N);
        rev[0] = 0, rt[1] = 1;
        for (ll i = 0; i < N; i++)
            rev[i] = (rev[i / 2] | (i & 1) << LOGN) / 2;
        int curL = (MOD - 1) >> 2;
        for (int k = 2; k < N; k *= 2) {
            int z = mod_pow(root, curL);
            curL >>= 1;
            for (int i = k / 2; i < k; i++) {
                rt[2 * i] = rt[i], rt[2 * i + 1] = (rt[i] * z) % MOD;
            }
        }
    }
    void ntt(ll *a) {
        for (ll i = 0; i < N; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (ll k = 1; k < N; k *= 2)
            for (ll i = 0; i < N; i += 2 * k)
                for (ll j = 0; j < k; j++) {
                    ll z = (rt[j + k] * a[i + j + k]) % MOD;
                    a[i + j + k] = (a[i + j] - z + MOD) % MOD;
                    a[i + j] = (a[i + j] + z) % MOD;
                }
    }

    vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        ll s = a.size() + b.size() - 1;
        LOGN = 32 - __builtin_clz(s), N = 1 << LOGN;
        calcRoots();
        vector<ll> lft = a, rght = b;
        lft.resize(N), rght.resize(N);
        ntt(&lft[0]);
        ntt(&rght[0]);
        ll invN = mod_pow(N, MOD - 2);
        for (ll i = 0; i < N; i++)
            lft[i] = (((lft[i] * rght[i]) % MOD) * invN) % MOD;
        reverse(lft.begin() + 1, lft.begin() + N);
        ntt(&lft[0]);
        return lft;
    }
};
struct NTT4 {
    const static int MOD = 998244353;
    const static int root = 3;
    typedef long long T;
    int N, LOGN;
    vector<int> rev;
    vector<int> rt;
    inline int mul(const int a, const int b) { return (T)a * b % MOD; }
    inline int sub(const int a, const int b) { return b > a ? a - b + MOD : a - b; }
    inline int add(const int a, const int b) { return a + b >= MOD ? a + b - MOD : a + b; }
    int mod_pow(int a, T p) {
        int result = 1;
        while (p > 0) {
            if (p & 1)
                result = mul(result, a);
            a = mul(a, a);
            p >>= 1;
        }
        return result;
    }
    void calcRoots() {
        rev.resize(N), rt.resize(N);
        rev[0] = 0, rt[1] = 1;
        for (int i = 0; i < N; i++)
            rev[i] = (rev[i / 2] | (i & 1) << LOGN) / 2;
        int curL = (MOD - 1) >> 2;
        for (int k = 2; k < N; k *= 2) {
            int z = mod_pow(root, curL);
            curL >>= 1;
            for (int i = k / 2; i < k; i++) {
                rt[2 * i] = rt[i], rt[2 * i + 1] = mul(rt[i], z);
            }
        }
    }
    void ntt(int *a) {
        for (int i = 0; i < N; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < N; k *= 2)
            for (int i = 0; i < N; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    int z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }

    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        int s = a.size() + b.size() - 1;
        LOGN = 32 - __builtin_clz(s), N = 1 << LOGN;
        calcRoots();
        vector<int> lft = a, rght = b;
        lft.resize(N), rght.resize(N);
        ntt(&lft[0]);
        ntt(&rght[0]);
        int invN = mod_pow(N, MOD - 2);
        for (int i = 0; i < N; i++)
            lft[i] = mul(mul(lft[i], rght[i]), invN);
        reverse(lft.begin() + 1, lft.begin() + N);
        ntt(&lft[0]);
        return lft;
    }
};

namespace NTT5 {
const int MOD = 998244353;

inline int mod_add(int a, int b, int m = MOD) {
    int sum = a + b;
    return sum >= m ? sum - m : sum;
}

inline int mod_sub(int a, int b, int m = MOD) {
    int diff = a - b;
    return diff < 0 ? diff + m : diff;
}

inline int mod_mul(int a, int b, int m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
    return (uint64_t)a * b % m;
#endif
    // Mod multiplication optimized for Codeforces 32-bit machines.
    uint64_t x = (uint64_t)a * b;
    unsigned x_high = x >> 32, x_low = (unsigned)x;
    unsigned quot, rem;
    asm("divl %4; \n\t" : "=a"(quot), "=d"(rem) : "d"(x_high), "a"(x_low), "r"(m));
    return rem;
}

inline int mod_inv(int a, int m = MOD) {
    // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
    int g = m, r = a, x = 0, y = 1;

    while (r != 0) {
        int q = g / r;
        g %= r;
        swap(g, r);
        x -= q * y;
        swap(x, y);
    }

    assert(g == 1);
    assert(y == m || y == -m);
    return x < 0 ? x + m : x;
}

inline int mod_pow(int a, long long p, int m = MOD) {
    assert(p >= 0);
    int result = 1;

    while (p > 0) {
        if (p & 1)
            result = mod_mul(result, a, m);

        a = mod_mul(a, a, m);
        p >>= 1;
    }

    return result;
}
vector<int> roots = {0, 1};
vector<int> bit_reverse;
int max_size = -1;
int root;

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
void bit_reorder(int n, vector<int> &values) {
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

void find_root() {
    int order = MOD - 1;
    max_size = 1;

    while (order % 2 == 0) {
        order /= 2;
        max_size *= 2;
    }

    root = 2;

    // Find a max_size-th primitive root of MOD.
    while (!(mod_pow(root, max_size) == 1 && mod_pow(root, max_size / 2) != 1))
        root++;
}

void prepare_roots(int n) {
    if (max_size < 0)
        find_root();

    if ((int)roots.size() >= n)
        return;

    int length = get_length(roots.size());
    roots.resize(n);

    // The roots array is set up such that for a given power of two n >= 2, roots[n / 2] through roots[n - 1] are
    // the first half of the n-th primitive roots of MOD.
    while (1 << length < n) {
        // z is a 2^(length + 1)-th primitive root of MOD.
        int z = mod_pow(root, max_size >> (length + 1));

        for (int i = 1 << (length - 1); i < 1 << length; i++) {
            roots[2 * i] = roots[i];
            roots[2 * i + 1] = mod_mul(roots[i], z);
        }

        length++;
    }
}

void fft_iterative(int N, vector<int> &values) {
    assert(is_power_of_two(N));
    prepare_roots(N);
    bit_reorder(N, values);
    assert(N <= max_size);

    for (int n = 1; n < N; n *= 2)
        for (int start = 0; start < N; start += 2 * n)
            for (int i = 0; i < n; i++) {
                int even = values[start + i];
                int odd = mod_mul(values[start + n + i], roots[n + i]);
                values[start + n + i] = mod_sub(even, odd);
                values[start + i] = mod_add(even, odd);
            }
}

const int FFT_CUTOFF = 150;

vector<int> mod_multiply(vector<int> left, vector<int> right, bool trim = true) {
    int n = left.size();
    int m = right.size();

    for (int i = 0; i < n; i++)
        assert(0 <= left[i] && left[i] < MOD);

    for (int i = 0; i < m; i++)
        assert(0 <= right[i] && right[i] < MOD);

    // Brute force when either n or m is small enough.
    if (min(n, m) < FFT_CUTOFF) {
        const uint64_t ULL_BOUND = numeric_limits<uint64_t>::max() - (uint64_t)MOD * MOD;
        vector<uint64_t> result(n + m - 1);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                result[i + j] += (uint64_t)left[i] * right[j];

                if (result[i + j] > ULL_BOUND)
                    result[i + j] %= MOD;
            }

        for (int i = 0; i < (int)result.size(); i++)
            if (result[i] >= (uint64_t)MOD)
                result[i] %= MOD;

        if (trim) {
            while (!result.empty() && result.back() == 0)
                result.pop_back();
        }

        return vector<int>(result.begin(), result.end());
    }

    int N = round_up_power_two(n + m - 1);
    left.resize(N);
    right.resize(N);

    bool equal = left == right;
    fft_iterative(N, left);

    if (equal)
        right = left;
    else
        fft_iterative(N, right);

    int inv_N = mod_inv(N);

    for (int i = 0; i < N; i++)
        left[i] = mod_mul(mod_mul(left[i], right[i]), inv_N);

    reverse(left.begin() + 1, left.end());
    fft_iterative(N, left);
    left.resize(n + m - 1);

    if (trim) {
        while (!left.empty() && left.back() == 0)
            left.pop_back();
    }

    return left;
}

vector<int> power(const vector<int> &v, int exponent) {
    assert(exponent >= 0);
    vector<int> result = {1};

    if (exponent == 0)
        return result;

    for (int k = 31 - __builtin_clz(exponent); k >= 0; k--) {
        result = mod_multiply(result, result);

        if (exponent & 1 << k)
            result = mod_multiply(result, v);
    }

    return result;
}
}; // namespace NTT5

struct NTT6 {
    const static int M = 998244353, G = 3;
    ll pm(ll b, int p) {
        ll r = 1;
        while (p) {
            if (p & 1)
                r = r * b % M;
            b = b * b % M;
            p /= 2;
        }
        return r;
    }
    void ntt(vector<ll> &a, bool iv) {
        int n = a.size();
        for (int i = 0, j = 0; i < n; ++i) {
            if (i > j)
                swap(a[i], a[j]);
            for (int k = n / 2; (j ^= k) < k; k /= 2)
                ;
        }
        for (int st = 1, id = 1; 2 * st <= n; st *= 2, ++id) {
            ll wn = pm(G, iv ? (M - 1 - (M - 1 >> id)) : (M - 1 >> id));
            for (int i = 0; i < n; i += 2 * st) {
                ll wi = 1;
                for (int j = i; j < i + st; ++j, wi = wi * wn % M) {
                    ll u = a[j], v = wi * a[j + st] % M;
                    a[j] = u + v;
                    if (a[j] >= M)
                        a[j] -= M;
                    a[j + st] = u - v;
                    if (a[j + st] < 0)
                        a[j + st] += M;
                }
            }
        }
        if (iv) {
            ll in = pm(n, M - 2);
            for (int i = 0; i < n; ++i)
                a[i] = a[i] * in % M;
        }
    }
    vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        int s = a.size() + b.size() - 1;
        int logn = 32 - __builtin_clz(s), n = 1 << logn;
        vector<ll> lft(n), rght(n);
        copy(a.begin(), a.end(), lft.begin()), copy(b.begin(), b.end(), rght.begin());
        ntt(lft, false);
        ntt(rght, false);
        int invN = pm(n, MOD - 2);
        for (int i = 0; i < n; i++)
            lft[i] = lft[i] * rght[i] % MOD;
        ntt(lft, true);
        return lft;
    }
};
template <int maxn> struct NTT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    const static int MOD = 998244353;
    const static int root = 62;
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

NTT<MAXN> ntt1;
NTT2 ntt2;
NTT3 ntt3;
NTT4 ntt4;
NTT6 ntt6;
vector<int> a, b;
vector<ll> al, bl;
const int RANDOM =
    (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();

signed main() {
    srand(RANDOM);
    clock_t begin;
    vector<int> res;
    // for (int _t = 0; _t < 100; _t++) {

    //     for (int i = 0; i < 30; i++) {
    //         a.push_back(uni(rng)), b.push_back(uni(rng));
    //         al.push_back(a.back()), bl.push_back(b.back());
    //     }
    //     a.resize(rand() % 10);
    //     b.resize(rand() % 10);
    //     cout << "size: " << a.size() << ' ' << b.size() << endl;
    //     vector<ll> resl;

    //     begin = clock();
    //     auto resM = ntt1.multiply(a, b);
    //     cout << "custom: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << resM.size() << endl;

    //     begin = clock();
    //     res = NTT5::mod_multiply(a, b);
    //     cout << "neal: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res.size() << endl;

    //     for (int i = 0; i < res.size(); i++) {
    //         cout << res[i] << ' ' << resM[i] << endl;
    //         assert(resM[i] == res[i]);
    //     }
    // }
    for (int i = 0; i < MAXN / 2; i++) {
        a.push_back(uni(rng)), b.push_back(uni(rng));
        al.push_back(a.back()), bl.push_back(b.back());
    }
    begin = clock();
    res = NTT5::mod_multiply(a, b);
    cout << "neal: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res.size() << endl;

    begin = clock();
    auto resM = ntt1.multiply(a, b);
    cout << "custom: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << resM.size() << endl;

    // begin = clock();
    // resl = ntt3.multiply(al, bl);
    // cout << "old custom: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << resl[a.size() / 2] << endl;

    // begin = clock();
    // resl = ntt2.conv(al, bl);
    // cout << "kactl: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << resl[a.size() / 2] << endl;

    // begin = clock();
    // res = ntt4.multiply(a, b);
    // cout << "optimized custom: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << res[a.size() / 2] << endl;

    // begin = clock();
    // resl = ntt6.multiply(al, bl);
    // cout << "william: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << resl[a.size() / 2] << endl;
}
