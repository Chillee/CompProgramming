#include <bits/stdc++.h>

using namespace std;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
struct node {
    node *l = nullptr, *r = nullptr;
    int val, key = rnd();
    int sz = 1;
    node(int value) : val(value) {}
    ~node() { delete l, delete r; }
    void upd() { sz = 1 + (l ? l->sz : 0) + (r ? r->sz : 0); }
};

struct treap {
    node *root;
    treap() { root = nullptr; }
    void split(node *t, int val, node *&l, node *&r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (t->val < val) {
            split(t->r, val, l, r);
            t->r = l;
            l = t;
        } else {
            split(t->l, val, l, r);
            t->l = r;
            r = t;
        }
        t->upd();
    }
    node *merge(node *l, node *r) {
        if (!l || !r)
            return l ? l : r;
        if (l->key < r->key) {
            l->r = merge(l->r, r);
            l->upd();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->upd();
            return r;
        }
    }
    void insert(int val) {
        if (find(root, val))
            return;
        node *l, *r;
        split(root, val, l, r);
        root = merge(merge(l, new node(val)), r);
    }
    void erase(int val) {
        node *l, *t, *r;
        split(root, val, l, t);
        split(t, val + 1, t, r);
        delete t;
        root = merge(l, r);
    }
    bool find(node *t, int val) {
        if (!t)
            return false;
        if (t->val == val)
            return true;
        if (t->val < val)
            return find(t->r, val);
        return find(t->l, val);
    }
    int size() { return root ? root->sz : 0; }
    int index(node *t, int i) {
        int lsz = t->l ? t->l->sz : 0;
        if (i == lsz)
            return t->val;
        if (i < lsz)
            return index(t->l, i);
        return index(t->r, i - lsz - 1);
    }
    int indexof(node *t, int x) {
        int lsz = t->l ? t->l->sz : 0;
        if (t->val == x)
            return lsz;
        if (t->val < x)
            return lsz + 1 + indexof(t->r, x);
        return indexof(t->l, x);
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    treap t;
    t.insert(1);
    t.insert(3);
    t.insert(4);
    cout << t.size() << endl;
}