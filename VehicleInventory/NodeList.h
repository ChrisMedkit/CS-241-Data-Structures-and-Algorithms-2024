#pragma once
#ifndef NODELIST
#define NODELIST

#include <iostream>
using namespace std;

template <class Elem>
class NodeList {
private:
    class Node {
    public:
        Elem elem;
        Node* prev;
        Node* next;
    };

public:
    class Iterator {
    public:
        Elem& operator*();
        bool operator==(const Iterator& p) const;
        bool operator!=(const Iterator& p) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        friend class NodeList<Elem>;

    private:
        Node* v;
        Iterator(Node* u);
    };

public:
    NodeList();
    int size() const;
    bool empty() const;
    Iterator begin() const;
    Iterator end() const;
    void insertFront(const Elem& e);
    void insertBack(const Elem& e);
    void insert(const Iterator& p, const Elem& e);
    void eraseFront();
    void eraseBack();
    void erase(const Iterator& p);
    ~NodeList();
    NodeList(const NodeList<Elem>& obj);
    NodeList<Elem>& operator=(const NodeList<Elem>& rhs);

private:
    int n;
    Node* header;
    Node* trailer;
};

template <class Elem>
NodeList<Elem>::Iterator::Iterator(Node* u) : v(u) {}

template <class Elem>
Elem& NodeList<Elem>::Iterator::operator*() {
    return v->elem;
}

template <class Elem>
bool NodeList<Elem>::Iterator::operator==(const Iterator& p) const {
    return v == p.v;
}

template <class Elem>
bool NodeList<Elem>::Iterator::operator!=(const Iterator& p) const {
    return v != p.v;
}

template <class Elem>
typename NodeList<Elem>::Iterator& NodeList<Elem>::Iterator::operator++() {
    v = v->next;
    return *this;
}

template <class Elem>
typename NodeList<Elem>::Iterator NodeList<Elem>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++*this;
    return temp;
}

template <class Elem>
typename NodeList<Elem>::Iterator& NodeList<Elem>::Iterator::operator--() {
    v = v->prev;
    return *this;
}

template <class Elem>
NodeList<Elem>::NodeList() : n(0) {
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}

template <class Elem>
int NodeList<Elem>::size() const {
    return n;
}

template <class Elem>
bool NodeList<Elem>::empty() const {
    return (n == 0);
}

template <class Elem>
typename NodeList<Elem>::Iterator NodeList<Elem>::begin() const {
    return Iterator(header->next);
}

template <class Elem>
typename NodeList<Elem>::Iterator NodeList<Elem>::end() const {
    return Iterator(trailer);
}

template <class Elem>
void NodeList<Elem>::erase(const Iterator& p) {
    Node* v = p.v;
    Node* w = v->next;
    Node* u = v->prev;
    u->next = w;
    w->prev = u;
    delete v;
    n--;
}

template <class Elem>
void NodeList<Elem>::eraseFront() {
    erase(begin());
}

template <class Elem>
void NodeList<Elem>::eraseBack() {
    erase(--end());
}

template <class Elem>
void NodeList<Elem>::insert(const typename NodeList<Elem>::Iterator& p, const Elem& e) {
    Node* w = p.v;
    Node* u = w->prev;
    Node* v = new Node;
    v->elem = e;
    v->next = w;
    w->prev = v;
    v->prev = u;
    u->next = v;
    n++;
}

template <class Elem>
void NodeList<Elem>::insertFront(const Elem& e) {
    insert(begin(), e);
}

template <class Elem>
void NodeList<Elem>::insertBack(const Elem& e) {
    insert(end(), e);
}

template <class Elem>
NodeList<Elem>::~NodeList() {
    while (!empty()) {
        eraseFront();
    }
    delete header;
    delete trailer;
}

template <class Elem>
NodeList<Elem>::NodeList(const NodeList<Elem>& obj) : n(0) {
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;

    if (obj.header != obj.trailer) {
        for (Node* curr = obj.header->next; curr != obj.trailer; curr = curr->next) {
            insertBack(curr->elem);
        }
    }
}

template <class Elem>
NodeList<Elem>& NodeList<Elem>::operator=(const NodeList<Elem>& rhs) {
    if (this != &rhs) {
        while (!empty()) eraseFront();
        for (Node* curr = rhs.header->next; curr != rhs.trailer; curr = curr->next) {
            insertBack(curr->elem);
        }
    }
    return *this;
}

#endif
