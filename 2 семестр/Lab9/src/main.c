#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "prqueue.h"

#define MAX_VERT 5000
#define INF UINT_MAX

const char *ERRORS[] = {
        "bad number of vertices",
        "bad number of edges",
        "bad vertex",
        "bad length",
        "bad number of lines"
};

int getValue(int low, int high, const char* err);
unsigned** readAndFillMatrix(short* N, short* S, short* F, int *M);
void dijkstra(short n, short s, short f, unsigned** matrix, Heap* heap);
void printWays(unsigned* d, short* p, short n);
int findWay(unsigned* d, short* p, short s, short f, short of);
short overflow(short n, short f, unsigned len, unsigned* d, unsigned** matrix);

int main() {
    short N, S, F;
    int M;
    unsigned** matrix = readAndFillMatrix(&N, &S, &F, &M);

    Heap* heap = createHeap(N);

    dijkstra(N, S, F, matrix, heap);

    freeHeap(heap);
    return 0;
}

void dijkstra(short n, short s, short f, unsigned** matrix, Heap* heap){
    short visited[n+1];
    unsigned d[n+1];
    short p[n+1];
    for (short i = 1; i < n+1; ++i) {
        d[i] = INF; p[i] = i; visited[i] = 0;
    }
    d[s] = 0;
    decreaseKey(heap, s, 0);

    short v = extractMin(heap), of = 0;
    while (heap->size){
        for (int i = 1; i < n+1; ++i) {
            if (!visited[i] && matrix[v][i] <= INT_MAX
                            && d[v] <= INT_MAX && d[i] >= d[v] + matrix[v][i]){
                d[i] = matrix[v][i] + d[v];
                p[i] = v;
                decreaseKey(heap, i, (int)matrix[v][i]);
            }
        }
        visited[v]++;
        v = extractMin(heap);
    }

    of = overflow(n, f, d[f], d, matrix);

    printWays(d, p, n);
    findWay(d, p, s, f, of);

    for (int j = 1; j < n+1; ++j) {
        free(matrix[j]);
    }
    free(matrix);
}

short overflow(short n, short f, unsigned len, unsigned* d, unsigned** matrix){
    if (len > INT_MAX){
        short count = 0;
        for (int i = 1; i < n+1; ++i) {
            if (matrix[f][i] != INF && d[i] + matrix[f][i] > INT_MAX){count++;}
            if (count > 1) break;
        }
        if (count > 1){return 1;}
    }
    return 0;
}

int findWay(unsigned* d, short* p, short s, short f, short of){
    if (d[f] == UINT_MAX && p[f] == f){
        printf("no path");
        return 1;
    }
    if (of && d[f] > INT_MAX){
        printf("overflow");
        return 2;
    }
    while(p[f] != f){
        printf("%d ", f);
        f = p[f];
    }
    printf("%d", s);
    return 3;
}

void printWays(unsigned* d, short* p, short n){
    for (int j = 1; j < n+1; ++j) {
        if (d[j] > INT_MAX){
            if (p[j] == j && d[j] == UINT_MAX)
                printf("oo ");
            else
                printf("INT_MAX+ ");
        } else
            printf("%u ", d[j]);
    }
    printf("\n");
}

int getValue(int low, int high, const char* err) {
    long n;
    if (scanf("%ld", &n) == EOF) {
        printf("%s", ERRORS[4]);
        exit(0);
    }
    if (n < low || n > high) {
        printf("%s", err);
        exit(66);
    }
    return (int)n;
}

unsigned** readAndFillMatrix(short* N, short* S, short* F, int *M){
    *N = (short) getValue(0, MAX_VERT, ERRORS[0]);
    *S = (short) getValue(1, *N, ERRORS[2]);
    *F = (short) getValue(1, *N, ERRORS[2]);
    *M = (int) getValue(0, *N * (*N + 1) / 2, ERRORS[1]);

    unsigned** m = malloc((*N+1) * sizeof(int*));
    for (int i = 1; i < *N+1; ++i) {
        m[i] = malloc((*N+1) * sizeof(int));
        for (int j = 1; j < (*N+1); ++j) {
            m[i][j] = INF;
        }
    }

    for (int k = 0; k < *M; ++k) {
        short a = (short) getValue(1, *N, ERRORS[2]);
        short b = (short) getValue(1, *N, ERRORS[2]);
        int length = getValue(0, INT_MAX, ERRORS[3]);
        m[a][b] = length;
        m[b][a] = length;
    }

    return m;
}
