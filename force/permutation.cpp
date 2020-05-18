#include <iostream>

#define num 9

using namespace std;

bool used[num];
int result[num];

void permutation(int n, int m) {
    if (m == n) {
        for (int i = 0; i < n; i++)
            cout << result[i] << ' ';
        cout << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                used[i] = true;
                result[m] = i;
                permutation(n, m + 1);
                used[i] = false;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    permutation(n, 0);
}
