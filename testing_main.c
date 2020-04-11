#include <stdio.h>
#include <time.h>   	// for time()
#include "AVL_tree.c"
#include "Red_Black_tree.c"
 

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

int main() 
{ 
  struct Node *root = NULL; 

  test_big_avl();
  test_big_red_black();
  
  return 0; 
} 