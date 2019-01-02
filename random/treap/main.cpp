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

struct Node {
    Node *child[2], *parent;
    bool reverse;
    int value, size;
    long long sum;
};

Node *nil, *root;

void initTree() {
    nil = new Node();
    nil->child[0] = nil->child[1] = nil->parent = nil;
    nil->value = nil->size = nil->sum = 0;
    nil->reverse = false;
    root = nil;
}

void update(Node *x) {
    x->size = x->child[0]->size + x->child[1]->size + 1;
    x->sum = x->child[0]->sum + x->child[1]->sum + x->value;
}

void setLink(Node *x, Node *y, int d) {
    x->child[d] = y;
    y->parent = x;
}

int getDir(Node *x, Node *y) { return x->child[0] == y ? 0 : 1; }

void rotate(Node *x, int d) {
    Node *y = x->child[d], *z = x->parent;
    setLink(x, y->child[d ^ 1], d);
    setLink(y, x, d ^ 1);
    setLink(z, y, getDir(z, x));
    update(x);
    update(y);
}

void splay(Node *x) {
    while (x->parent != nil) {
        Node *y = x->parent, *z = y->parent;
        int dy = getDir(y, x), dz = getDir(z, y);
        if (z == nil)
            rotate(y, dy);
        else if (dy == dz)
            rotate(z, dz), rotate(y, dy);
        else
            rotate(y, dy), rotate(z, dz);
    }
}

Node *nodeAt(Node *x, int pos) {
    while (pushDown(x), x->child[0]->size != pos)
        if (pos < x->child[0]->size)
            x = x->child[0];
        else
            pos -= x->child[0]->size + 1, x = x->child[1];
    return splay(x), x;
}

void queryAssign(int pos, int value) {
    root = nodeAt(root, pos);
    root->value = value;
    update(root);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    treap t;
    t.insert(1);
    t.insert(3);
    t.insert(4);
}