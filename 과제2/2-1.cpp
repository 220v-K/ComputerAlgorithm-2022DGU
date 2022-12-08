#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stack1 {
   private:
    int *stack;
    int p;

   public:
    Stack1(int max = 100) {
        stack = new int[max];
        p = 0;
    }
    ~Stack1() {
        delete stack;
    }
    inline void push(int x) {
        stack[p++] = x;
    }
    inline int pop() {
        return stack[--p];
    }
    inline int empty() {
        return !p;
    }
};

int main() {
    char c;
    Stack1 acc(50);
    int x;

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
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            cin.get(c);
        }
        acc.push(x);
    }
    cout << acc.pop() << endl;
}
