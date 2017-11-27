#include <iostream>

// https://gist.github.com/mopkaloppt/63108d67fed6d3161ad9

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are printed to the screen.
void print(int* heap, int size)
{
    for(int i = 0; i < size; i++)
        std::cout << heap[i] << " ";
    std::cout << std::endl;
}

// PRE:  subtrees rooted at leftChild and rightChild of i are heaps.
// POST: subtree rooted at i is a heap.
void swapDown(int* heap, int i, int size)
{
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int min = i;
    // find who holds smallest element of i and its two children
    if(leftChild < size && heap[leftChild] < heap[min])
        min = leftChild;
    if(rightChild < size && heap[rightChild] < heap[min])
        min = rightChild;
    // if a child holds smallest element, swap i's element to that child
    // and recurse.
    if(min != i)
    {
        std::swap(heap[i], heap[min]);
        swapDown(heap, min, size);
    }
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are a heap.
void heapify(int* heap, int size)
{
    for (int i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, i, size);
}

int find(const int* heap, int n, int i=0)
{
    if (heap[i] == n)
        return i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    // TODO: Continue writing
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are sorted in descending order. 
void sort(int* heap, int size)
{
    heapify(heap, size);  // Heapify algorithm
    for (int i = size - 1; i > 0; i--)
    {
        std::swap(heap[0], heap[i]);
        swapDown(heap, 0, i);
    }
}

void printHeap(int *heap, int size, int node=0, int d=0)
{
    int left = (2 * node) + 1;
    int right = left + 1;

    if (right < size)
        printHeap(heap, size, right, d + 3);

    std::cout << std::string(d, ' ') + std::to_string(heap[node]) << std::endl;

    if (left < size)
        printHeap(heap, size, left, d + 3);
}

int main()
{
    int heap[12] = {10,9,8,7,6,5,4,3,2,1,0,12};
    heapify(heap, 12);
    print(heap, 12);
    printHeap(heap, 12);

    return 0;
}
