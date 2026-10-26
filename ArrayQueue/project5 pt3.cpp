// ArrayBasedQueuePrj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

template <class T>
class ArrayQueue {
public:

    ArrayQueue();
    ArrayQueue(int);
    void enqueue(T item);/*Inserts an element at the rear of the queue. */
    void dequeue();/*Removes the first element of the queue.*/
    T front();/*Returns, but does not remove, the first element of the queue.*/
    bool empty() {
        return (currentNumberOfElements == 0);
    }
    int size() {
        return (currentNumberOfElements);
    }
    bool expand(int newSize); //expanding the dynamic array
    void printQueue();
    template <class T> friend  ostream& operator<<(ostream& os, const ArrayQueue<T>&);
    /*Default array capacity. */
    int CAPACITY = 10;
private:

    int first; // index of the front element
    int last; // index of the last element
    int currentNumberOfElements = 0;// current number of elements
    /** Generic array used for storage of queue elements. */
    T* data; // generic array used for storage

};
template <class T>
ArrayQueue<T>::ArrayQueue() {    // constructs queue with default capacity
    data = new T[CAPACITY];
    first = 0;
    last = -1;
    currentNumberOfElements = 0;
}

template <class T>
ArrayQueue<T>::ArrayQueue(int CAPACITY_) {  // constructs queue with given capacity
    CAPACITY = CAPACITY_;
    data = new T[CAPACITY];
    first = 0;
    last = -1;
    currentNumberOfElements = 0;
}

template <class T>
void ArrayQueue<T>::enqueue(T e) {

    if (currentNumberOfElements < (CAPACITY)) {
        int avail = (last + 1) % CAPACITY;   // use modular arithmetic
        data[avail] = e;
        ++currentNumberOfElements;
        last = (last + 1) % CAPACITY;
    }
    else
    {

        int newCAPACITY = CAPACITY + (CAPACITY / 4);
        if (expand(newCAPACITY)) {
            int avail = (last + 1) % CAPACITY;   // use modular arithmetic
            data[avail] = e;
            ++currentNumberOfElements;
            last = (last + 1) % CAPACITY;
            cout << "\nexpansion. New Capacity is" << CAPACITY << endl;
        }
        else
            cout << "Problem while expanding the queue!\nunsuccessful push operation.";
    }

}

template <class T>
T ArrayQueue<T>::front() {
    if (empty()) {
        cout << "Queue is empty!\n"; //I would throw an exception.
        return;
    }
    return data[first];
}

template <class T>
void ArrayQueue<T>::dequeue() {
    if (empty()) {
        cout << "Queue is empty!\n";
        return;
    }
    T answer = data[first];
    first = (first + 1) % CAPACITY;
    --currentNumberOfElements;
}
template <class T>
bool ArrayQueue<T>::expand(int newCAPACITY) { //expanding the array
    if (newCAPACITY > CAPACITY) {
        T* tmpArray = new T[newCAPACITY];
        int j = 0;
        for (int i = first; i != last; i = (i + 1) % CAPACITY)
            tmpArray[j++] = data[i];

        tmpArray[j] = data[last];
        delete[] data;
        data = tmpArray;
        CAPACITY = newCAPACITY;
        first = 0;
        last = size() - 1;
        return true;
    }
    else
        return false;
}

template <class T>
void ArrayQueue<T>::printQueue() {

    cout << "[";
    if (!empty()) {
        cout << data[first];
        for (int i = (first + 1) % CAPACITY; i != ((last + 1) % CAPACITY); i = (i + 1) % CAPACITY)
        {
            cout << ", " << data[i];
        }//end for

    }
    cout << "]";

}
template <class T>
ostream& operator<<(ostream& os, const ArrayQueue<T>& queueObj) {

    os << "[";
    if (1) {
        os << queueObj.data[queueObj.first];
        for (int i = (queueObj.first + 1) % queueObj.CAPACITY; i != ((queueObj.last + 1) % queueObj.CAPACITY); i = (i + 1) % queueObj.CAPACITY)
        {
            os << ", " << queueObj.data[i];
        }//end for

    }
    os << "]";
    return os;
}