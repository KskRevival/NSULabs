#define BUFF_SIZE 1000000
#define TEMPLATE_SIZE 18
#define ASCII_SIZE 256

#include <stdlib.h>
#include <stdio.h>

int updateBuffer(FILE* file, unsigned char* buffer, int addition); //обновление буффера
int* createTable(unsigned char* template, int templateLength); // создание таблицы сдвигов
void check(unsigned char* buffer, unsigned char* template, int ptr, int templateLength, int shift); // сама проверка при совпадении символа

int main(){
    unsigned char* template = calloc(TEMPLATE_SIZE + 1, sizeof(char));
    unsigned char* buffer = calloc(BUFF_SIZE, sizeof(char));
    FILE* file = fopen("in.txt", "r");
    int templateLength = 0, ptr = 0, shift = 0;
    char* checker;
    checker = fgets((char*) template, TEMPLATE_SIZE, file);
    if (!checker){
        fclose(file); free(buffer); free(template);
        return 2;
    }
    while(template[templateLength] != 0)
        templateLength++;
    templateLength -= 1;
    int* table = createTable(template, templateLength);
    int bufLen = (int) updateBuffer(file, buffer, 0);

    while (bufLen == BUFF_SIZE || ptr + templateLength <= bufLen){
        if(ptr + templateLength > bufLen){
            int addition = BUFF_SIZE - ptr;
            for (int i = 0; i < addition; ++i) {
                buffer[i] = buffer[i + addition];
            }
            bufLen = updateBuffer(file, buffer, addition) + addition;
            ptr = 0;
            shift += BUFF_SIZE - addition;
        }

        printf("%d ", ptr + shift + templateLength );
        if(template[templateLength - 1] == buffer[ptr + templateLength - 1])
            check(buffer, template, ptr, templateLength, shift);
        ptr += templateLength - 1 - table[(int) buffer[ptr + templateLength - 1]];
    }

    fclose(file); free(table); free(template); free(buffer);
    return 0;
}

int *createTable(unsigned char *template, int templateLength) {
    int *table = (int*) malloc(sizeof(int) * ASCII_SIZE);

    for (int i = 0; i < ASCII_SIZE; i++)
        table[i] = - 1;
    for (int i = 0; i < templateLength - 1; i++)
        table[(int)template[i]] = i;

    return table;
}

void check(unsigned char* buffer, unsigned char* template, int ptr, int templateLength, int shift){
    int i = templateLength - 1;

    while(i > 0 && template[i] == buffer[ptr+i]){
        i--;
        printf("%d ", ptr + shift + i + 1);
    }
}

int updateBuffer(FILE* file, unsigned char* buffer, int addition){
    return (int)fread(buffer + addition, sizeof(char), BUFF_SIZE - addition, file);
}
