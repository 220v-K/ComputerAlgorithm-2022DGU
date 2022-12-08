#include <math.h>

#include <iostream>
#include <vector>

using namespace std;

const int N = 500;
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

    for (int i = 0; i < primes.size(); i++) {
        cout << primes[i] << " ";
    }
}