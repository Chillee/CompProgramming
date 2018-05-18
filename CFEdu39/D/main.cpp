#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int dp1[505][505];
int dp2[505][505];
int dp1final[505][505];
bool classes[505][505];
int getmin(int day, int cnt) {
    for (int i = 0; i < M; i++) {
        if (classes[day][i]) {
            cnt--;
            if (cnt == -1)
                return i;
        }
    }
    return -1;
}

int getmax(int day, int cnt) {
    for (int i = M - 1; i >= 0; i--) {
        if (classes[day][i]) {
            cnt--;
            if (cnt == -1)
                return i;
        }
    }
    return -1;
}

int main() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char t;
            cin >> t;
            if (t == '0') {
                classes[i][j] = false;
            } else {
                classes[i][j] = true;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        int classcnt = 0;
        for (int j = 0; j < M; j++) {
            if (classes[i][j]) {
                classcnt++;
            }
        }
        int left[505];
        int right[505];
        int cnt = 0;
        for (int j = 0; j < M; j++) {
            if (classes[i][j]) {
                cnt += 1;
                left[cnt - 1] = j;
            }
        }
        cnt = 0;
        for (int j = M - 1; j >= 0; j--) {
            if (classes[i][j]) {
                cnt += 1;
                right[cnt - 1] = j;
            }
        }
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k <= M; k++) {
                if (j + k >= classcnt) {
                    dp1[j][k] = -1;
                } else {
                    dp1[j][k] = right[j] - left[k];
                }
            }
        }
        for (int j = 0; j < M; j++) {
            dp1final[i][j] = dp1[0][0];
            for (int k = 0; k <= j; k++) {
                dp1final[i][j] = min(dp1final[i][j], dp1[k][j - k]);
            }
            dp1final[i][j]++;
        }
    }
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            dp2[0][0] = dp1final[0][0];
        } else {
            dp2[i][0] = dp2[i - 1][0] + dp1final[i][0];
        }
        for (int j = 1; j <= K; j++) {
            if (i == 0) {
                dp2[0][j] = dp1final[0][j];
            } else {
                dp2[i][j] = 1e9;
                for (int k = 0; k <= j; k++) {
                    dp2[i][j] = min(dp2[i - 1][k] + dp1final[i][j - k], dp2[i][j]);
                }
            }
        }
    }
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j <= K; j++) {
    //         cout << dp2[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    cout << dp2[N - 1][K] << endl;
}