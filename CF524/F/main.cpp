#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXK = 3e5 + 5;
const int INF = 1e9 + 5;
int N, M, K;
typedef vector<array<int, 2>> info;
bool cmp(array<int, 2> a, array<int, 2> b) { return make_pair(a[0], -a[1]) < make_pair(b[0], -b[1]); }

void process(info &a) {
    info res;
    for (auto i : a) {
        while (res.size() > 0 && res.back()[1] >= i[1]) {
            res.pop_back();
        }
        res.push_back(i);
    }
    a = res;
}
array<int, 2> merge(array<int, 2> a, array<int, 2> b) { return {min(a[0], b[0]), max(a[1], b[1])}; }

info combine(info &a, info &b) {
    info res;
    if (a.size() == 0) {
        return {};
    } else if (b.size() == 0) {
        return {};
    }
    int lidx = 0, ridx = 0;
    while (lidx < a.size() && ridx < b.size()) {
        res.push_back(merge(a[lidx], b[ridx]));
        if (cmp(a[lidx], b[ridx])) {
            lidx++;
        } else {
            ridx++;
        }
    }
    sort(res.begin(), res.end(), cmp);
    process(res);
    return res;
}

info seg[2 * MAXK];
void build() {
    for (int i = N - 1; i > 0; --i) {
        seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }
}

void modify(int p, info value) {
    for (seg[p += N] = value; p >>= 1;)
        seg[p] = combine(seg[p << 1], seg[p << 1 | 1]);
}

bool isGood(info &x, int l, int r) {
    array<int, 2> val = {l, -INF};
    auto lb = lower_bound(x.begin(), x.end(), val);
    if (lb == x.end()) {
        return false;
    }
    return (*lb)[1] <= r;
}

bool query(int l, int r, int x, int y) {
    bool res = true;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = res && isGood(seg[l++], x, y);
        }
        if (r & 1) {
            res = isGood(seg[--r], x, y) && res;
        }
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < K; i++) {
        int l, r, p;
        cin >> l >> r >> p;
        p--;
        seg[p + N].push_back({l, r});
    }
    for (int i = N; i < 2 * N; i++) {
        sort(seg[i].begin(), seg[i].end(), cmp);
        process(seg[i]);
    }
    build();
    for (int i = 0; i < M; i++) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        a--;
        cout << (query(a, b, x, y) ? "yes" : "no") << endl;
    }
}