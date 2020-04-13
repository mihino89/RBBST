#include <stdio.h>
#include <time.h>   	// for time()
#include "AVL_tree.c"
#include "Red_Black_tree.c"
#include "chaining_hashing.c"
 // https://www.geeksforgeeks.org/hashing-set-3-open-addressing/

void test_big_avl(){
    Node *head=NULL;
    double time_spent = 0.0;

    int number = 1000000;
    int array[number];

    for (int i = 0; i < number; i++) {     
        array[i] = i;
    }

    for (int i = 0; i < number; i++) {    
        int temp = array[i];
        int randomIndex = rand() % number;

        array[i]           = array[randomIndex];
        array[randomIndex] = temp;
    }

    clock_t begin = clock();
    for (int i = 0; i < number; i++) {    
        head = insert_avl(head, array[i]);
    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased of AVL TREE is %f seconds\n", time_spent);
}

void test_big_red_black(){
    NODE *head=NULL;
    double time_spent = 0.0;

    int number = 1000000;
    int array[number];

    for (int i = 0; i < number; i++) {     
        array[i] = i;
    }

    for (int i = 0; i < number; i++) {    
        int temp = array[i];
        int randomIndex = rand() % number;

        array[i]           = array[randomIndex];
        array[randomIndex] = temp;
    }

    clock_t begin = clock();
    for (int i = 0; i < number; i++) {    
        head = insert_red_black_tree(head, array[i]);
    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased of RED BLACK TREE is %f seconds\n", time_spent);
}


void test_hashing(){
    int number = 11;
    int array[number];

    for (int i = 1; i < number-1; i++) {     
        array[i] = i;
    }
    array[10] = 2;

    main_chaining_hashing(number, array);
}


int main() 
{ 
  struct Node *root = NULL; 

//   test_big_avl();
//   test_big_red_black();

  test_hashing();
  
  return 0; 
} 