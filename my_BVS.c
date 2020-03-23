#include <stdio.h>
#include <stdlib.h>

#define BLACK 1
#define RED 0


typedef struct node {
    int val;
    int color;
    struct node *right, *left, *parent;
} NODE;


NODE *createNode(int val){
    NODE *node = (NODE *)malloc(sizeof(NODE));

    node->left = node->right = node->parent = NULL;
    node->val = val;
    node->color = RED;

    return node;
}


void rules_check(){
    /**
     * There will be rules check of black red alg.
    */
}


void insert(NODE *head, int new_value){
    NODE *current, *parrent;
    current = head;
    parrent = NULL;

    if(head == NULL){
        head = createNode(new_value);
        head->color = BLACK;
    }

    while (current != NULL){
        parrent = current;

        if(current->val < new_value){
            current = current->right;
        }
        else
            current = current->left;       
    }

    current = createNode(new_value);

    if(parrent->val > new_value){
        parrent->left = current;
    } else {
        parrent->right = current;
    }

    current->parent = parrent;

    if(parrent->color == BLACK){
        printf("mam rodica BLACK farby %d\n", parrent->val);

    }
    else if(parrent->color == RED){
        printf("mam rodica RED farby\n");
    }

    // rules_check
}


int main(void) {
    NODE *head = createNode(50);
    head->color = BLACK;

    insert(head, 70);
    insert(head, 80);
}
