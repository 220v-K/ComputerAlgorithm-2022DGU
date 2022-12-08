#include <iostream>

using namespace std;

struct node {
    char info;
    struct node *l;
    struct node *r;
};

class Stack {
   private:
    struct node *stack;
    int p;

   public:
    Stack(int max = 100) {
        stack = new node[max];
        p = 0;
    }
    ~Stack() {
        delete stack;
    }
    inline void push(node v) {
        stack[p++] = v;
    }
    inline node pop() {
        return stack[--p];
    }
    inline int empty() {
        return !p;
    }
};

void showStructure(node *p, int level) {
    int j;

    if (p != NULL) {
        showStructure(p->r, level + 1);
        for (j = 0; j < level; j++)
            cout << "\t";
        cout << p->info;
        if ((p->l != NULL) && (p->r != NULL))
            cout << "<";
        else if (p->r != NULL)
            cout << "/";
        else if (p->l != NULL)
            cout << "\\";
        cout << endl;
        showStructure(p->l, level + 1);
    }
}

void inorder(node *p) {
    if (p->l != NULL) {
        cout << "(";
        inorder(p->l);
    }
    cout << p->info;
    if (p->r != NULL) {
        inorder(p->r);
        cout << ")";
    }
}

int main() {
    struct node *x, *root;
    char c;
    int cnt = 0;
    Stack s(50);

    // make expression tree
    while ((c = cin.get()) != '\n') {
        while (c == ' ') cin.get(c);

        x = new node;
        x->info = c;
        if (c == '+' || c == '*') {
            struct node *temp = new node;
            *temp = s.pop();
            x->l = temp;
            struct node *temp2 = new node;
            *temp2 = s.pop();
            x->r = temp2;
        }
        s.push(*x);
    }

    root = new node;
    *root = s.pop();

    // print tree
    // print(root);
    cout << endl;
    showStructure(root, 1);
    cout << endl;
    inorder(root);
}