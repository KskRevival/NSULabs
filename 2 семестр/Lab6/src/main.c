#include <stdio.h>
#include <stdlib.h>
#include "treenode.h"

Node* AVL(int n,  Node* nodes);
Node* addNode(Node* node, int val, Node* free);
Node* toAVL(Node* node);

int main(){
    int n;
    if (!scanf("%d", &n))
        return 1;
    if (n < 1){
        printf("%d", 0);
        return 0;
    }

    Node* nodes = (Node*) malloc (n * sizeof(Node));
    Node* head = AVL(n, nodes);
    printf("%d", getHeight(head));

    free(nodes);
    return 0;
}

Node* AVL(int n, Node* nodes){
    int currNum;
    Node* node = NULL;

    for (int i = 0; i < n; i++) {
        if(!scanf("%d", &currNum))
            exit(2);
        node = addNode(node, currNum, &nodes[i]);
    }

    return node;
}

Node* addNode(Node* node, int val, Node* free){
    if (!node)
        return construct(val, free);
    if (val < node->val)
        node->leftSon = addNode(node->leftSon, val, free);
    else
        node->rightSon = addNode(node->rightSon, val, free);
    return toAVL(node);
}

Node* toAVL(Node* node){
    fixHeight(node);
    if (getBF(node) == 2){
        if ( getBF(node->rightSon) < 0)
            node->rightSon = rotateRight(node->rightSon);

        return rotateLeft(node);
    }
    if (getBF(node) == -2){
        if (getBF(node->leftSon) > 0)
            node->leftSon = rotateLeft(node->leftSon);

        return rotateRight(node);
    }

    return node;
}
