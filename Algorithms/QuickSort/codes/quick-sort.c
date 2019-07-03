#include <stdio.h>

void quick_sort(int *, int, int);
int partition(int *, int, int);

int main(void)
{
    int list[] = {2,4,6,8,1,3,5,7};
    quick_sort(list, 0, 7);
    for (int i = 0; i < 8; i++) {
        printf("%d\n", list[i]);
    }
    return 0;
}

void quick_sort(int * list, int start, int end)
{
    if (start < end) {
        int mid = partition(list, start, end);
        quick_sort(list, start, mid - 1);
        quick_sort(list, mid + 1, end);
    }
}

int partition(int * list, int start, int end)
{
    int swap;
    int pivot = list[end];
    int current = start - 1;
    for (int i = start; i <= end - 1; i++) {
        if (list[i] < pivot) {
            current++;
            swap = list[i];
            list[i] = list[current];
            list[current] = swap;
        }
    }
    swap = list[end];
    list[end] = list[current + 1];
    list[current + 1] = swap;
    return current + 1;
}
