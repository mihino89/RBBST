#include <stdio.h>
#include <stdlib.h>

#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"

#define BLACK 1
#define RED 0

#define COUNT 10 

#define LEFTLEFT 0
#define RIGHTRIGHT 1
#define LEFTRIGHT 2
#define RIGHTLEFT 3

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
        printf("%s%d\n", KRED, head->val);
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


NODE *find_parent_sibling(NODE *head, NODE *current){
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


int check_which_rotation(NODE *head, NODE *current){
    
    if(current->val < current->parrent->val && current->parrent->val < current->parrent->parrent->val)
        return LEFTLEFT;

    if(current->val > current->parrent->val && current->parrent->val > current->parrent->parrent->val)
        return RIGHTRIGHT;
    
    if(current->val > current->parrent->val && current->parrent->val < current->parrent->parrent->val)
        return LEFTRIGHT;
    
    if(current->val < current->parrent->val && current->parrent->val > current->parrent->parrent->val)
        return RIGHTLEFT;
        
    return -1;
}


NODE *left_rotations(NODE *head, NODE *current){

    if(current == NULL || current->parrent == NULL){
        printf("PROBLEM!\n");
        return head;
    }

    NODE *current_parrent = current->parrent;

    current_parrent->right = current->left;

    if(current->left != NULL)
        current_parrent->right->parrent = current_parrent;
    

    if(current_parrent->parrent == NULL){
        head = current;
    }
    else {
        current->parrent = current_parrent->parrent;

        if(current_parrent->val > current_parrent->parrent->val)
            current->parrent->right = current;

        else if(current_parrent->val < current_parrent->parrent->val)
            current->parrent->left = current;
    }

    current->left = current_parrent;
    current_parrent->parrent = current;
    // printf("current: %d, current parrent: %d, current left: %d\n", current->val, current->parrent->val, current->left->val);

    return head;
}


// need refactor
NODE *right_rotations(NODE *head, NODE *current){
    NODE *pom = head;
    // printf("pom: %d\n", pom->val);
    
    if(current == NULL || current->parrent == NULL){
        return head;
    }

    NODE *current_parrent = current->parrent;
    // printf("current: %d, head: %d, current parrent: %d\n", current->val, current->parrent->val, current_parrent->val);


    if(current_parrent->val > current->val){
        current_parrent->left = current->right;
        current->right = current_parrent;
    }
    else{
        current_parrent->right = current->left;
        current_parrent->right->parrent = current_parrent;
        current->left = current_parrent;
        // printf("?current: %d, head: %d, current left: %d, current_parrent right: %d\n", current->val, head->val, current->left->val, current_parrent->right->val);
    }

    if(current_parrent->parrent == NULL){
        pom = current;

        current_parrent->parrent = current;
        return pom;
    }
    else {
        current->parrent = current_parrent->parrent;

        if(current_parrent->val > current_parrent->parrent->val)
            current->parrent->right = current;

        else if(current_parrent->val < current_parrent->parrent->val)
            current->parrent->left = current;
    }

    current_parrent->parrent = current;
    printf(".current: %d, head: %d, current right:\n", current->val, head->val);

    return head;

}


NODE *do_rotations(NODE *head, NODE *current, int which_rotation){
    NODE *pom;

    if(which_rotation == LEFTRIGHT){
        head = left_rotations(head, current);
        head = right_rotations(head, current);

        current->color = BLACK;
        current->right->color = RED;
    }

    else if(which_rotation == RIGHTLEFT){
        head = right_rotations(head, current);
        head = left_rotations(head, current);

        current->color = BLACK;
        current->left->color = RED;
    }

    else if(which_rotation == RIGHTRIGHT){
        // printf("!!!!!!!current %d current->parent: %d %d\n", current->val, current->parrent->val, current->parrent->parrent->val);
        current->parrent->color = BLACK;
        current->parrent->parrent->color = RED;
        pom = left_rotations(head, current->parrent);
        // printf("HEAD VALUE: %d %d %d %d\n", pom->left->left->val, pom->left->val, pom->right->val, pom->left->right->val);
        // print2DUtil(pom, 0);
        return pom;
    }


    return head;
}


/**
 * There will be rules check of black red alg.
*/
NODE *rules_check(NODE *head, NODE *current){
    NODE *pom;
    NODE *parent_sibling;
    int which_rotation;
    
    /**
     * 3. If parent is black
    */
    if(current == head || current->parrent->color == BLACK){
        return head;
    }

    /**
     * Red-red parent/child relationship
    */
    parent_sibling = find_parent_sibling(head, current);

    if(current->val ==  30){
        printf("now!%d %d\n", current->parrent->val, current->parrent->parrent->val);
    }

    /**
     * 4.b If parent is red and parent sibling is red as well - change colors and recheck
    */
    if(parent_sibling != NULL && parent_sibling->color == RED){
        printf("mam rodica RED farby, moja hodnota: %d, hodnota rodica: %d, farba suseda rodica BLACK a jeho hodnota %d\n", current->val, current->parrent->val, parent_sibling->val);

        parent_sibling->color = BLACK;
        current->parrent->color = BLACK;

        if(current->parrent->parrent != head)
            current->parrent->parrent->color = RED;
        
        // printf("haha\n");
        rules_check(head, current->parrent->parrent);
    }

    /**
     * 4.a If parent is red and sibling is black -> rotation and recolor
    */
    else{
        printf("mam rodica RED farby, moja hodnota: %d, hodnota rodica: %d, hodnota suseda rodica: NULL alebo farba black\n", current->val, current->parrent->val);

        which_rotation = check_which_rotation(head, current);
        printf("which rotation: %d\n", which_rotation);
        pom = do_rotations(head, current, which_rotation);
        // print2DUtil(pom, 0);
        // printf("current value: %d\n", pom->val);
        return pom;
    }
}


NODE *insert(NODE *head, int new_value){
    NODE *current, *parrent, *pom;
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
    pom = rules_check(head, current);
    // print2DUtil(pom, 0);
    // printf("!HEAD VALUE: %d\n", pom->val);

    return pom;
}


int main(void) {
    NODE *head;

    head = insert(head, 10);
    head = insert(head, 18);
    head = insert(head, 7);
    head = insert(head, 15);
    head = insert(head, 16);
    head = insert(head, 30);
    head = insert(head, 25);
    head = insert(head, 40);
    // head = insert(head, 60);
    // head = insert(head, 2);
    // head = insert(head, 1);
    // head = insert(head, 70);

    print2DUtil(head, 0);
}
