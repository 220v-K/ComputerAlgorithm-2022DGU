#include <iostream>
using namespace std;

class PQ {
   private:
    int N;
    int i;

   public:
    int *a;
    int heapCompare;

    PQ(int max) {
        a = new int[max];
        N = 0;
        i = 0;
        heapCompare = 0;
    }
    ~PQ() {
        delete a;
    }

    void insertData(int v) {
        a[i++] = v;
    }

    int get(int i) {
        return a[i];
    }

    // insert a new element into the priority queue - O(logN)
    // !---------------
    void MakeHeap(int a[], int root, int LastNode) {
        int child;
        int temp;
        temp = a[root];
        child = 2 * root;
        while (child <= LastNode) {
            heapCompare++;
            if ((child < LastNode) && (a[child] < a[child + 1])) {
                child++;
            }
            heapCompare++;
            if (temp >= a[child]) {
                break;
            } else {
                a[child / 2] = a[child];
                child *= 2;
            }
        }
        a[child / 2] = temp;
    }
};

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapSort(int a[], int N, PQ &pq) {
    for (int i = N / 2 - 1; i >= 0; i--)
        pq.MakeHeap(a, i, N - 1);
    for (int i = N - 1; i >= 1; i--) {
        swap(a[0], a[i]);
        pq.MakeHeap(a, 0, i - 1);
    }
}

int main() {
    int N;
    cin >> N;
    PQ pq(N);
    for (int i = 0; i < N; i++) {
        pq.insertData(rand() % 10000 + 1);
    }
    heapSort(pq.a, N, pq);
    cout << "Random Numbers Array - Compare count: " << pq.heapCompare << endl;

    //!----------------
    //최악의 경우 : 이미 정렬된 배열을 입력받을 경우 -> 최대 힙을 사용하기 때문에 비교 횟수가 많아짐.
    int K = 10000;
    PQ pq2(K);
    for (int i = 0; i < K; i++) {
        pq2.insertData(i + 1);
    }
    heapSort(pq2.a, K, pq2);
    cout << "Sorted Array - Compare count: " << pq2.heapCompare << endl;
    //!----------------
    for (int i = 0; i < N; i++) {
        cout << pq.get(i) << " ";
    }

    return 0;
}