#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int fib(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int dp[300][1000000] = {
    0,
};

void bottom_up_fib(int n) {
    dp[0][0] = 1;
    dp[0][1] = 1;

    for (int i = 2; i <= n - 1; i++) {
        // big number addition with int array
        int carry = 0;
        for (int j = 0; j < 300; j++) {
            dp[j][i] = dp[j][i - 1] + dp[j][i - 2] + carry;
            if (dp[j][i - 1] == 0) break;   // if previous number is 0, break
            carry = dp[j][i] / 1000000000;  // int형의 범위가 2,147,483,647이므로 1,000,000,000으로 나눠준다. (10^9 자리까지만 사용)
            dp[j][i] -= carry * 1000000000;
        }
    }
}

int main() {
    cout << "피보나치 20번째 수 (top-down) : " << fib(20) << endl;
    int N = 10000;
    bottom_up_fib(N);
    // print dp[9999]
    cout << "피보나치 10000번째 수 (bottom-up) : ";
    for (int i = 299; i >= 0; i--) {
        if (dp[i][N - 1] != 0) cout << dp[i][N - 1];
    }
}