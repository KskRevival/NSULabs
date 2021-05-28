#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SYNTAX_ERR do { printf("syntax error"); exit(0); } while(0);
#define ZERO_DIV do { printf("division by zero"); exit(0); } while(0);


int expr(int *token, int *token_value, int *bracket_count);

int next(int *token, int *token_value) {
    for (;;) {
        int c = getchar();
        if (c == EOF || strchr("+-*/()\n", c) != NULL) return *token = c;
        if (isdigit(c)) {
            ungetc(c, stdin);
            if (!scanf("%d", token_value)) SYNTAX_ERR
            return *token = 'n';
        }
        SYNTAX_ERR
    }
}

void skip(int t, int *token, int *token_value) {
    if (t != *token) SYNTAX_ERR
    next(token, token_value);
}

int brackets(int *token, int *token_value, int *bracket_count) {
    if (*token == 'n') {
        int x = *token_value;
        skip('n', token, token_value);
        return x;
    }
    skip('(', token, token_value);
    (*bracket_count)++;
    int x = expr(token, token_value, bracket_count);
    skip(')', token, token_value);
    (*bracket_count)--;
    return x;
}

int term(int *token, int *token_value, int *bracket_count) {
    int x = brackets(token, token_value, bracket_count);
    for (;;) {
        if (*token == '*') {
            skip('*', token, token_value);
            x *= brackets(token, token_value, bracket_count);
        }
        else if (*token == '/') {
            skip('/', token, token_value);
            int y = brackets(token, token_value, bracket_count);
            if (!y) ZERO_DIV
            x /= y;
        }
        else return x;
    }
}

int expr(int *token, int *token_value, int *bracket_count) {
    int x = term(token, token_value, bracket_count);
    for (;;) {
        if (*token == '+') {
            skip('+', token, token_value);
            x += term(token, token_value, bracket_count);
        }
        else if (*token == '-') {
            skip('-', token, token_value);
            x -= term(token, token_value, bracket_count);
        }
        else if (*token == '(') SYNTAX_ERR
        else if (*token == ')' && !(*bracket_count)) SYNTAX_ERR
        else return x;
    }
}

int main(void) {
    int token, token_value, bracket = 0;
    next(&token, &token_value);
    printf("%d\n", expr(&token, &token_value, &bracket));
    return 0;
}
