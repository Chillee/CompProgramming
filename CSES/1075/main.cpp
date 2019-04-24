#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
struct H {
    typedef uint64_t ull;
    ull x;
    H(ull x = 0) : x(x) {}
    H operator+(H o) {
        ull r = x;
        asm("addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : "d"(o.x));
        return r;
    }
    H operator*(H o) {
        ull r = x;
        asm("mul %1\n"
            "addq %%rdx, %0\n adcq $0,%0"
            : "+a"(r)
            : "r"(o.x)
            : "rdx");
        return r;
    }
    H operator-(H o) { return *this + ~o.x; }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ull x = 5;
    ull y = 2;
    x = x + ~y;
    cout << x + !~x << endl;
}