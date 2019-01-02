#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;
int N, K;
vector<pii> adjlist[MAXN];
int dist[MAXN];
void dfs1(int cur, int depth) {
    if (dist[cur] != -1) {
        return;
    }
    dist[cur] = depth;
    for (auto i : adjlist[cur]) {
        dfs1(i.first, depth + i.second);
    }
}
bool getPath(int cur, int dest, vector<int> &path) {
    if (cur == dest) {
        path.push_back(dest);
        return true;
    }
    if (dist[cur] != -1) {
        return false;
    }
    dist[cur] = true;
    bool hasPath = false;
    for (auto i : adjlist[cur]) {
        if (getPath(i.first, dest, path)) {
            hasPath = true;
        }
    }
    if (hasPath) {
        path.push_back(cur);
        return true;
    }
    return false;
}
int getDist(int a, int b) {
    for (auto i : adjlist[a]) {
        if (i.first == b) {
            return i.second;
        }
    }
    return -100000;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adjlist[a].push_back({b, d});
        adjlist[b].push_back({a, d});
    }
    fill(dist, dist + N, -1);
    dfs1(0, 0);
    int node1 = max_element(dist, dist + N) - dist;
    fill(dist, dist + N, -1);
    dfs1(node1, 0);
    int node2 = max_element(dist, dist + N) - dist;
    fill(dist, dist + N, -1);
    vector<int> res;
    getPath(node1, node2, res);
    vector<int> dist;
    dist.push_back(0);
    for (int i = 0; i < res.size() - 1; i++) {
        dist.push_back(dist[i] + getDist(res[i], res[i + 1]));
    }
    int center = 0;
    int totDist = dist[dist.size() - 1];
    for (int i = 0; i < dist.size(); i++) {
        if (abs(dist[i] - totDist / 2) < abs(dist[center] - totDist / 2)) {
            center = i;
        }
    }
    int leftIdx = center;
    int rightIdx = center;
    vector<int> nodes = {res[center]};
    for (int i = 1; i < K; i++) {
        if (leftIdx == 0 && rightIdx == res.size() - 1) {
            break;
        }
        if (leftIdx == 0) {
            nodes.push_back(res[rightIdx + 1]);
            rightIdx++;
        } else if (rightIdx == res.size() - 1) {
            nodes.push_back(res[leftIdx - 1]);
            leftIdx--;
        } else if (dist[leftIdx - 1] < totDist - dist[rightIdx + 1]) {
            nodes.push_back(res[rightIdx + 1]);
            rightIdx++;
        } else {
            nodes.push_back(res[leftIdx - 1]);
            leftIdx--;
        }
    }
    fill(::dist, ::dist + N, -1);
    for (auto i : nodes) {
        ::dist[i] = 0;
    }
    for (auto i : nodes) {
        ::dist[i] = -1;
        dfs1(i, 0);
    }
    cout << *max_element(::dist, ::dist + N) << endl;
}