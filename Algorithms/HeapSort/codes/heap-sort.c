#include <stdio.h>

void max_heapify(int *, int, int);

void build_max_heap(int *, int);

void heap_sort(int *);

int main(void)
{
    int list[] = {2,4,6,8,1,3,5,7};
    heap_sort(list);
    for (int i = 0; i < 8; i++) {
        printf("%d\n", list[i]);
    }
    return 0;
}

void max_heapify(int * list, int start, int end)
{
    int left = 2 * start;
    int right = left + 1;
    int largest = start;

    if (left <= end && list[left] > list[start]) {
        largest = left;
    }
    if (right <= end && list[right] > list[largest]) {
        largest = right;
    }

    if (largest != start) {
        int swap = list[start];
        list[start] = list[largest];
        list[largest] = swap;
        max_heapify(list, largest, end);
    }
}

void build_max_heap(int * list, int end)
{
    int lastParentIndex = end / 2;

    for (int i = lastParentIndex; i >= 0; i--) {
        max_heapify(list, i, end);
    }
}

void heap_sort(int * list)
{
    int length = sizeof(list);
    int end = length - 1;

    build_max_heap(list, end);

    while (end >= 1)
    {
        int swap = list[0];
        list[0] = list[end];
        list[end] = swap;
        max_heapify(list, 0, --end);
    }
}
