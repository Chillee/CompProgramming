#include <immintrin.h>
#include <bits/stdc++.h>

using namespace std;

int dist(const char *s, const char *t, unsigned int len) {
    int i, d = 0;
    for (i = 0; i < len; i++) {
        d += s[i] != t[i];
    }
    return d;
}
int dist2(const char *s, const char *t, unsigned int len) {
    __m256i a, b, c, e, f, g, h, x, x2, y, y2, b2, c2;
    int i = 0, d = len;
    for (; i < len;) {
        int j = 0;
        x = _mm256_set1_epi32(0);
        x2 = _mm256_set1_epi32(0);
        int lim = len, lim2 = i + 64 * 120;
        if (lim2 < lim)
            lim = lim2;
        for (; i < lim; i += 64) {
            b = _mm256_loadu_si256((void *)(s + i));
            c = _mm256_loadu_si256((void *)(t + i));
            y = _mm256_cmpeq_epi8(b, c);
            b2 = _mm256_loadu_si256((void *)(s + i + 32));
            c2 = _mm256_loadu_si256((void *)(t + i + 32));
            y2 = _mm256_cmpeq_epi8(b2, c2);
            x = _mm256_add_epi8(x, y);
            x2 = _mm256_add_epi8(x2, y2);
        }
        signed char z[64];
        _mm256_storeu_si256((void *)z, x);
        _mm256_storeu_si256((void *)(z + 32), x2);
        for (j = 0; j < 64; j++) {
            d += z[j];
        }
    }
    return d;
}

int dist_vec(const char *s, const char *t, unsigned int len) {
    int i = 0, d = 0;
    while (len % 64) {
        len--;
        d += s[len] != t[len];
    }
    d += dist2(s, t, len);
    return d;
}
const int MAXN = 2e5 + 5;
char A[MAXN], B[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    begin = clock();
    cout << dist(A, B, MAXN) << endl;
    cout << "unvectorized: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}