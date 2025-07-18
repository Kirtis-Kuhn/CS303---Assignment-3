#ifndef QUEUE_CPP
#define QUEUE_CPP
#include "Queue.h"

template <typename T>
Queue<T>::Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
    frontPtr = rearPtr = nullptr;
    Node* current = other.frontPtr;

    while (current) {
        push(current->data);  // Reuse your push() to add a deep copy
        current = current->next;
    }
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        clear();  // Delete old contents safely

        Node* current = other.frontPtr;
        while (current) {
            push(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Queue<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Queue<T>::push(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        frontPtr = rearPtr = newNode;
    }
    else {
        rearPtr->next = newNode;
        rearPtr = newNode;
    }
    count++;
}

template <typename T>
void Queue<T>::pop() {
    if (empty()) return;

    Node* temp = frontPtr;
    frontPtr = frontPtr->next;
    delete temp;
    count--;

    if (!frontPtr) rearPtr = nullptr;
}

template <typename T>
T Queue<T>::front() const {
    if (empty()) throw runtime_error("Queue is empty");
    return frontPtr->data;
}

template <typename T>
int Queue<T>::size() const {
    return count;
}

template <typename T>
bool Queue<T>::empty() const {
    return frontPtr == nullptr;
}

template <typename T>
void Queue<T>::move_to_rear() {
    if (size() <= 1) return;
    T temp = front();
    pop();
    push(temp);
}

template <typename T>
void Queue<T>::display() const {
    Node* current = frontPtr;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
bool  Queue<T>::contains(const T& value) const {
    Node* current = frontPtr;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}
#endif // QUEUE_CPP