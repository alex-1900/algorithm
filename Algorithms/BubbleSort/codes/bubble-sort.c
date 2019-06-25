#include <stdio.h>

int main(void)
{
    int list[] = {2,4,6,8,1,3,5,7};
    int swap;

    for (int i = 0; i < 7; i++) {
        for (int n = 0; n < 7; n++) {
            if (list[n] > list[n+1]) {
                swap = list[n];
                list[n] = list[n+1];
                list[n+1] = swap;
            }
        }
    }

    for (int m = 0; m < 8; m++) {
        printf("%d\n", list[m]);
    }
    return 0;
}