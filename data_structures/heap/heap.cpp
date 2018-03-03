#include "heap.hpp"

void print(int* array, int size)  // O(n)
{
    for (int i = 0; i < size; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

void heapify(int* heap, int size, int parent)  // O(log n)
{
    int min = parent;
    // Calculate parent's left children
    int left = 2 * parent + 1;
    // Check if left children holds a smaller value than parent
    if (left < size && heap[left] < heap[min])
        // Assign children to min if it is smaller
        min = left;
    // Do the same for the right children
    int right = 2 * parent + 2;
    if (right < size && heap[right] < heap[min])
        min = right;
    if (min != parent)
    {
        // Swap parent with min if they are unequal
        std::swap(heap[parent], heap[min]);
        // Recursively swap parent and child until tree has a heap structure
        heapify(heap, size, min);
    }
}

void build(int* heap, int size)  // O(n)
{
    // The lowest level only contains leaves (nodes without further children)
    // The second Lowest level holds the first valid nodes and ends at (size / 2 - 1)
    for (int parent = size / 2 - 1; parent >= 0; parent--)
        // Work bottom-up and call heapify for each node
        // This makes sure that the whole tree under the current parent has heap structure
        heapify(heap, size, parent);
}

int find(int* heap, int size, int value, int parent=0)  // O(n)
{
    // Check if parent is the searched value
    if (heap[parent] == value)
        return parent;
    // Calculate index of parent's left children
    int left = 2 * parent + 1;
    // Compare heap's value of the left children to the searched value
    // If heap's value equals the searched value, the function will return it at the next recursion
    // If heap's value is smaller than the searched value, it might occur in later recursions
    // Else the whole tree can be skipped because there is no chance of finding the searched value
    if (left < size && heap[left] <= value)
    {
        // Call the function with the left children as parent and search through the sub tree
        int result = find(heap, size, value, left);
        // Return the searched index if it was found
        if (result != FAILED)
            return result;
    }
    // Do the same thing for the right children
    int right = 2 * parent + 2;
    if (right < size && heap[right] <= value)
    {
        int result = find(heap, size, value, right);
        if (result != FAILED)
            return result;
    }
    // Return failed if neither the left nor the right children yielded a result
    return FAILED;
}

void heapsort(int* heap, int size)  // O(n log n)
{
    // Build could be called to ensure the heap structure
    // build(heap, size);
    for (int parent = size - 1; parent > 0; parent--)
    {
        // Smallest element is first, swap it with the last
        std::swap(heap[0], heap[parent]);
        // Make sure the next smallest element is at the first position
        // Call heapify just for the unsorted part of the heap to keep the sorted part
        heapify(heap, parent, 0);
    }
}
