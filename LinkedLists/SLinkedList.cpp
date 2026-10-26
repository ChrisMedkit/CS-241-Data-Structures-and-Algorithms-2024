#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//singley linked list implementation start

template <class E> class SLinkedList;

template <class E>
class SNode {
public:
    const E& getElem() const { return elem; }
    SNode<E>* getNext() const { return next; }
private:
    E elem;
    SNode<E>* next;
    friend class SLinkedList<E>;
};

template <class E>
class SLinkedList {
public:
    SLinkedList();
    SLinkedList(const SLinkedList<E>&);
    ~SLinkedList();
    SLinkedList<E>& operator=(const SLinkedList<E>&);

    bool empty() const;
    const E& front() const;
    void addFront(const E& e);
    void addBack(const E& e);
    void removeFront();
    SNode<E>* getHead() const { return head; }
    SNode<E>* getTail() const { return tail; }

    int getNumberOfCopies(const E& key) const;
    SLinkedList<E> operator*(const SLinkedList<E>& other) const;

private:
    SNode<E>* head;
    SNode<E>* tail;
};

template <class E>
SLinkedList<E>::SLinkedList() : head(NULL), tail(NULL) { }

template <class E>
bool SLinkedList<E>::empty() const {
    return head == NULL;
}

template <class E>
const E& SLinkedList<E>::front() const {
    return head->elem;
}

template <class E>
void SLinkedList<E>::addFront(const E& e) {
    SNode<E>* v = new SNode<E>;
    v->elem = e;
    v->next = head;
    head = v;
    if (tail == NULL)
        tail = v;
}

template <class E>
void SLinkedList<E>::addBack(const E& e) {
    SNode<E>* newNode = new SNode<E>;
    newNode->elem = e;
    newNode->next = NULL;
    if (tail == NULL) {
        tail = newNode;
        head = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

template <class E>
void SLinkedList<E>::removeFront() {
    SNode<E>* old = head;
    head = old->next;
    if (head == NULL) tail = NULL;
    delete old;
}

template <class E>
SLinkedList<E>::~SLinkedList() {
    while (!empty())
        removeFront();
}

template <class E>
SLinkedList<E>& SLinkedList<E>::operator=(const SLinkedList<E>& rhs) {
    if (this != &rhs) {
        while (!empty())
            removeFront();

        for (SNode<E>* current = rhs.head; current != NULL; current = current->getNext()) {
            addBack(current->getElem());
        }
    }
    return *this;
}



template <class E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& obj) : head(NULL), tail(NULL) {
    *this = obj;
}

template <class E>
int SLinkedList<E>::getNumberOfCopies(const E& key) const {
    int count = 0;
    for (SNode<E>* current = head; current != NULL; current = current->getNext()) {
        if (current->getElem() == key) {
            ++count;
        }
    }
    return count;
}

template <class E>
SLinkedList<E> SLinkedList<E>::operator*(const SLinkedList<E>& other) const {
    SLinkedList<E> result;
    for (SNode<E>* current = head; current != NULL; current = current->getNext()) {
        for (SNode<E>* otherCurrent = other.head; otherCurrent != NULL; otherCurrent = otherCurrent->getNext()) {
            if (current->getElem() == otherCurrent->getElem()) {
                result.addBack(current->getElem());
                break;
            }
        }
    }
    return result;
}

template <class E>
void printSLL(SLinkedList<E> sll) {
    int nodeRank = 0;
    for (SNode<E>* current = sll.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "localSLL.Node " << nodeRank << ": " << current->getElem() << endl;
    }
}

//singley linked list implementation end


//start of main function

int main() {
    srand(time(nullptr));

    SLinkedList<int> intSLL1;
    for (int i = 0; i < 10; ++i)
        intSLL1.addBack(rand() % 101);

    int nodeRank = 0;
    for (SNode<int>* current = intSLL1.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "intSLL1.Node " << nodeRank << ": " << current->getElem() << endl;
    }

    // testing the copy constructor

    cout << "Number of copies of 50: " << intSLL1.getNumberOfCopies(50) << endl;

    SLinkedList<int> intSLL2;
    for (int i = 0; i < 10; ++i)
        intSLL2.addFront(rand() % 101);

    nodeRank = 0;
    for (SNode<int>* current = intSLL2.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "intSLL2.Node " << nodeRank << ": " << current->getElem() << endl;
    }

    intSLL2 = intSLL1;

    if (intSLL2.empty())
        cout << "intSLL2 is empty. Fail!" << endl;

    nodeRank = 0;
    for (SNode<int>* current = intSLL2.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "after assigning. intSLL2.Node " << nodeRank << ": " << current->getElem() << endl;
    }

    nodeRank = 0;
    for (SNode<int>* current = intSLL1.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "intSLL1.Node " << nodeRank << ": " << current->getElem() << endl;
    }

    printSLL(intSLL1);

    nodeRank = 0;
    for (SNode<int>* current = intSLL1.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "caller.intSLL1.Node " << nodeRank << ": " << current->getElem() << endl;
    }
    //end test


    // test intersection operator
    SLinkedList<int> intSLL3;
    intSLL3.addBack(3);
    intSLL3.addBack(7);
    intSLL3.addBack(9);
    intSLL3.addBack(10);

    SLinkedList<int> intersectionList = intSLL1 * intSLL3;

    nodeRank = 0;
    for (SNode<int>* current = intersectionList.getHead(); current != NULL; current = current->getNext()) {
        ++nodeRank;
        cout << "intersectionList.Node " << nodeRank << ": " << current->getElem() << endl;
    }

    return 0;
}
