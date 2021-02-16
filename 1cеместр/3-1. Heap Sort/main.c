#include <stdlib.h>
#include <stdio.h>

void heapSort(int size, int* mas);//сам алгоритм
void Down(int root, int border, int* mas);//рекурсивный спуск по пирамиде
void Swap(int i, int j, int* mas);//меняет местами значения
void printMas(int size, int* mas);//выводит отсортированный массив

int main(void) {
    int size, curr;
    int check = scanf("%d", &size);
    if (check == 0)
        return 0;
    int* mas = (int*) malloc(size * sizeof(int));
    if (mas == NULL)
        return 0;
    for (int i = 0; i < size; i++) {
        check = scanf("%d", &curr);
        if (check == 0){
            free(mas);
            return 0;
        }
        mas[i] = curr;
    }

    heapSort(size, mas);
    printMas(size, mas);

    free(mas);
    return 1;
}


void heapSort(int size, int* mas) {
    int start = size / 2 - 1;
    for (int i = start; i >= 0; i--) {
        Down(i, size - 1, mas);
    }
    Swap(0, size - 1, mas);
    for (int j = size - 2; j > 0; j--) {
        Down(0, j, mas);
        Swap(0, j, mas);
    }
}

void Swap(int i, int j, int* mas) {
    int tmp = mas[i];
    mas[i] = mas[j];
    mas[j] = tmp;
}

void Down(int root, int border, int* mas) {
    int left = root * 2 + 1, right = root * 2 + 2, x = root;
    if (left <= border && mas[left] > mas[x])
        x = left;
    if (right <= border && mas[right] > mas[x])
        x = right;
    if (x == root)
        return;
    Swap(root, x, mas);
    Down(x, border, mas);
}

void printMas(int size, int* mas) {
    for (int i = 0; i < size; i++) {
        printf("%d ", mas[i]);
    }
}
