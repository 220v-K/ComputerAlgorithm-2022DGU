#include <iostream>

using namespace std;

class Stack2 {
   private:
    struct node {
        int data;
        node *next;
        node *prev;
    };
    struct node *head, *cursor;

   public:
    Stack2(int max = 100) {
        head = NULL;
        cursor = NULL;
    }
    ~Stack2() {
        head = NULL;
        cursor = NULL;
    }
    void push(int x) {
        node *temp = new node;
        temp->data = x;
        temp->next = NULL;
        temp->prev = NULL;
        if (head == NULL) {
            head = temp;
            cursor = temp;
        } else {
            cursor->next = temp;
            temp->prev = cursor;
            cursor = temp;
        }
    }
    int pop() {
        if (head == NULL) {
            cout << "Stack is empty" << endl;
            return 0;
        } else {
            int x = cursor->data;
            if (cursor == head) {
                delete cursor;
                cursor = NULL;
                head = NULL;
            } else {
                cursor = cursor->prev;
                delete cursor->next;
                cursor->next = NULL;
            }
            return x;
        }
    }
    void empty() {
        while (head != NULL) {
            pop();
        }
    }
};

int main() {
    char c;
    Stack2 acc(50);
    int x, y;

    while ((c = cin.get()) != '\n') {
        x = 0;
        while (c == ' ') {
            cin.get(c);
        }
        if (c == '+') {
            x = acc.pop() + acc.pop();
        }
        if (c == '*') {
            x = acc.pop() * acc.pop();
        }
        if (c == '-') {
            x = acc.pop();
            y = acc.pop();
            x = y - x;
        }
        if (c == '/') {
            x = acc.pop();
            y = acc.pop();
            x = y / x;
        }
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            cin.get(c);
        }
        acc.push(x);
    }
    cout << acc.pop() << endl;
}
