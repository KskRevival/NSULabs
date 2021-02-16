#include <stdio.h>
#include <stdlib.h>

void swap(char* a, char* b);//меняет значения 2ух элементов
int checkNum(char* num);//проверяет ввод
int findBS(int pos, char* num);//находит самое большое число справа, которое меньше рассматриваемого
void sort(int pos, int len, char* num);//сортирует часть числа справа от сортируемого по неубыванию
void printNums(int n, int len, char* num);//сам алгоритм

int main(){
    char* num = calloc(11, sizeof(char));
    int checker = scanf("%10s", num);
    if (checker == 0){
        free(num);
        return 1;
    }
    int n, len = 0;
    checker = scanf("%d", &n);
    if (checker == 0){
        free(num);
        return 1;
    }
    if (checkNum(num)){
        free(num);
        printf("bad input");
        return 1;
    }
    for(len = 0;len < 10; len++){
        if (num[len] == 0)
            break;
    }
    printNums(n, len, num);
    free(num);
    return 0;
}
void printNums(int n, int len, char* num){
    int curr = 0;
    while(curr != -1 && n > 0){
        curr = -1;
        for(int j = len - 2; j >= 0; j--){
            if (num[j] < num[j+1]){
                curr = j;
                swap(&num[curr], &num[findBS(curr, num)]);
                break;
            }
        }
        if (curr == -1)
            break;
        sort(curr, len, num);
        for (int i = 0; i < len; ++i) {
            printf("%c", num[i]);
        }
        printf("\n");
        n -= 1;
    }
}

void sort(int curr, int len, char* num){
    char* numCpy = calloc(11, sizeof(char));
    int j;
    for (j = curr + 1; j < len; j++) {
        numCpy[j] = num[j];
    }
    j = curr + 1;
    for (int k = len-1; k >= curr + 1; k--) {
        num[j] = numCpy[k];
        j++;
    }
    free(numCpy);
}


int findBS(int pos, char* num){
    char minimax = num[pos+1];
    int fpos = pos + 1, currpos = pos+1;
    while(num[currpos] != 0){
        if (num[pos] < num[currpos] && num[currpos] < minimax){
            minimax = num[currpos];
            fpos = currpos;
        }
        currpos++;
    }
    return fpos;
}

int checkNum(char* num){
    int* mas = calloc(10, sizeof(int));
    int i = 0;
    while (num[i] != 0){
        if (num[i] - '0' < 0 || num[i] - '0' > 9){
            free(mas);
            return 1;
        }
        if (mas[num[i] - '0']){
            free(mas);
            return 1;
        } else
            mas[num[i] - '0']++;
        i++;
    }
    free(mas);
    return 0;
}

void swap(char* a, char* b){
    char tmp = *a;
    *a = *b;
    *b = tmp;
}
