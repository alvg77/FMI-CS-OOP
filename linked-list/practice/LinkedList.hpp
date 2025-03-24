#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class LinkedList {
public:
    LinkedList();
    explicit LinkedList(T data);
    explicit LinkedList(Node<T>* head);
    LinkedList(const LinkedList& other);

    LinkedList& operator=(const LinkedList& other);

    ~LinkedList();

    void insert(T data);
    void insertAtStart(T data);
    void remove(T data);
    void reverse();
    void printElements();

private:
    Node<T>* head;

    Node<T>* getTail();
};

#include "LinkedList.inl.hpp"

#endif
