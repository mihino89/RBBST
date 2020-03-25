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

    if(current == NULL || current->parrent == NULL){
        return pom;
    }

    NODE *current_parrent = current->parrent;

    current_parrent->left = current->right;
    if(current->right != NULL){
        current->right->parrent = current_parrent;
    }

    if(current_parrent->parrent == NULL){
        current->parrent = NULL;
        pom = current;
    }
    else {
        current->parrent = current_parrent->parrent;

        if(current_parrent->val > current_parrent->parrent->val)
            current->parrent->right = current;

        else if(current_parrent->val < current_parrent->parrent->val)
            current->parrent->left = current;
    }

    // printf("haha\n");
    current->right = current_parrent;
    current_parrent->parrent = current;
    // printf("pom: %d pom left: %d pom right: %d\n", pom->val, pom->left->parrent->val, pom->right->parrent->val);

    return pom;

}


NODE *do_rotations(NODE *head, NODE *current, int which_rotation){
    NODE *pom;

    if(which_rotation == LEFTRIGHT){
        pom = left_rotations(head, current);
        // print2DUtil(head, 0);
        pom = right_rotations(head, current);
        // printf("pom: %d pom left: %d pom right: %d\n", pom->val, pom->left->val, pom->right->val);

        current->color = BLACK;
        current->right->color = RED;
    }

    else if(which_rotation == RIGHTLEFT){
        pom = right_rotations(head, current);
        pom = left_rotations(head, current);

        current->color = BLACK;
        current->left->color = RED;
    }

    else if(which_rotation == RIGHTRIGHT){
        // printf("!!!!!!!current %d current->parent: %d %d\n", current->val, current->parrent->val, current->parrent->parrent->val);
        current->parrent->color = BLACK;
        current->parrent->parrent->color = RED;
        pom = left_rotations(head, current->parrent);
    }

    else if(which_rotation == LEFTLEFT){
        current->parrent->color = BLACK;
        current->parrent->parrent->color = RED;
        pom = right_rotations(head, current->parrent);
    }

    return pom;
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

    /**
     * 4.b If parent is red and parent sibling is red as well - change colors and recheck
    */
    if(parent_sibling != NULL && parent_sibling->color == RED){
        // printf("mam rodica RED farby, moja hodnota: %d, hodnota rodica: %d, farba suseda rodica BLACK a jeho hodnota %d\n", current->val, current->parrent->val, parent_sibling->val);

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
        // printf("mam rodica RED farby, moja hodnota: %d, hodnota rodica: %d, hodnota suseda rodica: NULL alebo farba black\n", current->val, current->parrent->val);

        which_rotation = check_which_rotation(head, current);
        // printf("which rotation: %d\n", which_rotation);
        pom = do_rotations(head, current, which_rotation);
        // print2DUtil(pom, 0);
        // printf("current value: %d\n", pom->val);
        // rules_check(head, current->parrent->parrent);
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

    return pom;
}


void test_small(){
    NODE *head = NULL;

    int array[300];

    for (int i = 0; i < 300; i++) {     // fill array
        array[i] = i;
    }

    for (int i = 0; i < 300; i++) {    // shuffle array
        int temp = array[i];
        int randomIndex = rand() % 300;

        array[i]           = array[randomIndex];
        array[randomIndex] = temp;
    }


    for (int i = 0; i < 300; i++) {    // print array
        printf("\n done with population %d \n", array[i]);
        head = insert(head, array[i]);
    }

    print2DUtil(head, 0);
}


int main(void) {
    NODE *head=NULL;

    head = insert(head, 153);
    head = insert(head, 886);
    head = insert(head, 457);
    head = insert(head, 922);
    head = insert(head, 771);
    head = insert(head, 335);
    head = insert(head, 1386);
    head = insert(head, 492);
    head = insert(head, 940);
    head = insert(head, 48);
    // head = insert(head, 1048);
    // head = insert(head, 1139);
    // head = insert(head, 509);
    // head = insert(head, 1062);
    // head = insert(head, 1702);
    // head = insert(head, 1926);
    // head = insert(head, 540);
    // head = insert(head, 1985); 
    // head = insert(head, 684);
    // head = insert(head, 863);
    // head = insert(head, 1211);
    // head = insert(head, 397);
    // head = insert(head, 48);

    // test_small();
    // int number = 2000;
    // int array[number];

    // for (int i = 0; i < number; i++) {     // fill array
    //     array[i] = i;
    // }

    // for (int i = 0; i < number; i++) {    // shuffle array
    //     int temp = array[i];
    //     int randomIndex = rand() % number;

    //     array[i]           = array[randomIndex];
    //     array[randomIndex] = temp;
    // }


    // for (int i = 0; i < number; i++) {    // print array
    //     printf("\n done with population %d \n", array[i]);
    //     head = insert(head, array[i]);
    // }
    print2DUtil(head, 0);
}
