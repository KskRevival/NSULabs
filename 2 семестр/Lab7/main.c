#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    short val;
} node;

void freeGraph(node** graph, short n);
void addNode(node** head, short x);
void dfs(node** graph, short v, short* output, short* pos, char* color, short n);
int getVal(short floor, int ceil, const char* err);
node** readAll(short* n, int* m);

int main(void) {
    short n;
    int m;
    node** graph = readAll(&n, &m);
    char* color = calloc(n, sizeof(char));
    short* output = malloc(sizeof(short) * n);
    short pos = 0;

    for (int i = 0; i < n; i++)
        if (graph[i])
            dfs(graph, i, output, &pos, color, n);

    for (int i = pos - 1; i >= 0; i--)
        printf("%d ", output[i] + 1);

    for (int i = 0; i < n; i++) {
        if (color[i] == 0)
            printf("%d ", i + 1);
    }

    freeGraph(graph, n);
    free(output);
    free(color);
    return 0;
}

void addNode(node** head, short x) {
    node* tmp = malloc(sizeof(node));
    if (tmp == NULL) {
        printf("memory");
        exit(1);
    }
    tmp->val = x;
    tmp->next = *head;
    *head = tmp;
}

void dfs(node** graph, short v, short* output, short* pos, char* color, short n) {
    if (color[v] == 1) {
        printf("impossible to sort");
        exit(7);
    } else if (color[v] == 2) {
        return;
    }

    color[v] = 1;
    node* tmp = graph[v];

    while (tmp) {
        if (tmp->val < n && graph[tmp->val])
            dfs(graph, tmp->val, output, pos, color, n);
        tmp = tmp->next;
    }
    color[v] = 2;
    output[*pos] = v;
    (*pos)++;
}

int getVal(short floor, int ceil, const char* err) {
    int n;
    if (scanf("%d", &n) == EOF) {
        printf("%s", "bad number of lines");
        exit(1);
    }
    if (n < floor || n > ceil) {
        printf("%s", err);
        exit(2);
    }
    return n;
}

node** readAll(short* n, int* m) {
    *n = getVal(0, 1000, "bad number of vertices");
    *m = getVal(0, *n * (*n - 1) / 2, "bad number of edges");
    node** graph = malloc(sizeof (node*) * *n);
    for (int i = 0; i < *n; i++) { graph[i] = NULL; }

    for (int i = 0; i < *m; i++) {
        short u = (short) (getVal(1, *n, "bad vertex") - 1);
        short v = (short) (getVal(1, *n, "bad vertex") - 1);
        addNode(graph + u, v);
    }
    return graph;
}

void freeGraph(node** graph, short n) {
    for (int i = 0; i < n; i++) {
        while (graph[i]) {
            node* tmp = graph[i];
            graph[i] = graph[i]->next;
            free(tmp);
        }
    }
    free(graph);
}
