#include <iostream>

#include "LinkedList.hpp"

template<typename T>
LinkedList<T>::LinkedList()
    :head(nullptr)
{}

template<typename T>
LinkedList<T>::LinkedList(T data)
    :head(new Node<T> {data, nullptr})
{}

template<typename T>
LinkedList<T>::LinkedList(Node<T>* head)
    :head(head)
{}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other) {
    Node<T>* otherTemp = other.head;
    this->head = new Node<T> {otherTemp->data, nullptr};
    Node<T>* thisTemp = this->head;

    otherTemp = otherTemp->next;

    while (otherTemp != nullptr) {
        thisTemp->next = new Node<T> {otherTemp->data, nullptr};

        thisTemp = thisTemp->next;
        otherTemp = otherTemp->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        Node<T>* otherTemp = other.head;
        this->head = new Node<T> {otherTemp->data, nullptr};
        Node<T>* thisTemp = this->head;

        otherTemp = otherTemp->next;

        while (otherTemp != nullptr) {
            thisTemp->next = new Node<T> {otherTemp->data, nullptr};

            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
        }
    }

    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        const Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::insert(T data) {
    Node<T>* tail = getTail();

    if (tail == nullptr) {
        this->head = new Node<T> {data, nullptr};
        return;
    }

    tail->next = new Node<T> {data, nullptr};
}

template<typename T>
void LinkedList<T>::insertAtStart(T data) {
    auto* newHead = new Node<T> {data, head};
    head = newHead;
}

template<typename T>
void LinkedList<T>::remove(T data) {
    if (head == nullptr) {
        return;
    }

    if (head->data == data) {
        const Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    Node<T>* current = head;

    while (current->next != nullptr && current->next->data != data) {
        current = current->next;
    }

    if (current->next != nullptr) {
        const Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::reverse() {
    Node<T>* next = nullptr;
    Node<T>* current = this->head;
    Node<T>* prev = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    this->head = prev;
}

template<typename T>
void LinkedList<T>::printElements() {
    Node<T>* current = head;

    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

template<typename T>
Node<T> *LinkedList<T>::getTail() {
    if (head == nullptr) {
        return nullptr;
    }

    Node<T>* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }

    return  current;
}
