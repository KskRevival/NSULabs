#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "qsort.h"

void swap(int *a, int *b){
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

int partition (int* u, int* v, int* len, int l, int r) {
    int x = (l + r)/2;
    int i = l;
    int j = r;
    while (i <= j) {
        while (len[i] < len[x]) {
            i++;
        }
        while (len[j] > len[x]) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(&len[i], &len[j]);
        swap(&u[i], &u[j]);
        swap(&v[i], &v[j]);
        i++;
        j--;
    }
    return j;
}

void quickSort (int* u, int* v, int* len, int l, int r) {
    if (l < r) {
        int q = partition(&u[0], &v[0], &len[0], l, r);
        quickSort(u, v, len, l, q);
        quickSort(u, v, len, q + 1, r);
    }
}
