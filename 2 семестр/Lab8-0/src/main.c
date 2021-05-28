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
unsigned** readAndFillMatrix(short* N, int *M);
short prim(short n, Heap* h, unsigned** matrix);

int main() {
    short N;
    int M;
    unsigned **matrix = readAndFillMatrix(&N, &M);
    Heap *heap = createHeap(N);

    prim(N, heap, matrix);

    for (int i = 1; i < N+1; ++i){
        free(matrix[i]);
    }
    freeHeap(heap); free(matrix);
}

short prim(short n, Heap* h, unsigned** matrix){
    short position = 0, exist = 1;
    short p[n+1];
    unsigned d[n+1];
    short* visited = malloc((n+1) * sizeof(short));
    short* output = calloc((n) * 2, sizeof(short));
    for (int i = 1; i < n+1; ++i) {
        p[i] = 0;
        visited[i] = 0;
        d[i] = UINT_MAX;
    }
    decreaseKey(h, 1, 0); d[1] = 0;
    short v = extractMin(h);
    while(h->size){
        /*while(adj[v]->size){
            short u = adj[v]->v->num;
            if (!visited[u] && matrix[v][u] < d[u]){
                d[u] = matrix[v][u];
                p[u] = v;
                decreaseKey(h, u, (int)d[u]);
            }
            adj[v]->size--;
            ListItem* tmp = adj[v]->v;
            if (adj[v]->size)
                adj[v]->v = adj[v]->v->prev;
            free(tmp);

        }*/
        for (int i = 1; i < n+1; ++i) {
            if(!visited[i] && matrix[v][i] != INF && matrix[v][i] < d[i]){
                d[i] = matrix[v][i];
                p[i] = v;
                decreaseKey(h, i, (int)d[i]);
            }
        }
        visited[v]++;
        v = extractMin(h);

        output[position++] = v;
        output[position++] = p[v];
        if (!p[v]){
            exist--;
            break;
        }
    }

    if (exist){
        for (int i = 0; i < position; i+=2) {
            printf("%d %d\n", output[i], output[i+1]);
        }
    } else{
        printf("no spanning tree");
    }

    free(visited);free(output);

    return exist;
}

int getValue(int low, int high, const char* err) {
    int n;
    if (scanf("%d", &n) == EOF && n != INT_MAX) {
        printf("%s", ERRORS[4]);
        exit(999);
    }

    if (n < low || n > high) {
        printf("%s", err);
        exit(1);
    }
    return n;
}

unsigned** readAndFillMatrix(short* N, int *M){
    *N = (short) getValue(0, MAX_VERT, ERRORS[0]);
    if (*N == 0){
        printf("no spanning tree");
        exit(123);
    }
    *M = getValue(0, *N * (*N + 1) / 2, ERRORS[1]);

    unsigned** m = malloc((*N+1) * sizeof(int*));
    if (m == NULL){
        printf("matrix doesn't exist");
        exit(200);
    }
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
