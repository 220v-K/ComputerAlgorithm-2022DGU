#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>

using namespace std;

const int n = 1000;
int insertionCompare = 0;
int insertionSwap = 0;
int QuickCompare = 0;
int QuickSwap = 0;
int heapCompare = 0;
int heapSwap = 0;

long long insertionMoveWeight = 0;
long long QuickMoveWeight = 0;
long long heapMoveWeight = 0;

void insertion(int a[], int N) {
    int i, j, v;
    for (i = 0; i < N; i++) {
        v = a[i];
        insertionMoveWeight += a[i];
        j = i;
        while (j > 0 && a[j - 1] > v) {
            insertionCompare++;
            a[j] = a[j - 1];
            insertionMoveWeight += a[j - 1];
            insertionSwap++;
            j--;
        }
        a[j] = v;
        insertionMoveWeight += v;
        insertionSwap++;
    }
}

void swap(int a[], int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int partition(int a[], int l, int r) {
    int i, j, v;
    if (r > l) {
        v = a[l];
        i = l;
        j = r + 1;
        while (1) {
            do {
                ++i;
                QuickCompare++;
            } while (a[i] < v);
            do {
                --j;
                QuickCompare++;
            } while (a[j] > v);
            if (i >= j) break;
            swap(a, i, j);
            QuickSwap += 2;
            QuickMoveWeight += a[i] * 2 + a[j];
            // i를 두 번 들어 움직임
        }
        swap(a, j, l);
        QuickSwap += 2;
        QuickMoveWeight += a[j] * 2 + a[l];
    }
    return j;
}

void quicksort(int a[], int l, int r) {
    int j;
    if (r > l) {
        j = partition(a, l, r);
        quicksort(a, l, j - 1);
        quicksort(a, j + 1, r);
    }
}

void makeHeap(int a[], int i, int N) {
    int j, v;
    v = a[i];
    heapMoveWeight += a[i];
    j = 2 * i;
    while (j <= N) {
        if (j < N && a[j] < a[j + 1]) {
            j++;
            heapCompare++;
        }
        if (v >= a[j]) {
            break;
            heapCompare++;
        }
        a[j / 2] = a[j];
        heapSwap++;
        heapMoveWeight += a[j];
        j *= 2;
    }
    a[j / 2] = v;
    heapSwap++;
    heapMoveWeight += v;
}

void heapsort(int a[], int n) {
    int i;

    for (int i = n / 2; i > 0; i--) {
        makeHeap(a, i - 1, n - 1);
    }
    for (i = n - 1; i > 0; i--) {
        swap(a, 0, i);
        makeHeap(a, 0, i - 1);
    }
}

int main() {
    int a[n], b[n], c[n];
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000 + 1;
        b[i] = a[i];
        c[i] = a[i];
        // printf("%5d", a[i]);
    }

    insertion(a, n);
    quicksort(b, 0, n - 1);
    heapsort(c, n);

    cout << "Insertion Compare: " << insertionCompare << endl;
    cout << "Insertion Swap: " << insertionSwap << endl;
    cout << "Quick Compare: " << QuickCompare << endl;
    cout << "Quick Swap: " << QuickSwap << endl;
    cout << "Heap Compare: " << heapCompare << endl;
    cout << "Heap Swap: " << heapSwap << endl;

    cout << "Insertion Move Weight: " << insertionMoveWeight << endl;
    cout << "Quick Move Weight: " << QuickMoveWeight << endl;
    cout << "Heap Move Weight: " << heapMoveWeight << endl;

    // print a[i]
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}