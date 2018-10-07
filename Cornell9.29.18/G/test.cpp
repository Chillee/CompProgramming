#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
struct Edge {
    int x, y, w, xx, yy, idx;

    Edge(int a = 0, int b = 0, int c = 0) {
        x = a;
        y = b;
        w = c;
        xx = x;
        yy = y;
    }
};
vector<Edge> Result;
void addEdge(Edge e) {
    // cout<<"adding "<<e.xx<<" "<<e.yy<<endl;
    for (int i = 0; i < Result.size(); i++) {
        if (Result[i].yy == e.yy) {
            Result.erase(Result.begin() + i);
        }
    }
    Result.push_back(e);
}
typedef long long llint;

int dmst(int N, vector<Edge> E, int root) {
    const int oo = 1e9;

    vector<int> cost(N), back(N), label(N), bio(N);
    vector<Edge> edge(N);

    int ret = 0;

    for (;;) {
        REP(i, N) cost[i] = oo;
        for (auto e : E) {
            if (e.x == e.y)
                continue;
            if (e.w < cost[e.y]) {
                cost[e.y] = e.w, back[e.y] = e.x;
                edge[e.y] = e;
            }
        }
        cost[root] = 0;
        REP(i, N) {
            if (cost[i] == oo) {
                cout << -1 << endl;
                exit(0);
            }
        }

        REP(i, N) {
            ret += cost[i];
            if (i != root)
                addEdge(edge[i]);
        }

        int K = 0;
        REP(i, N) label[i] = -1;
        REP(i, N) bio[i] = -1;

        REP(i, N) {
            int x = i;
            for (; x != root && bio[x] == -1; x = back[x])
                bio[x] = i;

            if (x != root && bio[x] == i) {
                for (; label[x] == -1; x = back[x])
                    label[x] = K;
                ++K;
            }
        }
        if (K == 0)
            break;

        REP(i, N) if (label[i] == -1) label[i] = K++;

        for (auto &e : E) {
            int xx = label[e.x];
            int yy = label[e.y];
            if (xx != yy)
                e.w -= cost[e.y];
            e.x = xx;
            e.y = yy;
        }

        root = label[root];
        N = K;
    }

    return ret;
}

set<int> orig;
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int num, edge;
    cin >> num >> edge;
    vector<Edge> edges(edge);
    for (int n = 0; n < edge; n++) {
        cin >> edges[n].x >> edges[n].y >> edges[n].w;
        edges[n].x--, edges[n].y--;
        edges[n].xx = edges[n].x;
        edges[n].yy = edges[n].y;
        edges[n].idx = n;
    }

    cout << dmst(num, edges, 0) << endl;
    for (auto e : Result) {
        if (e.w == 1)
            cout << e.idx + 1 << ' ';
    }
    cout << endl;

    return 0;
}