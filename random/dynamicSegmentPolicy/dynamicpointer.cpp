
#include <bits/stdc++.h>
using namespace std;

random_device rd; // only used once to initialise (seed) engine
mt19937 rng(rd());
uniform_int_distribution<int> uni(0, 1e9);

struct node;
node *newNode();

struct node {
    int lv, rv, sum;
    node *left, *right;

    node() : left(NULL), right(NULL), sum(0) {}

    inline void init(int l, int r) {
        lv = l;
        rv = r;
    }

    inline void extend() {
        if (!left) {
            int m = (lv + rv) / 2;
            left = newNode();
            right = newNode();
            left->init(lv, m);
            right->init(m + 1, rv);
        }
    }

    int getSum(int l, int r) {
        if (r < lv || rv < l) {
            return 0;
        }

        if (l <= lv && rv <= r) {
            return sum;
        }

        extend();
        return left->getSum(l, r) + right->getSum(l, r);
    }

    void update(int p, int newVal) {
        if (lv == rv) {
            sum = newVal;
            return;
        }

        extend();
        (p <= left->rv ? left : right)->update(p, newVal);
        sum = left->sum + right->sum;
    }
};

node *newNode() {
    static int bufSize = 1e7;
    static node buf[(int)1e7];
    assert(bufSize);
    return &buf[--bufSize];
}

int main() {
    clock_t begin = clock();
    node *rmq = newNode();
    rmq->init(0, 1e9);
    for (int i = 0; i < 1e5; i++) {
        rmq->update(uni(rng), i);
    }
    for (int i = 0; i < 1e5; i++) {
        int a = uni(rng);
        int b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        rmq->getSum(a, b);
    }
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;

    /// do smth
}
