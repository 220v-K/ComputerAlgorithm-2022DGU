#include <iostream>
using namespace std;

int compareCount = 0;

void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(int a[], int l, int r) {
    int i, j;
    int v;

    if (r > l) {
        v = a[l];
        i = l;
        j = r + 1;
        while (1) {
            while (a[++i] < v)
                if (i == r) break;
            while (a[--j] > v)
                if (j == l) break;
            compareCount++;
            if (i >= j) break;
            swap(a, i, j);
        }
        swap(a, l, j);
    }
    return j;
}

void select(int a[], int l, int r, int k) {
    int j;
    if (r > l) {
        j = partition(a, l, r);
        if (j > l + k - 1) select(a, l, j - 1, k);
        if (j < l + k - 1) select(a, j + 1, r, k - (j - l + 1));
    }
}

int main() {
    int N;
    cin >> N;
    int a[N], b[N], c[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 10000 + 1;
        b[i] = a[i];
        c[i] = a[i];
    }

    select(a, 0, N - 1, 1);
    cout << "Minimum: " << a[0] << ", Compare: " << compareCount << endl;
    compareCount = 0;
    select(b, 0, N - 1, N);
    cout << "Maximum: " << b[N - 1] << ", Compare: " << compareCount << endl;
    compareCount = 0;
    select(c, 0, N - 1, N / 2);
    cout << "Middle: " << c[N / 2] << ", Compare: " << compareCount << endl;

    // print a array
    for (int i = 0; i < N; i++) {
        cout << a[i] << " ";
    }
}