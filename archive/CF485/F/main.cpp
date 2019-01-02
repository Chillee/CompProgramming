#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 22) + 5;

bool exists[MAXN];
bool visited[MAXN];
bool visited2[MAXN];
int cnt = 0;

int N, M;
int A[MAXN];

void dfs(int cur, bool is2) {
    if (is2) {
        visited2[cur] = true;
        for (int i = 0; i < N; i++) {
            int next = cur | (1 << i);
            if (visited2[next])
                continue;
            visited2[next] = true;
            dfs(next, true);
        }
        int complement = (1 << N) - 1 - cur;
        if (exists[complement] && !visited[complement]) {
            dfs(complement, false);
        }
    } else {
        visited[cur] = true;
        if (visited2[cur])
            return;
        dfs(cur, true);
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> A[i];
        exists[A[i]] = true;
    }
    int ans = 0;
    for (int i = 0; i < M; i++) {
        if (!visited[A[i]]) {
            ans++;
            visited[A[i]] = true;
            dfs(A[i], true);
        }
    }
    cout << ans << endl;
}