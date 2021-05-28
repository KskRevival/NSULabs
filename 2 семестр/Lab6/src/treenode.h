#ifndef LAB6_TREENODE_H
#define LAB6_TREENODE_H

typedef struct TreeNode{
    int val;
    unsigned char height;

    struct TreeNode* leftSon;
    struct TreeNode* rightSon;
}Node;

Node* rotateLeft(Node* node);
Node* rotateRight(Node* node);
void destroy(Node* node);
unsigned char getHeight(Node* node);
int getBF(Node* n);
Node* construct(int val, Node* free);
void fixHeight(Node* node);

#endif //LAB6_TREENODE_H
