#include <iostream>

// https://gist.github.com/mopkaloppt/63108d67fed6d3161ad9

void printHeap(int* heap, int size)
{
    for(int i = 0; i < size; i++)
        std::cout << heap[i] << " ";
    std::cout << std::endl;
}

void swapDown(int* heap, int i, int size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min = i;
    // find who holds smallest element of i and its two children
    if(left < size && heap[left] < heap[min])
        min = left;
    if(right < size && heap[right] < heap[min])
        min = right;
    // if a child holds smallest element, swap i's element to that child
    // and recurse.
    if(min != i)
    {
        std::swap(heap[i], heap[min]);
        swapDown(heap, min, size);
    }
}

void heapify(int* heap, int size)
{
    for (int i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, i, size);
}

int find(int* heap, int size, int value, int root=0)
{
    // Check if root is the searched value
    if (heap[root] == value)
        return root;
    // Calculate index of roots left children
    int left = 2 * root + 1;
    // Check if the calculated index is out of bounds
    // Compare the heap value of the left children to the searched value
    // If the heap value equals the searched value, the function will return at the next iteration
    // If the heap value is smaller than the searched value, it might occur in later iterations of this sub part
    // Else the whole sub part can be skipped because there is no chance of finding the searched value
    if (left < size && heap[left] <= value)
    {
        std::cout << "root " << root << " left " << left << " heap " << heap[left] << std::endl;
        // Call the function with the left children as root and search through the sub part
        int result = find(heap, size, value, left);
        // Return the searched index if it was found
        if (result != -1)
            return result;
    }
    // Do the same thing for the right children
    int right = 2 * root + 2;
    if (right < size && heap[right] <= value)
    {
        std::cout << "root " << root << " right " << right << " heap " << heap[right] << std::endl;
        int result = find(heap, size, value, right);
        if (result != -1)
            return result;
    }
    // Return -1 if neither the left nor the right children yielded a result
    return -1;
}

void sort(int* heap, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        std::swap(heap[0], heap[i]);
        swapDown(heap, 0, i);
    }
}

// TODO: Remove before handing in
void heapStructure(int *heap, int size, int node=0, int d=0)
{
    int left = (2 * node) + 1;
    int right = left + 1;

    if (right < size)
        heapStructure(heap, size, right, d + 3);

    std::cout << std::string(d, ' ') + std::to_string(heap[node]) << std::endl;

    if (left < size)
        heapStructure(heap, size, left, d + 3);
}

int main()
{
    int heap[12] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 12};
    heapify(heap, 12);
    heapStructure(heap, 12);
    printHeap(heap, 12);
    int m = find(heap, 12, 12);
    std::cout << "result: " << m << std::endl;


    return 0;
}
