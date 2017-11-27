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

int find(const int* heap, int size, int n, int root=0)
{
    if (heap[root] == n)  // Check if root is searched value
        return root;
    int left = 2 * root + 1;  // Get position of left children relative to root
    if (left < size)
    {
        std::cout << "root " << root << " left " << left << " heap " << heap[left] << std::endl;
        if (heap[left] == n)
            return left;
        if (heap[left] < n)
        {
            int res = find(heap, size, n, left);
            if (res != -1)
                return res;
        }
    }
    int right = 2 * root + 2;
    if (right < size)
    {
        std::cout << "root " << root << " right " << right << " heap " << heap[right] << std::endl;
        if (heap[right] == n)
            return right;
        if (heap[right] < n)
        {
            int res = find(heap, size, n, right);
            if (res != -1)
                return res;
        }
    }

    return -1;
}

//PRE:  The capacity of the array pointed to by heap is at least size.
//POST: The first size elements of heap are sorted in descending order. 
void sort(int* heap, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        std::swap(heap[0], heap[i]);
        swapDown(heap, 0, i);
    }
}

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
    std::cout << "res: " << m << std::endl;


    return 0;
}
