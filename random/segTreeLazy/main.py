

N = 4
H = 3  # height of the tree
seg = [0 for _ in range(100005)]
lazy = [0 for _ in range(100005)]


def apply(p, value, k):
    seg[p] += value * k
    if p < N:
        lazy[p] += value


def propDown(p) {
    k = 1 << (H - 1)
    for s in range(H, 0, -1):
        i = p >> s
        if (lazy[i] != 0):
            apply(i * 2, lazy[i], k)
            apply(i * 2 + 1, lazy[i], k)
            lazy[i] = 0
        k /= 2

def propUp(p) {
    k = 2
    while (p > 1):
        p >>= 1
        seg[p] = seg[p * 2] + seg[p * 2 1 + 1] + lazy[p] * k
        k <<= 1

def inc(l, r, val):
    l += N, r += N
    l0 = l, r0 = r, k = 1
    while (l < r):
        if (l & 1):
            apply(l, val, k)
            l += 1
        if (r & 1):
            apply(r, val, k)
            r -= 1
        l /= 2, r /= 2, k *= 2
    propUp(l0)
    propUp(r0 - 1)

def query(l, r):
    l += N, r += N
    propDown(l)
    propDown(r - 1)
    res = 0
    while l < r:
        if (l & 1):
            res += seg[l]
            l += 1
        if (r & 1):
            r -= 1
            res += seg[r]
        l /= 2, r /= 2
    return res

int main() {
    for (int i=0; i < N; i++) {
        seg[i + N] = i;}
    for (int i=0; i < N; i++) {
        propUp(i + N);}
    inc(0, 4, 1);
    inc(1, 3, 1);
    // for (int i=1; i < N; i++) {
    // propDown(i + N);
    // }
    // for (int i=0; i < 2 * N; i++) {
    // cout << "(" << seg[i] << ", " << lazy[i] << ") ";
    // }
    // cout << endl;
    cout << query(0, N) << endl;}
