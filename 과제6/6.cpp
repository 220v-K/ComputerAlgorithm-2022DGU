#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

typedef int itemType;
typedef int infoType;

class BST {
   private:
    struct node {
        int key;
        infoType info;
        struct node *left, *right;
        node(int k, infoType i, struct node *l, struct node *r) {
            key = k;
            info = i;
            left = l;
            right = r;
        }
    };
    struct node *head, *z;

   public:
    BST() {
        z = new node(0, 0, 0, 0);
        head = new node(0, 0, z, z);
    }
    ~BST(){};
    struct node *returnHead() {
        return head;
    }
    infoType BSTsearch(int v, int &count);
    itemType inorderSearch(struct node *x);
    void BSTinsert(int v, infoType info);
    int maxDepth(struct node *node) {
        if (node == z)
            return 0;
        else {
            int lDepth = maxDepth(node->left);
            int rDepth = maxDepth(node->right);
            if (lDepth > rDepth)
                return (lDepth + 1);
            else
                return (rDepth + 1);
        }
    }
    int printLevel(struct node *x, int value, int level) {
        if (x == z)
            return 0;
        if (x->key == value)
            return level;
        else {
            int downlevel = printLevel(x->left, value, level + 1);
            // left child node 쪽 subtree에서 value를 찾았다면 return
            if (downlevel != 0)
                return downlevel;
            // left child node 쪽 subtree에서 value를 못 찾았다면 right child node 쪽 subtree에서 검색
            // left child node 쪽 subtree에 없다면 무조건 right subtree에 존재함.
            // input value를 tree에 존재하는 value로 가정했기 때문.
            downlevel = printLevel(x->right, value, level + 1);
            return downlevel;
        }
    }
    void MaxMinLvl() {
        // print max Depth of tree
        cout << "Max Depth: " << maxDepth(head->right) << endl;
        // print min value's Level of tree
        cout << "Min Value's Level: " << printLevel(head->right, 1, 0) << endl;
        // print max value's Level of tree
        cout << "Max Value's Lelel: " << printLevel(head->right, 1999, 0) << endl;
    }
};

infoType BST::BSTsearch(int v, int &count) {
    struct node *x = head->right;
    while (v != x->key) {
        count++;
        // 키값이 같은 지와, 큰 지 작은 지 비교횟수 각각 1번씩으로 침.
        count++;
        if (v < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x->key;
}

void BST::BSTinsert(int v, infoType info) {
    struct node *p, *x;
    p = head;
    x = head->right;
    while (x != z) {
        p = x;
        if (v < x->key)
            x = x->left;
        else
            x = x->right;
    }
    x = new node(v, info, z, z);
    if (v < p->key)
        p->left = x;
    else
        p->right = x;
}

int inorderLevel = 0;
int inorderArr[2000];
int inorderIndex = 0;
// inorder traversal 결과는 inorderArr에 저장
itemType BST::inorderSearch(struct node *x) {
    if (!inorderLevel) x = head->right;
    inorderLevel++;
    if (x->left != z) inorderSearch(x->left);
    inorderArr[inorderIndex++] = x->key;
    if (x->right != z) inorderSearch(x->right);
}

int main() {
    BST T1;
    vector<int> a;
    int N = 2000;

    for (int i = 0; i < N; i++) {
        a.push_back(i);
    }

    // shuffle the vector
    random_device rd;
    default_random_engine rng(rd());
    shuffle(a.begin(), a.end(), rng);

    // insert
    for (int i = 0; i < N; i++) {
        cout << a[i] << " ";
        T1.BSTinsert(a[i], 1);
    }

    cout << endl;
    cout << "---------------------( 6 - 1 )---------------------" << endl;
    int searchCnt = 0;
    for (int i = 0; i < N; i++) {
        T1.BSTsearch(i, searchCnt);
    }

    cout << endl
         << endl;
    // shuffle할 때마다 다른 결과가 나오므로, 평균 비교 회수가 실행할 때마다 달라짐.
    cout << "Average search compare Cnt(T1): " << (double)searchCnt / (double)N << endl
         << endl;
    cout << "---------------------( 6 - 2 )---------------------" << endl;

    T1.inorderSearch(NULL);

    // print inorder
    for (int i = 0; i < N; i++) {
        cout << inorderArr[i] << " ";
    }

    BST T2;
    for (int i = 0; i < N; i++) {
        T2.BSTinsert(inorderArr[i], 1);
    }

    int searchCnt_T2 = 0;
    for (int i = 0; i < N; i++) {
        T2.BSTsearch(i, searchCnt_T2);
    }

    cout << endl
         << endl;
    // shuffle할 때마다 다른 결과가 나오므로, 평균 비교 회수가 실행할 때마다 달라짐.
    cout << "Average search compare Cnt (T2): " << (double)searchCnt_T2 / (double)N << endl
         << endl;

    cout << "---------------------( 6 - 3 )---------------------" << endl;
    T1.MaxMinLvl();

    return 0;
}