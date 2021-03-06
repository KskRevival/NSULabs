#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define eps 0.00000000001
#define difference 32

int checkInput(int b1, int b2, char* floatNum);//чтобы система система счисления была 2-16
char getCharNum(int num);//    
int getNum(char charNum);//    
void transferBefore(long long int num, int b2);//перевод части числа до точки    
int getNumLength(long long int num, int b2);//получение длины числа в системе счисления b2
void transferAfter(long long int num, int b1, int b2, int length); //перевод части числа после точки     
char toLower(char charNum);

int main(void) {
    int b1 = 0, b2 = 0, isAfter = 0, i = 0, afterDotNums = 0;
    long long int beforeDot = 0, afterDot = 0;
    char floatNum[14] = { 0 };
    int check = scanf("%d %d", &b1, &b2);
    check += scanf("%13s", floatNum);
    if (check != 3) {
        printf("bad input");
        return 1;
    }

    if (checkInput(b1, b2, floatNum)) {
        printf("bad input");
        return 1;
    }
    //перевод в 10ую систему счисления из b1      
    while (floatNum[i] != 0) {
        if (floatNum[i] == '.') {
            isAfter = i + 1;
            i++;
        }
        if (floatNum[i] != 0) {
            int currNum = getNum(floatNum[i]);
            if (isAfter) {
                afterDot += currNum;
                afterDot *= b1;
            }
            else {
                beforeDot += currNum;
                beforeDot *= b1;
            }

            i++;

        }
    }
    beforeDot /= b1;
    afterDot /= b1;
    afterDotNums = i - isAfter;

    if (!beforeDot)
        printf("0");
    else
        transferBefore(beforeDot, b2);
    if (afterDot > 0) {
        printf(".");
        transferAfter(afterDot, b1, b2, afterDotNums);
    }

    return 1;
}

int checkInput(int b1, int b2, char* floatNum) {
    if (b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16) {
        return 1;
    }
    int dotCount = 0, i = 0;

    if (floatNum[i] == '.')
        return 1;

    while (floatNum[i] != 0) {
        int nextInt = 0;
        if (!dotCount && floatNum[i] == '.') {
            dotCount = 1;
            i += 1;
        }
        nextInt = getNum(floatNum[i]);
        if (nextInt == -1 || nextInt >= b1)
            return 1;
        i++;
    }

    return 0;

}

char getCharNum(int num) {
    char charNum = '0';
    if (num < 10)
        charNum += num;
    else {
        charNum = 'a';
        charNum = charNum - 10 + num;
    }

    return charNum;
}

int getNum(char charNum) {
    charNum = toLower(charNum);
    int num = 0;
    if (charNum >= '0' && charNum <= '9') {
        num += charNum - '0';
    }
    else if (charNum >= 'a' && charNum <= 'f') {
        num += charNum - 'a' + 10;
    }
    else
        num = -1;
    return num;

}

void transferBefore(long long int num, int b2) {
    int length = getNumLength(num, b2);
    char* transferedNum = calloc(length, sizeof(char));
    int i = 1;
    if (num < b2) {
        transferedNum[0] = getCharNum(num);
    }
    long long int div = 0;
    while (num >= b2) {
        long long int mod = 0;
        mod = num % b2;
        div = num / b2;
        num = num / b2;
        transferedNum[length - i] = getCharNum(mod);
        i++;
    }
    if (div)
        transferedNum[0] = getCharNum(div);
    for (int it = 0; it < length; it++)
    {
        printf("%c", transferedNum[it]);
    }
    free(transferedNum);
}

int getNumLength(long long int num, int b2) {
    int length = 0;
    while (num > 0) {
        num /= b2;
        length++;
    }

    return length;
}

void transferAfter(long long int num, int b1, int b2, int length) {
    long long int bigB1 = 1;
    for (int pp = 0; pp < length; pp++) {
        bigB1 *= b1;
    }
    long double number = (long double)num / bigB1;
    int j = 1;

    while (number > eps && j <= 12) {
        number *= b2;
        int counter = 0;
        while (number >= 1) {
            number -= 1;
            counter++;
        }
        printf("%c", getCharNum(counter));
        j++;
    }
}

char toLower(char charNum) {
    if (charNum >= 'A' && charNum <= 'F')
        charNum += difference;

    return charNum;
}
