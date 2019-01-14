#include <iostream>

using namespace std;

bool comblock(int arr[], int n, int j) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    if (sum % 360 == 0)
        return 1;
    else {
        bool res = 0;
        for (int i = j; i < n; i++) {
            arr[i] = -arr[i];
            res = comblock(arr, n, i + 1);
            if (res)
                return 1;
            arr[i] = -arr[i];
        }
        return res;
    }
}

int main() {
    int n, *a;
    cin >> n;
    a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (comblock(a, n, 0))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}