#include <stdlib.h>
#include "treenode.h"

Node* rotateLeft(Node* node){
    Node* p = node->rightSon;
    node->rightSon = p->leftSon;
    p->leftSon = node;
    fixHeight(node);
    fixHeight(p);
    return p;
}

Node* rotateRight(Node* node){
    Node* q = node->leftSon;
    node->leftSon = q->rightSon;
    q->rightSon = node;
    fixHeight(node);
    fixHeight(q);
    return q;
}

int getBF(Node* n){
    return (int) (getHeight(n->rightSon) - getHeight(n->leftSon));
}

unsigned char getHeight(Node* node){
    return node ? node->height : (unsigned char) 0;
}

void fixHeight(Node* node){
    unsigned char nl = getHeight(node->leftSon);
    unsigned char nr = getHeight(node->rightSon);
    node->height = (nl > nr ? nl : nr) + (unsigned char) 1;
}

void destroy(Node* node){
    if (node == NULL)
        return;
    destroy(node->leftSon);
    destroy(node->rightSon);
    free(node);
}

Node* construct(int val, Node* free){
    Node* node = free;
    node->val = val;
    node->height = (unsigned char) 1;
    node->rightSon = node->leftSon = 0;

    return node;
}
