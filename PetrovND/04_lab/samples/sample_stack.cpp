#include "stack.h"
using namespace std;

int main() {
    Stack<int> myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    Stack<int> anotherStack(myStack);

    Stack<int> assignedStack = myStack;

    cout << "Top element of myStack: " << myStack.top() << endl;

    cout << "Pop elements from myStack:" << endl;
    while (!myStack.isEmpty()) {
        cout << myStack.top() << " ";
        myStack.pop();
    }
    cout << endl;

    cout << "Is anotherStack empty? " << (anotherStack.isEmpty() ? "Yes" : "No") << endl;
    cout << "Is assignedStack full? " << (assignedStack.isFull() ? "Yes" : "No") << endl;

    return 0;
}