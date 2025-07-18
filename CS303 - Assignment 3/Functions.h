#pragma once
#include "Queue.h"

// Declare function templates
template <typename T>
void readFile(ifstream& dataFile, Queue<T>& q);

template <typename T>
void menu(Queue<T>& q, string& menuTitle);

template <typename T>
int linear_search_last(const vector<T>& items, const T& target, size_t pos);

template <typename T>
vector<T> deepCopyToVector(Queue<T> q);

// Non-template helper
void mainMenu(Queue<int>& intQueue, Queue<string>& strQueue, Queue<float>& floQueue);
bool isInteger(const string& str);
