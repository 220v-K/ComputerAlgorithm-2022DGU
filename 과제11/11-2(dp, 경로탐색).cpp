#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

#define N 200

int matrix[4][4] = {
    {6, 7, 12, 5},
    {5, 3, 11, 18},
    {7, 17, 3, 3},
    {8, 10, 14, 9},
};
int minMatrix[4][4];

int findMinRoute_exampleMatrix() {
    minMatrix[0][0] = matrix[0][0];
    for (int i = 1; i < 4; i++) {
        minMatrix[0][i] = minMatrix[0][i - 1] + matrix[0][i];
        minMatrix[i][0] = minMatrix[i - 1][0] + matrix[i][0];
    }
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            minMatrix[i][j] = min(minMatrix[i - 1][j], minMatrix[i][j - 1]) + matrix[i][j];
        }
    }
    return minMatrix[3][3];
}

int BottomUpCount = 0;
int TopDownCount = 0;

int minRandomMatrix[N][N];
int findMinRoute_randomMatrix_bottomUp(int randomMatrix[N][N]) {
    minRandomMatrix[0][0] = randomMatrix[0][0];
    for (int i = 1; i < N; i++) {
        BottomUpCount++;
        minRandomMatrix[0][i] = minRandomMatrix[0][i - 1] + randomMatrix[0][i];
        minRandomMatrix[i][0] = minRandomMatrix[i - 1][0] + randomMatrix[i][0];
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            BottomUpCount++;
            minRandomMatrix[i][j] = min(minRandomMatrix[i - 1][j], minRandomMatrix[i][j - 1]) + randomMatrix[i][j];
        }
    }
    return minRandomMatrix[199][199];
}

int minRandomMatrix2[N][N];
int findMinRoute_randomMatrix_topDown(int randomMatrix[N][N], int i, int j) {
    TopDownCount++;
    if (i == 0 && j == 0) {
        return randomMatrix[0][0];
    }
    if (i < 0 || j < 0) {
        return 10000;
    }
    if (minRandomMatrix2[i][j] != 0) {
        return minRandomMatrix2[i][j];
    }

    minRandomMatrix2[i][j] = min(findMinRoute_randomMatrix_topDown(randomMatrix, i - 1, j), findMinRoute_randomMatrix_topDown(randomMatrix, i, j - 1)) + randomMatrix[i][j];
    return minRandomMatrix2[i][j];
}

int main() {
    int minRoute = findMinRoute_exampleMatrix();
    cout << "-------- 4x4 예시 행렬에 대한 경로 검색 --------" << endl;
    cout << minRoute << endl;
    // print minMatrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << minMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------- 랜덤 200x200 행렬에 대한 경로 검색 --------" << endl;
    // random 200x200 matrix (1 ~ 200)
    random_device rd;
    int randomMatrix[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            randomMatrix[i][j] = rd() % N;
        }
    }

    minRoute = findMinRoute_randomMatrix_bottomUp(randomMatrix);
    cout << "bottom-up 방식: " << minRoute << endl;
    cout << "bottom-up 방식 연산 횟수: " << BottomUpCount << endl;
    minRoute = findMinRoute_randomMatrix_topDown(randomMatrix, N - 1, N - 1);
    cout << "top-down 방식: " << minRoute << endl;
    cout << "top-down 방식 함수 호출 횟수: " << TopDownCount << endl;

    // cout << minRoute << endl;
}