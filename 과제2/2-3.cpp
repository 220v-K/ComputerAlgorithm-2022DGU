#include <stdlib.h>
#include <time.h>

#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    srand((unsigned)time(NULL));

    // Create a vector of Union and Intersection of A, B
    vector<int> U;
    vector<int> X;

    // n, m >= 10
    int n, m;
    cin >> n >> m;

    deque<int> A;
    deque<int> B;

    // number : 1 ~ 10000 - 집합이 아니라 집단이라고 했으므로, 중복된 값이 들어갈 수 있다.
    while (A.size() < n) {
        A.push_back(rand() % 10 + 1);
    }
    while (B.size() < m) {
        B.push_back(rand() % 10 + 1);
    }

    // union : A + B
    for (int i = 0; i < A.size(); i++) {
        auto iter = find(U.begin(), U.end(), A[i]);
        if (iter == U.end()) {
            U.push_back(A[i]);
        }
    }
    for (int i = 0; i < B.size(); i++) {
        auto iter = find(U.begin(), U.end(), B[i]);
        if (iter == U.end()) {
            U.push_back(B[i]);
        }
    }

    // intersection : A * B
    for (int i = 0; i < A.size(); i++) {
        auto iter = find(B.begin(), B.end(), A[i]);
        auto iter2 = find(X.begin(), X.end(), A[i]);
        if (iter != B.end() && iter2 == X.end()) {
            X.push_back(A[i]);
        }
    }

    // print A, B
    cout << "A : ";
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "B : ";
    for (int i = 0; i < B.size(); i++) {
        cout << B[i] << " ";
    }
    cout << endl;

    // print vector U
    cout << "U = { ";
    for (int i = 0; i < U.size(); i++) {
        cout << U[i] << " ";
    }
    cout << "}" << endl;
    cout << "X = { ";
    // print vector X
    for (int i = 0; i < X.size(); i++) {
        cout << X[i] << " ";
    }
    cout << "}" << endl;
}
