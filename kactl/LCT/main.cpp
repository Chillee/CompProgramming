#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;
struct Node {
    bool rr;
    Node *son[2], *pf, *fa;

    void downdate() {
        if (rr) {
            son[0]->rr = !son[0]->rr;
            son[1]->rr = !son[1]->rr;
            swap(son[0], son[1]);
            rr = false;
        }
        // add stuff
    }

    void update() {
        // add stuff
    }

    void rotate(bool t) { /// start-hash
        Node *y = fa, *z = y->fa;
        if (z != nullptr)
            z->son[z->son[1] == y] = this;
        fa = z;
        son[t] =son[!t];
        son[!t]->fa = y;
        son[!t] = y;
        fa = this;
        y->update();
    } /// end-hash

    void xiao() {
        if (fa != nullptr)
            fa->xiao(), pf = fa->pf;
        downdate();
    }

    void splay() { /// start-hash
        xiao();
        Node *y, *z;
        while (fa != nullptr) {
            y = fa;
            z = y->fa;
            bool t1 = (y->son[1] == this), t2 = (z->son[1] == y);
            if (z != nullptr) {
                if (t1 == t2)
                    y->rotate(y), rotate(t1);
                else
                    rotate(t1), rotate(t2);
            } else
                rotate(t1);
        }
        update();
    } /// end-hash
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Node * splay = new Node();
}