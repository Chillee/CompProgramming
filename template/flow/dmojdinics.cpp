#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace std::placeholders;
using namespace __gnu_pbds;
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define f first
#define s second
#define all(a) (a).begin(), (a).end()
#define For(i, a, b) for (auto i = (a); i < (b); i++)
#define FOR(i, b) For(i, 0, b)
#define Rev(i, a, b) for (auto i = (a); i > (b); i--)
#define REV(i, a) Rev(i, a, -1)
#define FORE(i, a) for (auto &&i : a)
template <class C> constexpr int sz(const C &c) { return int(c.size()); }
using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pill = pair<int, ll>;
using plli = pair<ll, int>;
using pdd = pair<double, double>;
using pld = pair<ld, ld>;
constexpr const char nl = '\n', sp = ' ';
constexpr const int INT_INF = 0x3f3f3f3f;
constexpr const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
constexpr const double D_INF = numeric_limits<double>::infinity();
constexpr const ld LD_INF = numeric_limits<ld>::infinity();
template <class T> constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template <class T> constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template <class T, class... Ts> constexpr const T &_min(const T &x, const Ts &... xs) { return _min(x, _min(xs...)); }
template <class T, class... Ts> constexpr const T &_max(const T &x, const Ts &... xs) { return _max(x, _max(xs...)); }
template <class T, class... Ts> void MIN(T &x, const Ts &... xs) { x = _min(x, xs...); }
template <class T, class... Ts> void MAX(T &x, const Ts &... xs) { x = _max(x, xs...); }
template <class T> constexpr const T &_clamp(const T &v, const T &lo, const T &hi) { return v < lo ? lo : hi < v ? hi : v; }
template <class T> void CLAMP(T &v, const T &lo, const T &hi) { v = _clamp(v, lo, hi); }
template <class T, class... Args> unique_ptr<T> _make_unique(Args &&... args) { return unique_ptr<T>(new T(forward<Args>(args)...)); }
template <class T, class... Args> shared_ptr<T> _make_shared(Args &&... args) { return shared_ptr<T>(new T(forward<Args>(args)...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define clamp(...) _clamp(__VA_ARGS__)
#define make_unique _make_unique
#define make_shared _make_shared
seed_seq seq{(uint64_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
             (uint64_t)__builtin_ia32_rdtsc(), (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);
mt19937_64 rng64(seq);
const size_t RANDOM = uniform_int_distribution<size_t>(0, (numeric_limits<size_t>::max)())(rng64);
template <class T, class H = hash<T>> struct rand_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(const T &x) const { return splitmix64(H{}(x) + RANDOM); }
};
template <class K, class H = rand_hash<K>, class... Ts> using hashset = gp_hash_table<K, null_type, H, Ts...>;
template <class K, class V, class H = rand_hash<K>, class... Ts> using hashmap = gp_hash_table<K, V, H, Ts...>;
template <class K, class C = less<K>, class... Ts> using treeset = tree<K, null_type, C, rb_tree_tag, tree_order_statistics_node_update, Ts...>;
template <class K, class V, class C = less<K>, class... Ts> using treemap = tree<K, V, C, rb_tree_tag, tree_order_statistics_node_update, Ts...>;
template <class K, class H = rand_hash<K>, class... Ts> using uset = unordered_set<K, H, Ts...>;
template <class K, class V, class H = rand_hash<K>, class... Ts> using umap = unordered_map<K, V, H, Ts...>;
template <class T> using minpq = std::priority_queue<T, vector<T>, greater<T>>;
template <class T> using maxpq = std::priority_queue<T, vector<T>, less<T>>;
template <class T> using minpairingheap = __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag>;
template <class T> using maxpairingheap = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
template <class T1, class T2, class H1 = rand_hash<T1>, class H2 = rand_hash<T2>> struct pair_hash {
    size_t operator()(const pair<T1, T2> &p) const { return 31 * H1{}(p.first) + H2{}(p.second); }
};
template <class T> struct is_iterator {
    template <class U, typename enable_if<!is_convertible<U, const char *>::value, int>::type = 0>
    constexpr static auto has_indirection(int) -> decltype(*declval<U>(), bool()) {
        return true;
    }
    template <class> constexpr static bool has_indirection(long) { return false; }
    constexpr static bool value = has_indirection<T>(0);
};

#define INTERACTIVE_INPUT 0
constexpr const int _bufferSize = 1 << 16, _maxNumLength = 128;
char _inputBuffer[_bufferSize + 1], *_inputPtr = _inputBuffer, _outputBuffer[_bufferSize], _c, _sign, *_tempInputBuf = nullptr,
                                    _numBuf[_maxNumLength], _tempOutputBuf[_maxNumLength], _fill = ' ';
FILE *_input = stdin, *_output = stdout, *_error = stderr;
const char *_delimiter = " ";
int _cur, _outputPtr = 0, _numPtr = 0, _precision = 6, _width = 0, _tempOutputPtr = 0, _cnt;
ull _precisionBase = 1000000;
#ifdef _WIN32
#define getchar_unlocked getchar
#define fread_unlocked fread
#define fwrite_unlocked fwrite
#endif
#if INTERACTIVE_INPUT
#define _getchar() getchar_unlocked()
#else
#define _peekchar() (*_inputPtr ? *_inputPtr : (_inputBuffer[fread_unlocked(_inputPtr = _inputBuffer, 1, _bufferSize, _input)] = '\0', *_inputPtr))
#define _getchar() (*_inputPtr ? *_inputPtr++ : (_inputBuffer[fread_unlocked(_inputPtr = _inputBuffer, 1, _bufferSize, _input)] = '\0', *_inputPtr++))
#define _hasNext() (*_inputPtr || !feof(_input))
bool hasNext() {
    while (_hasNext() && _peekchar() <= ' ')
        _getchar();
    return _hasNext();
}
bool hasNextLine() {
    while (_hasNext() && _peekchar() == '\r')
        _getchar();
    return _hasNext();
}
#endif
#define _readSignAndNum(x)                                                                                                                           \
    do {                                                                                                                                             \
        (x) = _getchar();                                                                                                                            \
    } while ((x) <= ' ');                                                                                                                            \
    _sign = (x) == '-';                                                                                                                              \
    if (_sign)                                                                                                                                       \
        (x) = _getchar();                                                                                                                            \
    for ((x) -= '0'; (_c = _getchar()) >= '0'; (x) = (x)*10 + _c - '0')
#define _readFloatingPoint(x, T) for (T _div = 1.0; (_c = _getchar()) >= '0'; (x) += (_c - '0') / (_div *= 10))
#define rc(x)                                                                                                                                        \
    do {                                                                                                                                             \
        do {                                                                                                                                         \
            (x) = _getchar();                                                                                                                        \
        } while ((x) <= ' ');                                                                                                                        \
    } while (0)
#define ri(x)                                                                                                                                        \
    do {                                                                                                                                             \
        _readSignAndNum(x);                                                                                                                          \
        if (_sign)                                                                                                                                   \
            (x) = -(x);                                                                                                                              \
    } while (0)
#define rd(x)                                                                                                                                        \
    do {                                                                                                                                             \
        _readSignAndNum(x);                                                                                                                          \
        if (_c == '.')                                                                                                                               \
            _readFloatingPoint(x, double);                                                                                                           \
        if (_sign)                                                                                                                                   \
            (x) = -(x);                                                                                                                              \
    } while (0)
#define rld(x)                                                                                                                                       \
    do {                                                                                                                                             \
        _readSignAndNum(x);                                                                                                                          \
        if (_c == '.')                                                                                                                               \
            _readFloatingPoint(x, ld);                                                                                                               \
        if (_sign)                                                                                                                                   \
            (x) = -(x);                                                                                                                              \
    } while (0)
#define rcs(x)                                                                                                                                       \
    do {                                                                                                                                             \
        _cur = 0;                                                                                                                                    \
        do {                                                                                                                                         \
            _c = _getchar();                                                                                                                         \
        } while (_c <= ' ');                                                                                                                         \
        do {                                                                                                                                         \
            (x)[_cur++] = _c;                                                                                                                        \
        } while ((_c = _getchar()) > ' ');                                                                                                           \
        (x)[_cur] = '\0';                                                                                                                            \
    } while (0)
#define rs(x)                                                                                                                                        \
    do {                                                                                                                                             \
        if (!_tempInputBuf)                                                                                                                          \
            assert(0);                                                                                                                               \
        rcs(_tempInputBuf);                                                                                                                          \
        (x) = string(_tempInputBuf, _cur);                                                                                                           \
    } while (0)
#define rcln(x)                                                                                                                                      \
    do {                                                                                                                                             \
        while (_inputPtr != _inputBuffer && *(_inputPtr - 1) == '\r')                                                                                \
            _getchar();                                                                                                                              \
        _cur = 0;                                                                                                                                    \
        while ((_c = _getchar()) != '\n' && _c) {                                                                                                    \
            if (_c != '\r')                                                                                                                          \
                (x)[_cur++] = _c;                                                                                                                    \
        }                                                                                                                                            \
        (x)[_cur] = '\0';                                                                                                                            \
    } while (0)
#define rln(x)                                                                                                                                       \
    do {                                                                                                                                             \
        if (!_tempInputBuf)                                                                                                                          \
            assert(0);                                                                                                                               \
        rcln(_tempInputBuf);                                                                                                                         \
        (x) = string(_tempInputBuf, _cur);                                                                                                           \
    } while (0)
void setLength(int x) {
    if (_tempInputBuf)
        delete[](_tempInputBuf);
    _tempInputBuf = new char[x + 1];
}
void read(int &x) { ri(x); }
void read(uint &x) { ri(x); }
void read(ll &x) { ri(x); }
void read(ull &x) { ri(x); }
void read(double &x) { rd(x); }
void read(ld &x) { rld(x); }
void read(char &x) { rc(x); }
void read(char *x) { rcs(x); }
void read(string &x) { rs(x); }
void readln(char *x) { rcln(x); }
void readln(string &x) { rln(x); }
template <class T1, class T2> void read(pair<T1, T2> &x) {
    read(x.first);
    read(x.second);
}
template <class T> void read(complex<T> &x) {
    T _re, _im;
    read(_re);
    read(_im);
    x.real(_re);
    x.imag(_im);
}
template <class T> void read(T &x);
template <class T, class... Ts> void read(T &x, Ts &&... xs);
template <class It> typename enable_if<is_iterator<It>::value>::type read(It st, It en) {
    for (It _i = st; _i != en; _i++)
        read(*_i);
}
template <class It, class... Ts> typename enable_if<is_iterator<It>::value>::type read(It st, It en, Ts &&... xs) {
    read(st, en);
    read(forward<Ts>(xs)...);
}
template <class T> void read(T &x) {
    for (auto &&_i : x)
        read(_i);
}
template <class T, class... Ts> void read(T &x, Ts &&... xs) {
    read(x);
    read(forward<Ts>(xs)...);
}
void setInput(FILE *file) {
    *_inputPtr = '\0';
    _input = file;
}
void setInput(const char *s) {
    *_inputPtr = '\0';
    _input = fopen(s, "r");
}
void setInput(const string &s) {
    *_inputPtr = '\0';
    _input = fopen(s.c_str(), "r");
}
#define _flush()                                                                                                                                     \
    do {                                                                                                                                             \
        _flushBuf();                                                                                                                                 \
        fflush(_output);                                                                                                                             \
    } while (0)
#define _flushBuf() (fwrite_unlocked(_outputBuffer, 1, _outputPtr, _output), _outputPtr = 0)
#define _putchar(x) (_outputBuffer[_outputPtr == _bufferSize ? _flushBuf() : _outputPtr] = (x), _outputPtr++)
#define _writeTempBuf(x) (_tempOutputBuf[_tempOutputPtr++] = (x))
#define _writeOutput()                                                                                                                               \
    for (int _i = 0; _i < _tempOutputPtr; _putchar(_tempOutputBuf[_i++]))                                                                            \
        ;                                                                                                                                            \
    _tempOutputPtr = 0
#define _writeNum(x, T, digits)                                                                                                                      \
    _cnt = 0;                                                                                                                                        \
    for (T _y = (x); _y; _y /= 10, _cnt++)                                                                                                           \
        _numBuf[_numPtr++] = '0' + _y % 10;                                                                                                          \
    for (; _cnt < digits; _cnt++)                                                                                                                    \
        _numBuf[_numPtr++] = '0';                                                                                                                    \
    _flushNumBuf();
#define _writeFloatingPoint(x, T)                                                                                                                    \
    ull _I = (ull)(x);                                                                                                                               \
    ull _F = ((x)-_I) * _precisionBase + (T)(0.5);                                                                                                   \
    if (_F >= _precisionBase) {                                                                                                                      \
        _I++;                                                                                                                                        \
        _F = 0;                                                                                                                                      \
    }                                                                                                                                                \
    _writeNum(_I, ull, 1);                                                                                                                           \
    _writeTempBuf('.');                                                                                                                              \
    _writeNum(_F, ull, _precision)
#define _checkFinite(x)                                                                                                                              \
    if (std::isnan(x)) {                                                                                                                             \
        wcs("NaN");                                                                                                                                  \
    } else if (std::isinf(x)) {                                                                                                                      \
        wcs("Inf");                                                                                                                                  \
    }
#define _flushNumBuf() for (; _numPtr; _writeTempBuf(_numBuf[--_numPtr]))
#define _fillBuf(x)                                                                                                                                  \
    for (int _i = 0; _i < (x); _i++)                                                                                                                 \
    _putchar(_fill)
#define _flushTempBuf()                                                                                                                              \
    int _tempLen = _tempOutputPtr;                                                                                                                   \
    _fillBuf(_width - _tempLen);                                                                                                                     \
    _writeOutput();                                                                                                                                  \
    _fillBuf(-_width - _tempLen)
#define wb(x)                                                                                                                                        \
    do {                                                                                                                                             \
        if (x)                                                                                                                                       \
            _writeTempBuf('1');                                                                                                                      \
        else                                                                                                                                         \
            _writeTempBuf('0');                                                                                                                      \
        _flushTempBuf();                                                                                                                             \
    } while (0)
#define wc(x)                                                                                                                                        \
    do {                                                                                                                                             \
        _writeTempBuf(x);                                                                                                                            \
        _flushTempBuf();                                                                                                                             \
    } while (0)
#define wi(x)                                                                                                                                        \
    do {                                                                                                                                             \
        if ((x) < 0) {                                                                                                                               \
            _writeTempBuf('-');                                                                                                                      \
            _writeNum(-(x), uint, 1);                                                                                                                \
        } else {                                                                                                                                     \
            _writeNum(x, uint, 1);                                                                                                                   \
        }                                                                                                                                            \
        _flushTempBuf();                                                                                                                             \
    } while (0)
#define wll(x)                                                                                                                                       \
    do {                                                                                                                                             \
        if ((x) < 0) {                                                                                                                               \
            _writeTempBuf('-');                                                                                                                      \
            _writeNum(-(x), ull, 1);                                                                                                                 \
        } else {                                                                                                                                     \
            _writeNum(x, ull, 1);                                                                                                                    \
        }                                                                                                                                            \
        _flushTempBuf();                                                                                                                             \
    } while (0)
#define wd(x)                                                                                                                                        \
    do {                                                                                                                                             \
        _checkFinite(x) else if ((x) < 0) {                                                                                                          \
            _writeTempBuf('-');                                                                                                                      \
            _writeFloatingPoint(-(x), double);                                                                                                       \
        }                                                                                                                                            \
        else {                                                                                                                                       \
            _writeFloatingPoint(x, double);                                                                                                          \
        }                                                                                                                                            \
        _flushTempBuf();                                                                                                                             \
    } while (0)
#define wld(x)                                                                                                                                       \
    do {                                                                                                                                             \
        _checkFinite(x) else if ((x) < 0) {                                                                                                          \
            _writeTempBuf('-');                                                                                                                      \
            _writeFloatingPoint(-(x), ld);                                                                                                           \
        }                                                                                                                                            \
        else {                                                                                                                                       \
            _writeFloatingPoint(x, ld);                                                                                                              \
        }                                                                                                                                            \
        _flushTempBuf();                                                                                                                             \
    } while (0)
#define wcs(x)                                                                                                                                       \
    do {                                                                                                                                             \
        int _slen = strlen(x);                                                                                                                       \
        _fillBuf(_width - _slen);                                                                                                                    \
        for (const char *_p = (x); *_p; _putchar(*_p++))                                                                                             \
            ;                                                                                                                                        \
        _fillBuf(-_width - _slen);                                                                                                                   \
    } while (0)
#define ws(x)                                                                                                                                        \
    do {                                                                                                                                             \
        _fillBuf(_width - int((x).length()));                                                                                                        \
        for (int _i = 0; _i < int((x).length()); _putchar(x[_i++]))                                                                                  \
            ;                                                                                                                                        \
        _fillBuf(-_width - int((x).length()));                                                                                                       \
    } while (0)
void setPrecision(int x) {
    _precision = x;
    _precisionBase = 1;
    for (int _i = 0; _i < x; _i++, _precisionBase *= 10)
        ;
}
void setWidth(int x) { _width = x; }
void setFill(char x) { _fill = x; }
void setDelimiter(const char *x) { _delimiter = x; }
void setDelimiter(const string &x) { _delimiter = x.c_str(); }
void writeDelimiter() {
    for (const char *_p = _delimiter; *_p; _putchar(*_p++))
        ;
}
void write(const bool &x) { wb(x); }
void write(const int &x) { wi(x); }
void write(const uint &x) { wi(x); }
void write(const ll &x) { wll(x); }
void write(const ull &x) { wll(x); }
void write(const double &x) { wd(x); }
void write(const ld &x) { wld(x); }
void write(const char &x) { wc(x); }
void write(const char *x) { wcs(x); }
void write(const string &x) { ws(x); }
template <class T1, class T2> void write(const pair<T1, T2> &x) {
    write(x.first);
    writeDelimiter();
    write(x.second);
}
template <class T> void write(const complex<T> &x) {
    write(x.real());
    writeDelimiter();
    write(x.imag());
}
template <class T> void write(const T &x);
template <class T, class... Ts> void write(const T &x, Ts &&... xs);
template <class It> typename enable_if<is_iterator<It>::value>::type write(It st, It en) {
    bool _first = 1;
    for (It _i = st; _i != en; _i++) {
        if (_first)
            _first = 0;
        else
            writeDelimiter();
        write(*_i);
    }
}
template <class It, class... Ts> typename enable_if<is_iterator<It>::value>::type write(It st, It en, Ts &&... xs) {
    write(st, en);
    writeDelimiter();
    write(forward<Ts>(xs)...);
}
template <class T> void write(const T &x) {
    bool _first = 1;
    for (auto &&_i : x) {
        if (_first)
            _first = 0;
        else
            writeDelimiter();
        write(_i);
    }
}
template <class T, class... Ts> void write(const T &x, Ts &&... xs) {
    write(x);
    writeDelimiter();
    write(forward<Ts>(xs)...);
}
void writeln() { _putchar('\n'); }
template <class... Ts> void writeln(Ts &&... xs) {
    write(forward<Ts>(xs)...);
    _putchar('\n');
}
void flush() { _flush(); }
class IOManager {
  public:
    ~IOManager() {
        flush();
        if (_tempInputBuf)
            delete[](_tempInputBuf);
    }
};
unique_ptr<IOManager> iomanager = make_unique<IOManager>();
void setOutput(FILE *file) {
    flush();
    _output = file;
}
void setOutput(const char *s) {
    flush();
    _output = fopen(s, "w");
}
void setOutput(const string &s) {
    flush();
    _output = fopen(s.c_str(), "w");
}
template <class... Ts> void debug(const Ts &... xs) {
    FILE *_temp = _output;
    setOutput(_error);
    write(xs...);
    setOutput(_temp);
}
template <class... Ts> void debugln(const Ts &... xs) {
    FILE *_temp = _output;
    setOutput(_error);
    writeln(xs...);
    setOutput(_temp);
}
void setError(FILE *file) {
    flush();
    _error = file;
}
void setError(const char *s) {
    flush();
    _error = fopen(s, "w");
}
void setError(const string &s) {
    flush();
    _error = fopen(s.c_str(), "w");
}

template <const int MAXV, const int MAXE, class unit, const bool SCALING> struct DinicMaxFlow {
    unit INF, EPS;
    DinicMaxFlow(unit INF, unit EPS) : INF(INF), EPS(EPS) {}
    struct Edge {
        int from, to;
        unit origCap, cap;
        int rev;
        char isRev;
        Edge() {}
        Edge(int from, int to, unit origCap, unit cap, char isRev) : from(from), to(to), origCap(origCap), cap(cap), isRev(isRev) {}
    };
    int E, cur[MAXV], level[MAXV], q[MAXV], st[MAXV], deg[MAXV], ord[MAXE * 2], ind[MAXE * 2];
    bool cut[MAXV];
    Edge e[MAXE * 2];
    unit maxFlow, minCut, maxCap;
    void addEdge(int v, int w, unit vw, unit wv = 0) {
        e[E++] = Edge(v, w, max(vw, wv), vw, 0);
        e[E++] = Edge(w, v, max(vw, wv), wv, 1);
        e[E - 2].rev = E - 1;
        e[E - 1].rev = E - 2;
        deg[v]++;
        deg[w]++;
        maxCap = max(maxCap, max(vw, wv));
    }
    bool bfs(int V, int s, int t, unit lim, char r) {
        fill(level, level + V, -1);
        level[s] = 0;
        int front = 0, back = 0;
        q[back++] = s;
        while (front < back && level[t] == -1) {
            int v = q[front++];
            for (int i = st[v]; i < st[v] + deg[v] && e[i].origCap > lim && e[i].isRev <= r; i++)
                if (level[e[i].to] == -1 && e[i].cap > EPS) {
                    level[e[i].to] = level[v] + 1;
                    q[back++] = e[i].to;
                }
        }
        return level[t] != -1;
    }
    unit dfs(int v, int t, unit flow, unit lim, char r) {
        if (v == t || flow <= EPS)
            return flow;
        unit ret = 0;
        for (int &i = cur[v]; i < st[v] + deg[v] && e[i].origCap > lim && e[i].isRev <= r; i++) {
            if (e[i].cap > EPS && level[e[i].to] == level[v] + 1) {
                unit res = dfs(e[i].to, t, min(flow, e[i].cap), lim, r);
                if (res > EPS) {
                    e[i].cap -= res;
                    e[e[i].rev].cap += res;
                    flow -= res;
                    ret += res;
                    if (flow <= EPS)
                        break;
                }
            }
        }
        return ret;
    }
    void init(int V = MAXV) {
        E = 0;
        maxCap = 0;
        fill(cut, cut + V, false);
        fill(deg, deg + V, 0);
    }
    unit getFlow(int V, int s, int t) {
        maxFlow = 0;
        iota(ord, ord + E, 0);
        stable_sort(ord, ord + E, [&](const int &a, const int &b) {
            if (e[a].from != e[b].from)
                return e[a].from < e[b].from;
            if (e[a].isRev != e[b].isRev)
                return e[a].isRev < e[b].isRev;
            return true;
            return e[a].origCap > e[b].origCap;
        });
        for (int i = 0; i < E; i++)
            ind[ord[i]] = i;
        for (int i = 0; i < E; i++)
            e[i].rev = ind[e[i].rev];
        stable_sort(e, e + E, [&](const Edge &a, const Edge &b) {
            if (a.from != b.from)
                return a.from < b.from;
            if (a.isRev != b.isRev)
                return a.isRev < b.isRev;
            return true;
            return a.origCap > b.origCap;
        });
        return 0;
        for (int v = 0, curSum = 0; v < V; v++) {
            st[v] = curSum;
            curSum += deg[v];
        }
        for (char r = 1 - int(SCALING); r <= 1; r++)
            for (unit lim = SCALING ? maxCap : EPS;; lim /= 2) {
                while (bfs(V, s, t, lim, r)) {
                    copy(st, st + V, cur);
                    maxFlow += dfs(s, t, INF, lim, r);
                }
                if (lim <= EPS)
                    break;
            }
        return maxFlow;
    }
    void inferMinCutDfs(int v) {
        cut[v] = true;
        for (int i = st[v]; i < st[v] + deg[v]; i++)
            if (e[i].cap > EPS && !cut[e[i].to])
                inferMinCutDfs(e[i].to);
    }
    unit inferMinCut(int V, int s) {
        inferMinCutDfs(s);
        minCut = 0;
        for (int v = 0; v < V; v++)
            if (cut[v])
                for (int i = st[v]; i < st[v] + deg[v]; i++)
                    if (!cut[e[i].to])
                        minCut += e[i].origCap;
        return minCut;
    }
};

const int MAXN = 5005, MAXM = MAXN * MAXN;

int N, M, S, T;
DinicMaxFlow<MAXN, MAXM, int, 1> mf(INT_INF, 0);

int main() {
    // setInput("in.txt");
    // setOutput("out.txt");
    // setError("err.txt");
    mf.init();
    // read(N, M, S, T);
    cin >> N >> M;
    S = 1, T = N;
    // cin >> S >> T;
    --S;
    --T;
    int a, b, c;
    FOR(i, M) {
        // read(a, b, c);
        cin >> a >> b >> c;
        mf.addEdge(--a, --b, c);
    }
    cout << mf.getFlow(N, S, T) << endl;
    return 0;
}