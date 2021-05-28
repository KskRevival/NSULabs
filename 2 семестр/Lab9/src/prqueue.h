#ifndef LAB9_PRQUEUE_H
#define LAB9_PRQUEUE_H

typedef struct heapItem{
    short vertex;
    long long priority;
}HeapItem;

typedef struct heap{
    short size;
    HeapItem* items;
}Heap;

Heap* createHeap(short n);
void freeHeap(Heap* h);
void heapSwap(HeapItem* a, HeapItem* b);
void insert(Heap* h);
short extractMin(Heap* h);
void decreaseKey(Heap* h, int vertex, int np);

#endif
