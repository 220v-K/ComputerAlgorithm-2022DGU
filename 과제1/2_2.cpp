#include <math.h>

#include <iostream>
#include <vector>

using namespace std;

const int N = 10000;
int mul_num = 0;
vector<int> primes;

bool isPrime(int num) {
    for (int i = 2; i <= (int)sqrt(num); i++) {
        mul_num++;
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    for (int i = 2; i < N; i++) {
        if (isPrime(i))
            primes.push_back(i);
    }

    cout << "10,000보다 작은 최대 소수: " << primes[primes.size() - 1] << endl;
    cout << "나눗셈 연산 회수: " << mul_num << endl;
}