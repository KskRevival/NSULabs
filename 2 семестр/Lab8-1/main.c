#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "qsort.h"

#define MAX_VERT 5000

const char *ERRORS[] = {
        "bad number of vertices",
        "bad vertex",
        "bad number of edges",
        "bad length",
        "bad number of lines"
};

void makeSet(int v, int* parent, int* rank);
int findSet(int v, int* parent);
void unionSets(int a, int b, int* parent, int* rank);
int getValue(int low, int high, const char* err, FILE* file);
void kruskal(int N, int M, int* u, int* v, int* len, FILE* file);

int main() {
    int N, M;
    FILE* file = fopen("out.txt", "w");

    N = (int) getValue(0, MAX_VERT, ERRORS[0], file);
    M = (int) getValue(0, N * (N + 1) / 2, ERRORS[2], file);

    int* u = (int*) malloc(M * sizeof(int));
    int* v = (int*) malloc(M * sizeof(int));
    int* len = (int*) malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        u[i] = getValue(1, N, ERRORS[1], file) - 1;
        v[i] = getValue(1, N, ERRORS[1], file) - 1;
        len[i] = getValue(0, INT_MAX, ERRORS[3], file);
    }

    kruskal(N, M, u, v, len, file);

    fclose(file);
    free(u); free(v); free(len);
    return 0;
}

void kruskal(int N, int M, int* u, int* v, int* len, FILE* file){
    int parent[MAX_VERT];
    int rank[MAX_VERT];

    quickSort(u, v, len, 0, M - 1);
    for (int i = 0; i < N; i++)
        makeSet(i, parent, rank);

    int edgeCount = 0;
    for (int i = 0; i < M; i++){
        if (findSet(u[i], parent) != findSet(v[i], parent)) {
            edgeCount++;
            fprintf(file, "%d %d\n", u[i] + 1, v[i] + 1);
            unionSets(u[i], v[i], parent, rank);
        }
        if (edgeCount == N - 1) break;
    }
    if (edgeCount != N - 1) {
        rewind(file);
        fprintf(file, "%s", "no spanning tree");
    }

}

void makeSet(int v, int* parent, int* rank) {
    parent[v] = v;
    rank[v] = 0;
}

int findSet(int v, int* parent) {
    int root = v;
    while (parent[root] != root)
        root = parent[root];
    int i = v;
    while (parent[i] != i) {
        int j = parent[i];
        parent[i] = root;
        i = j;
    }
    return root;
}

void unionSets(int a, int b, int* parent, int* rank) {
    a = findSet(a, parent);
    b = findSet(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            swap (&a, &b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

int getValue(int low, int high, const char* err, FILE* file) {
    int n;
    if (scanf("%d", &n) == EOF) {
        fprintf(file, "%s", ERRORS[4]);
        exit(0);
    }
    if (n < low || n > high) {
        fprintf(file, "%s", err);
        exit(0);
    }
    return n;
}
