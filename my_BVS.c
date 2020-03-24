#include <stdio.h>
#include <stdlib.h>

#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"

#define BLACK 1
#define RED 0

#define COUNT 10 


typedef struct node {
    int val;
    int color;
    struct node *right, *left, *parrent;
} NODE;


void print2DUtil(NODE *head, int space) { 
    // Base case 
    if (head == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(head->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
        
    if(head->color == RED){
        printf("%s%d,%d\n", KRED, head->val, head->color);
    } else {
        printf("%s%d\n", KBLU, head->val);
    }
  
    // Process left child 
    print2DUtil(head->left, space); 
} 


NODE *createNode(int val){
    NODE *node = (NODE *)malloc(sizeof(NODE));

    node->left = node->right = node->parrent = NULL;
    node->val = val;
    node->color = RED;

    return node;
}


NODE *find_parents_sibling(NODE *head, NODE *current){
    NODE *parrent, *parrent_of_parrent;
    parrent = current->parrent;

    parrent_of_parrent = parrent->parrent;

    if(parrent->val > parrent_of_parrent->val){
        if(parrent_of_parrent->left == NULL){
            // printf("now %d %d\n", parrent->parrent->val, parrent_of_parrent->val);
            return NULL;
        }
        return parrent_of_parrent->left;  
    } 

    if(parrent_of_parrent->right == NULL)
        return NULL;
    return parrent_of_parrent->right;  
}


/**
 * There will be rules check of black red alg.
*/
NODE *rules_check(NODE *head, NODE *current){
    NODE *parent_sibling;
    
    /**
     * 3. If parent is black
    */
    if(current->parrent->color == BLACK){
        printf("mam rodica BLACK farby, hodnota rodica: %d, moja hodnota: %d\n", current->parrent->val, current->val);
        return head;
    }

    parent_sibling = find_parents_sibling(head, current);
    if(parent_sibling != NULL && parent_sibling->color == RED){
        printf("mam rodica RED farby, moja hodnota: %d, hodnota rodica: %d, farba suseda rodica BLACK a jeho hodnota %d\n", current->val, current->parrent->val, parent_sibling->val);

        parent_sibling->color = BLACK;
        current->parrent->color = BLACK;

        if(current->parrent->parrent != head)
            current->parrent->parrent->color = RED;
        
        rules_check(head, current->parrent);
    }
    else{
        printf("mam rodica RED farby, moja hodnota: %d, hodnota rodica: %d, hodnota suseda rodica: NULL alebo farba black\n", current->val, current->parrent->val);
    }

    return head;
}


NODE *insert(NODE *head, int new_value){
    NODE *current, *parrent;
    current = head;
    parrent = NULL;

    /**
     * 1. If tree is empty, create new node as root (head) node with black color
    */
    if(head == NULL){
        head = createNode(new_value);
        head->color = BLACK;

        return head;
    }

    /* Find a leaf for new node with value */
    while (current != NULL){
        parrent = current;

        if(current->val < new_value)
            current = current->right;
        else
            current = current->left;       
    }

    /**
     * 2. If tree is not empty, create new node as leaf node with red (default) color
    */
    current = createNode(new_value);

    /* Priradenie dietata pre parenta */
    if(parrent->val > new_value){
        parrent->left = current;
    } else {
        parrent->right = current;
    }

    /* Priradenie rodica pre dieta*/
    current->parrent = parrent;

    /* Kontrola pravidiel cierno cervenho stromu */
    head = rules_check(head, current);

    return head;
}


int main(void) {
    NODE *head;

    head = insert(head, 50);
    head = insert(head, 70);
    head = insert(head, 75);
    head = insert(head, 85);
    head = insert(head, 80);
    head = insert(head, 30);
    head = insert(head, 20);
    head = insert(head, 100);

    print2DUtil(head, 0);
}
