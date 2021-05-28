#include "prqueue.h"
#include <stdlib.h>
#include <limits.h>

#define MAX_VERT 5000

Heap* createHeap(short n){
    Heap* h = malloc(sizeof(Heap));
    h->size = 0;
    h->items = malloc(sizeof(HeapItem) * (n + 1));
    for (int i = 0; i < n; ++i) {
        insert(h);
    }
    return h;
}

void freeHeap(Heap* h){
    free(h->items);
    free(h);
}

void heapSwap(HeapItem* a, HeapItem* b){
    HeapItem tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert(Heap* h){
    h->size++;
    h->items[h->size].priority = LLONG_MAX;
    h->items[h->size].vertex = h->size;
}

short extractMin(Heap* h){
    heapSwap(&h->items[1], &h->items[h->size]);
    int son, n = h->size-1;
    for (int i = 1; i*2 <= n; i = son) {
        son = 2*i;
        if (son < n && h->items[son].priority > h->items[son+1].priority)
            son++;
        if (h->items[i].priority <= h->items[son].priority)
            break;
        heapSwap(&h->items[i], &h->items[son]);
    }
    return h->items[h->size--].vertex;
}

void decreaseKey(Heap* h, int vertex, int np){
    for (int i = 1; i < MAX_VERT + 1; ++i) {
        if (h->items[i].vertex == vertex) {
            if (np < h->items[i].priority) {
                h->items[i].priority = np;
                for (int j = i; j > 1 && h->items[j].priority < h->items[j / 2].priority; j /= 2) {
                    heapSwap(&h->items[j], &h->items[j / 2]);
                }
            }
            break;
        }
    }
}
