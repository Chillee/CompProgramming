#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 105;
int T, N;
int A[MAXN][MAXN];
vector<int> adjList[MAXN * MAXN];
int main() {
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> A[i][j];
            }
        }
        for (int i = 0; i < N; i++) {
            map<int, vector<int>> graph;
            for (int j = 0; j < N; j++) {
                if (graph.count(A[i][j]) == 0) {
                    graph[A[i][j]] = vector<int>();
                }
                graph[A[i][j]].push_back(j);
            }
            for (auto v : graph) {
                for (auto j : v.second) {
                    for (auto k : v.second) {
                        if (j == k)
                            continue;
                        adjlist[i * N + j].push_back(i * N + k);
                        adjlist[i * N + k].push_back(i * N + j);
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) {
            map<int, vector<int>> graph;
            for (int j = 0; j < N; j++) {
                if (graph.count(A[j][i]) == 0) {
                    graph[A[j][i]] = vector<int>();
                }
                graph[A[j][i]].push_back(j);
            }
            for (auto v : graph) {
                for (auto j : v.second) {
                    for (auto k : v.second) {
                        if (j == k)
                            continue;
                        adjlist[j * N + i].push_back(j * N + i);
                        adjlist[k * N + i].push_back(k * N + i);
                    }
                }
            }
        }
        priority_queue<pii> curDegrees;
        for (int i = 0; i < N * N; i++) {
            curDegrees.push({adjlist[i].size(), i});
        }
        int ans = 0;
        vector<int> inQ(N * N);
        while (curDegrees.size()) {
            auto t = curDegrees.top();
            curDegrees.pop();
            if (inQ[t.second] > 0) {
                inQ[t.second]--;
                continue;
            }
            for (auto i : adjlist[t.second]) {
            }
        }
    }
}