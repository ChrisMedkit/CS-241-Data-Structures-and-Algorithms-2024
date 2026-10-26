#include <iostream>
using namespace std;

template <class T>
class Stack {
public:
    Stack() : top(-1), CAPACITY(10) {
        data = new T[CAPACITY];
    }

    // Copy constructor
    Stack(const Stack& other) : top(other.top), CAPACITY(other.CAPACITY) {
        data = new T[CAPACITY];
        for (int i = 0; i <= top; ++i) {
            data[i] = other.data[i];
        }
    }

    // Destructor
    ~Stack() {
        delete[] data;
    }

    // Copy assignment operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            top = other.top;
            CAPACITY = other.CAPACITY;
            data = new T[CAPACITY];
            for (int i = 0; i <= top; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push(T item);
    void pop();
    bool empty() { return (top == -1); }
    int size() { return (top + 1); }
    int getCAPACITY() { return CAPACITY; }
    T atTop();

private:
    int CAPACITY;
    int top;
    T* data;

    bool expand(int newSize); //expanding the array
    bool shrink(int newSize); //reducing the size of the array
};

template <class T>
void Stack<T>::push(T item) {
    // Pre-condition: stack is not full.
    if (top < (CAPACITY - 1)) {
        ++top;
        data[top] = item;
    }
    else {
        int newCAPACITY = CAPACITY + (CAPACITY / 4);
        if (expand(newCAPACITY)) {
            ++top;
            data[top] = item;
        }
        else {
            cout << "Problem while expanding the stack!\nUnsuccessful push operation.";
        }
    }
}

template <class T>
void Stack<T>::pop() {
    // Pre-condition: stack is not empty
    if (!empty()) {
        --top;
        if ((top + 1) <= (CAPACITY / 2) && (top + 1) > 10) {
            int newCAPACITY = CAPACITY - (CAPACITY / 4);
            if (!shrink(newCAPACITY)) {
                cout << "Problem while shrinking the stack!\n";
            }
        }
    }
    else {
        cout << "Stack Underflow!\n";
    }
}

template <class T>
T Stack<T>::atTop() {
    // Pre-condition: stack is not empty
    if (!empty()) {
        return data[top];
    }
    else {
        cout << "Stack Underflow!\n";
        exit(1); // Terminate the program
    }
}

template <class T>
bool Stack<T>::expand(int newCAPACITY) {
    // Expanding the array
    if (newCAPACITY > CAPACITY) {
        T* tmpArray = new T[newCAPACITY];
        for (int i = 0; i < size(); ++i) {
            tmpArray[i] = data[i];
        }
        delete[] data;
        data = tmpArray;
        CAPACITY = newCAPACITY;
        return true;
    }
    else {
        return false;
    }
}

template <class T>
bool Stack<T>::shrink(int newCAPACITY) {
    // Reducing the size of the array
    if (newCAPACITY < CAPACITY) {
        T* tmpArray = new T[newCAPACITY];
        for (int i = 0; i < newCAPACITY; ++i) {
            tmpArray[i] = data[i];
        }
        delete[] data;
        data = tmpArray;
        CAPACITY = newCAPACITY;
        return true;
    }
    else {
        return false;
    }
}
