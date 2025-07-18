#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>
using namespace std;

template <typename T>
class Queue {
private:
    // Node structure
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontPtr; // Points to the front of the queue
    Node* rearPtr;  // Points to the rear of the queue
    int count;      // Number of elements in the queue

public:
    // Constructor
    Queue();

    // Destructor
    ~Queue();

    // Core functions
    void push(const T& value);  // Add to rear
    void pop();                 // Remove from front
    T front() const;            // Access front element
    int size() const;           // Get number of elements
    bool empty() const;         // Check if queue is empty
    bool contains(const T& value) const;

    // Special function for assignment
    void move_to_rear();        // Move front element to rear

    // Utility
    void display() const;       // Optional: display queue content
};

#include "Queue.cpp"
#endif // QUEUE_H
