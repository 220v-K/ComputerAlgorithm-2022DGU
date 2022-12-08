#include <math.h>

#include <iostream>
#include <vector>

using namespace std;

const int N = 10000;
int mul_num = 0;

int main() {
    int i, j, a[N + 1];
    for (a[1] = 0, i = 2; i <= N; i++)
        a[i] = 1;
    for (i = 2; i <= N / 2; i++)
        for (j = 2; j <= N / i; j++) {
            a[i * j] = 0;
            mul_num++;
        }

    for (i = N - 1; i > 0; i--)
        if (a[i]) {
            cout << "10,000º¸´Ù ÀÛÀº ÃÖ´ë ¼Ò¼ö: " << i << endl;
            break;
        }

    cout << "°ö¼À ¿¬»ê È½¼ö: " << mul_num << endl;
}