#define _CRT_SECURE_NO_WARNINGS
#define BUFF_SIZE 1000000
#define TEMPLATE_SIZE 18
#define ASCII_SIZE 256

#include <stdlib.h>
#include <stdio.h>

int updateBuffer(FILE* file, unsigned char* buffer);//перезаписывает буффер
void getTemplateHash(unsigned char* buffer, unsigned char* template, int templateLength, int* threeMax, int* templateHash, int* currHash);//Считает Хэш шаблона и первых
//templateLength элементов буффера
void compare(unsigned char* buffer, unsigned char* template, int templateLength, int ptr, int shift);//сравнивает шаблон с частью строки, если совпали хэши

int main(){
    unsigned char* template = calloc((TEMPLATE_SIZE + 1), sizeof(char));
    unsigned char* buffer = malloc(BUFF_SIZE * sizeof(char));
    FILE* file = fopen("in.txt", "r");
    int templateLength = 0, threeMax = 1, currHash = 0, templateHash = 0, ptr = 0, shift = 0;
    char* checker;
    checker = fgets((char*)template, TEMPLATE_SIZE, file);
    if (!checker){
        fclose(file);
        free(template); free(buffer);
        return 1;
    }
    while(template[templateLength])
        templateLength++;
    template[--templateLength] = '\0';
    int bufLen = updateBuffer(file, buffer);
    getTemplateHash(buffer, template, templateLength, &threeMax, &templateHash, &currHash);
    threeMax /= 3;
    printf("%d ", templateHash);
    ptr = templateLength;

    while(bufLen == BUFF_SIZE || ptr <= bufLen){
        if (currHash == templateHash){
            compare(buffer, template, templateLength, ptr, shift);
        }
        currHash = (currHash / 3) + threeMax*(buffer[ptr] % 3);
        if(ptr + 1 == BUFF_SIZE){
            bufLen = updateBuffer(file, buffer);
            ptr = 0;
            shift += BUFF_SIZE;
            continue;
        }
        ptr++;
    }

    fclose(file); free(template); free(buffer);
    return 0;
}

void compare(unsigned char* buffer, unsigned char* template, int templateLength, int ptr, int shift){
     int i = templateLength;
     while (i > 0){
         i--;
         printf("%d ", ptr + shift - i);
         if (template[templateLength - i - 1] != buffer[ptr - i - 1]){
             break;
         }
     }
}

void getTemplateHash(unsigned char* buffer, unsigned char* template, int templateLength, int* threeMax, int* templateHash, int* currHash){
    for (int i = 0; i < templateLength; ++i) {
        *templateHash += (*threeMax) * (template[i] % 3);
        *currHash += (*threeMax) * (buffer[i] % 3);
        *threeMax *= 3;
    }
}

int updateBuffer(FILE* file, unsigned char* buffer){
    return (int)fread(buffer, sizeof(char), BUFF_SIZE, file);
}
