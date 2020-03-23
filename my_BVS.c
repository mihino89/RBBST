#include <stdio.h>
#include <stdlib.h>

#define BLACK 1
#define RED 0

typedef struct node {
    int val;
    int color = RED;
    struct node *right, *left, *parent;
} NODE;

NODE *createNode(int val){
    NODE *node = (NODE *)malloc(sizeof(NODE));

    node->left = node->right = node->parent = NULL;
    node->val = val;

    return node;
}

NODE *insert(NODE *node, int key){
    if(node == NULL){
        createNode(key);
    }

    if(key > node->val){
        insert(node->right, key);
    } else {
        insert(node->left, key);
    }

    return node;
}

int main(void) {

}
