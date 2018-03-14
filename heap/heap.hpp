#ifndef HEAPSORT_HEAP_HPP
#define HEAPSORT_HEAP_HPP

#include <iostream>

#define FAILED (-1)  // Value for failed search, (-1) because arrays have no negative indices

void print(int* array, int size);
void heapify(int* heap, int size, int parent);
void build(int* heap, int size);
int find(int* heap, int size, int value, int parent=0);
void heapsort(int* heap, int size);

#endif //HEAPSORT_HEAP_HPP
