#include <iostream>

#define FAILED (-1)  // Value for failed search, could be any other

void print(int* array, int size)  // O(n)
{
    for(int i = 0; i < size; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

void heapify(int* heap, int size, int root)  // O(log n)
{
    int min = root;
    // Calculate root's left and right children
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    // Find out if and which of root's two children holds the minimal value
    if(left < size && heap[left] < heap[min])
        // Assign children index to min if it is smaller
        min = left;
    if(right < size && heap[right] < heap[min])
        min = right;
    if(min != root)
    {
        // Swap root with min if they are unequal
        std::swap(heap[root], heap[min]);
        // Recursively swap root and child until tree has a heap structure
        heapify(heap, size, min);
    }
}

void build(int* heap, int size)  // O(n)
{
    // Lowest level with leaves begins at size / 2 - 1
    // Just go through levels without leaves and heapify them from lowest to highest
    for (int root = size / 2 - 1; root >= 0; root--)
        heapify(heap, size, root);
}

int find(int* heap, int size, int value, int root=0)  // O(n)
{
    // Check if root is the searched value
    if (heap[root] == value)
        return root;
    // Calculate index of root's left children
    int left = 2 * root + 1;
    // Check if the calculated index is out of bounds
    // Compare the heap's value of the left children to the searched value
    // If the heap's value equals the searched value, the function will return at the next iteration
    // If the heap's value is smaller than the searched value, it might occur in later iterations of this sub part
    // Else the whole sub part can be skipped because there is no chance of finding the searched value
    if (left < size && heap[left] <= value)
    {
        std::cout << "root " << heap[root] << " left " << heap[left] << std::endl;
        // Call the function with the left children as root and search through the sub part
        int result = find(heap, size, value, left);
        // Return the searched index if it was found
        if (result != FAILED)
            return result;
    }
    // Do the same thing for the right children
    int right = 2 * root + 2;
    if (right < size && heap[right] <= value)
    {
        std::cout << "root " << heap[root] << " right " << heap[right] << std::endl;
        int result = find(heap, size, value, right);
        if (result != FAILED)
            return result;
    }
    // Return -1 if neither the left nor the right children yielded a result
    return -1;
}

void sort(int* heap, int size)  // O(n log n)
{
    // Make sure array has heap structure
    build(heap, size);
    // Build creates a min heap -> sort in descending order
    for (int root = size - 1; root > 0; root--)
    {
        // Smallest element is first, swap it with the last
        std::swap(heap[0], heap[root]);
        // Make sure the second smallest element is at first position
        heapify(heap, root, 0);
    }
}

int main()
{
    int heap[9] = {6, 2, 3, 8, 7, 5, 10, 12, 1};
    std::cout << "array: ";
    print(heap, 9);

    // 4.
    build(heap, 9);
    std::cout << "heap: ";
    print(heap, 9);

    // 6.
    std::cout << "start searching 10" << std::endl;
    int result = find(heap, 9, 10);
    if (result != FAILED)
        std::cout << "value 10 found at index " << result << std::endl;
    else
        std::cout << "value 10 not found" << std::endl;

    // 7.
    std::cout << "start searching 34" << std::endl;
    result = find(heap, 9, 34);
    if (result != FAILED)
        std::cout << "value 34 found at index " << result << std::endl;
    else
        std::cout << "value 34 not found" << std::endl;

    // 5.
    sort(heap, 9);
    std::cout << "sorted: "; print(heap, 9);

    return 0;
}
