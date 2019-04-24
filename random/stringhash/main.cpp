// #pragma GCC optimize("O3")
#include <bits/stdc++.h>

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

typedef unsigned long long ull;

namespace b {
struct H {
    array<ull, 2> x;
    static const ull MOD = 1e9 + 7;
    H() : x({0, 0}) {}
    H(ull a, ull b) : x({a, b}) {}
    H norm(H a) { return H((a.x[0] + MOD) % MOD, (a.x[1] + MOD) % MOD); }
#define op(o) \
    H operator o(H a) { return norm({x[0] o a.x[0], x[1] o a.x[1]}); }
    op(+) op(-) op(*);
    H operator+(int a) { return (*this) + H(a, a); }
    bool operator==(H a) { return x == a.x; }
};

struct RollingHash {
    H p = H(29, 29);
    vector<H> ha;
    vector<H> pw;
    RollingHash(string s) : ha(s.size() + 1), pw(ha) {
        pw[0] = H(1, 1);
        for (int i = 0; i < s.size(); i++) {
            ha[i + 1] = ha[i] * p + s[i], pw[i + 1] = pw[i] * p;
            // cout << ha[i + 1].x[0] << ' ';
        }
        // cout << endl;
    }
    H interval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};
} // namespace b

namespace dacin {

template <size_t len> class Rolling_Hash_Base : public array<uint64_t, len> {
  private:
    static inline uint64_t add(uint64_t a, uint64_t b) {
        a += b + 1;
        a = (a & mod) + (a >> 61);
        return a - 1;
    }
    static inline uint64_t sub(uint64_t a, uint64_t b) { return add(a, mod - b); }
    static uint64_t modmul(uint64_t a, uint64_t b) {
        uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
        uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & mod) + (ret >> 61);
        ret = (ret & mod) + (ret >> 61);
        return ret - 1;
    }
    static const array<uint64_t, len> base;
    static array<uint64_t, len> const &get_base_pow(int exp) {
        assert(exp >= 0);
        static vector<array<uint64_t, len>> base_pow;
        if ((int)base_pow.size() <= exp) {
            if (base_pow.empty()) {
                base_pow.reserve(1001);
                base_pow.emplace_back();
                for (auto &e : base_pow.back())
                    e = 1;
            }
            for (int it = base_pow.size(); it < exp + 1000; ++it) {
                base_pow.push_back(base_pow.back());
                auto &e = base_pow.back();
                for (size_t i = 0; i < len; ++i) {
                    e[i] = modmul(e[i], base[i]);
                }
            }
        }
        return base_pow[exp];
    }

  public:
    static constexpr uint64_t mod = (1ull << 61) - 1;

    Rolling_Hash_Base() = default;
    Rolling_Hash_Base(Rolling_Hash_Base const &o) = default;
    Rolling_Hash_Base &operator=(Rolling_Hash_Base const &o) = default;

    static array<uint64_t, len> gen_base() {
        seed_seq seed{(uint32_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
                      (uint32_t)random_device()(), (uint32_t)4730921};
        mt19937 rng(seed);
        array<uint64_t, len> ret;
        for (auto &e : ret)
            e = uniform_int_distribution<uint64_t>(0, mod - 1)(rng);
        return ret;
    }
    static vector<Rolling_Hash_Base> hashify(string const &s) {
        vector<Rolling_Hash_Base> ret;
        ret.reserve(s.size());
        ret.push_back(Rolling_Hash_Base());
        // for (char const &e : s) {
        //     ret.push_back(ret.back() + e);
        // }
        return ret;
    }

    template <typename T, typename enable_if<is_integral<T>::value, int>::type = 0> Rolling_Hash_Base &operator+=(T const &o) {
        for (size_t i = 0; i < len; ++i) {
            (*this)[i] = add(modmul((*this)[i], base[i]), static_cast<uint64_t>(o));
        }
        ++length;
        return *this;
    }
    template <typename T, typename enable_if<is_integral<T>::value, int>::type = 0> Rolling_Hash_Base operator+(T const &o) const {
        Rolling_Hash_Base ret(*this);
        ret += o;
        return ret;
    }
    Rolling_Hash_Base &operator-=(Rolling_Hash_Base const &o) {
        assert(length >= o.length);
        auto const &base_pow = get_base_pow(length - o.length);
        // cerr << length << " - " << o.length << "\n";
        for (size_t i = 0; i < len; ++i) {
            (*this)[i] = sub((*this)[i], modmul(o[i], base_pow[i]));
        }
        length -= o.length;
        return *this;
    }
    Rolling_Hash_Base operator-(Rolling_Hash_Base const &o) const {
        Rolling_Hash_Base ret(*this);
        ret -= o;
        return ret;
    }

    size_t length = 0;
};
template <size_t len> const array<uint64_t, len> Rolling_Hash_Base<len>::base = Rolling_Hash_Base<len>::gen_base();

using Rolling_Hash = Rolling_Hash_Base<1>;
} // namespace dacin

// unordered_set<H> testHash;
const int MAXN = 1e5;
const int ITERS = 1e3;

struct H {
    ull x;
    H(ull x = 0) : x(x) {}
    ull get() const { return x + !~x; }
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator*(H o) {
        ull a = x >> 32, b = x & -1u, c = o.x >> 32, d = o.x & -1u;
        ull y = (H(a * d) + H(b * c)).get();
        return H(a * c) + H(b * d) + H((y >> 32) + ((y & -1u) << 32));
    }
    H operator-(H o) { return *this + ~o.x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<string> strings(ITERS);
    for (int i = 0; i < ITERS; i++) {
        for (int j = 0; j < MAXN; j++)
            strings[i].push_back((rand() & 1) ? 'a' : 'b');
    }
    vector<string> strings2(ITERS);
    for (int i = 0; i < ITERS; i++) {
        for (int j = 0; j < MAXN; j++)
            strings2[i].push_back((rand() & 1) ? 'a' : 'b');
    }
    // {
    //     int ans = 0;
    //     timeit t("extensible");
    //     for (int i = 0; i < ITERS; i++) {
    //         b::RollingHash x(strings[i]);
    //         auto l = x.interval(0, 5);
    //         auto r = x.interval(MAXN - 5, MAXN);
    //         ans = ans + (x.interval(0, 5) == x.interval(MAXN - 5, MAXN));
    //     }
    //     cout << ans << endl;
    // }
    // {
    //     int ans = 0;
    //     timeit t("dacin21");
    //     for (int i = 0; i < ITERS; i++) {
    //         dacin::Rolling_Hash hash;
    //         auto res = hash.hashify(strings[i]);
    //         ans = ans + ((res[5] - res[0]) == (res[MAXN] - res[MAXN - 5]));
    //     }
    //     cout << ans << endl;
    // }
    // {
    //     int ans = 0;
    //     timeit t("extensible");
    //     for (int i = 0; i < ITERS; i++) {
    //         b::RollingHash x(strings[i]);
    //         ans = ans + (x.interval(0, 5) == x.interval(MAXN - 5, MAXN));
    //     }
    //     cout << ans << endl;
    // }
    // {
    //     int ans = 0;
    //     timeit t("extensible");
    //     for (int i = 0; i < ITERS; i++) {
    //         b::RollingHash x(strings[i]);
    //         ans = ans + (x.interval(0, 5) == x.interval(MAXN - 5, MAXN));
    //     }
    //     cout << ans << endl;
    // }
    // {
    //     int ans = 0;
    //     timeit t("extensible");
    //     for (int i = 0; i < ITERS; i++) {
    //         b::RollingHash x(strings[i]);
    //         ans = ans + (x.interval(0, 5) == x.interval(MAXN - 5, MAXN));
    //     }
    //     cout << ans << endl;
    // }
}