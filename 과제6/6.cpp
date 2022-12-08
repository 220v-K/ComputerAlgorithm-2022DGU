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
            // left child node �� subtree���� value�� ã�Ҵٸ� return
            if (downlevel != 0)
                return downlevel;
            // left child node �� subtree���� value�� �� ã�Ҵٸ� right child node �� subtree���� �˻�
            // left child node �� subtree�� ���ٸ� ������ right subtree�� ������.
            // input value�� tree�� �����ϴ� value�� �����߱� ����.
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
        // Ű���� ���� ����, ū �� ���� �� ��Ƚ�� ���� 1�������� ħ.
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
// inorder traversal ����� inorderArr�� ����
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
    // shuffle�� ������ �ٸ� ����� �����Ƿ�, ��� �� ȸ���� ������ ������ �޶���.
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
    // shuffle�� ������ �ٸ� ����� �����Ƿ�, ��� �� ȸ���� ������ ������ �޶���.
    cout << "Average search compare Cnt (T2): " << (double)searchCnt_T2 / (double)N << endl
         << endl;

    cout << "---------------------( 6 - 3 )---------------------" << endl;
    T1.MaxMinLvl();

    return 0;
}