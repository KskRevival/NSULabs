#include <stdlib.h>
#include <stdio.h>

void printMas(int size, int* mas);//вывод отсортированного массива
void quickSort(int left, int right, int* mas);//сам алгоритм (рекурсивный)
int separator(int left, int right, int* mas);//делит на подмассивы
void swap(int* a, int* b);//меняет местами значения

int main(void) {
    int size, curr;
    int check = scanf("%d", &size);
    if (!check)
        return 1;
    int* mas = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        check = scanf("%d", &curr);
        if (!check) {
            free(mas);
            return 1;
        }
        mas[i] = curr;
    }

    quickSort(0, size - 1, mas);
    printMas(size, mas);

    free(mas);
    return 0;
}

int separator(int left, int right, int* mas) {
    int point = mas[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (mas[i] < point)
            i++;
        while (mas[j] > point)
            j--;
        if (i >= j)
            break;
        swap(&mas[i++], &mas[j--]);
    }
    return j;
}

void quickSort(int left, int right, int* mas) {
    if (left < right) {
        int mid = separator(left, right, mas);
        quickSort(left, mid, mas);
        quickSort(mid + 1, right, mas);
    }
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void printMas(int size, int* mas) {
    for (int i = 0; i < size; i++) {
        printf("%d ", mas[i]);
    }
}
