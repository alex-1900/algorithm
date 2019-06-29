#include <stdio.h>
#include <stdlib.h>

// Merge two parts of array.
void merge(int *, int *, int, int, int);

void merge_sort(int *, int *, int, int);

int main(void)
{
    int array[] = {2, 4, 6, 8, 1, 3, 5, 7};
    int swapArray[8];
    int indexR = (int)sizeof(array) / sizeof(int) - 1;
    merge_sort(array, swapArray, 0, indexR);

    for (int i = 0; i <= indexR; i++) {
        printf("%d\n", array[i]);
    }
    return 0;
}

void merge_sort(int * array, int * swapArray, int indexL, int indexR)
{
    if (indexL < indexR) {
        int indexM = (indexL + indexR) / 2;
        merge_sort(array, swapArray, indexL, indexM);
        merge_sort(array, swapArray, indexM+1, indexR);
        merge(array, swapArray, indexL, indexM, indexR);
    }
}

void merge(int * array, int * swapArray, int indexL, int indexM, int indexR)
{
    int l = indexL;
    int r = indexM + 1;
    int k = indexL;
    while (l < indexM + 1 && r < indexR + 1)
    {
        if (array[l] > array[r]) {
            swapArray[k] = array[r];
            r++;
        } else {
            swapArray[k] = array[l];
            l++;
        }
        k++;
    }
    while (l < indexM + 1) {
        swapArray[k] = array[l];
        k++;
        l++;
    }
    while (r < indexR + 1)
    {
        swapArray[k] = array[r];
        k++;
        r++;
    }
    for (int i = indexL; i <= indexR; i++) {
        array[i] = swapArray[i];
    }
}
