#include <stdio.h>
#include <time.h>   	// for time()
#include "AVL_tree.c"
#include "Red_Black_tree.c"
#include "chaining_hashing.c"
#include "linear_probing.c"

#define TEST_BASIC_SIZE 1000000
#define TEST_BIG_NUMBERS 200000


void test_basic_red_black_tree(int *arr, int arr_size){
    NODE *head=NULL;
    double time_spent = 0.0;

    clock_t begin = clock();
    for (int i = 0; i < arr_size; i++) {    
        head = insert_red_black_tree(head, arr[i]);
    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased of RED BLACK TREE is %f seconds\n", time_spent);
}


void test_basic_avl_tree(int *arr, int arr_size){
    Node *head=NULL;
    double time_spent = 0.0;

    clock_t begin = clock();
    for (int i = 0; i < arr_size; i++) {    
        head = insert_avl(head, arr[i]);
    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased of AVL TREE is %f seconds\n", time_spent);
}


void test_basic_chaining_hashing(int *arr, int arr_size){
    double time_spent = 0.0;

    clock_t begin = clock();
    main_chaining_hashing(arr_size, arr);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased of Chaining hash table is %f seconds\n", time_spent);
}


void test_basic_linear_probing(int *arr, int arr_size){
    double time_spent = 0.0;
    
    clock_t begin = clock();
    main_linear_probing(arr_size, arr);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased of Linear probing hash table is %f seconds\n", time_spent);
}


void switcher(int *temp1, int *temp2){
    int temp = *temp1;
    *temp1 = *temp2;
    *temp2 = temp;
}


int *prepare_dataset_basic_test(int arr_size){
    int *arr, helper, randomIndex, i;
    
    arr  = (int *)malloc(arr_size * sizeof(int)); 

    for (i = 0; i < arr_size; i++)    
        arr[i] = i;

    for (i = 0; i < arr_size; i++) {  
        randomIndex = rand() % arr_size;
        switcher(&arr[i], &arr[randomIndex]);
    }

    return arr;
}


int *prepare_dataset_with_collisions_test(int arr_size){
    int *arr, helper, randomIndex, i;

    arr  = (int *)malloc(arr_size * sizeof(int)); 

    for (i = 0; i < arr_size; i++){
        if(i % 2 == 0){
            arr[i] = i*11;
        } else if(i % 3 == 0){
            arr[i] = i*13;
        } else if(i % 5 == 0){
            arr[i] = i*17;
        } else if(i % 7 == 0){
            arr[i] = i*19;
        } else {
            arr[i] = 23 * i;
        }
    }

    for (i = 0; i < arr_size; i++) {  
        randomIndex = rand() % arr_size;
        switcher(&arr[i], &arr[randomIndex]);
    }

    return arr;
}


void testing_enviroment()
{
    int choice;
    int *dataset, *dataset2;

    printf("======= Vitajte v testovacom prostredi vyhladavacich algoritmov v mnozinach! =======\n");
    printf("Prosim vyberte si test (cislo 0-6):\n");
    printf("\t- 0. Zakladny test - Red Black tree \n");
    printf("\t- 1. Zakladny test - AVL tree \n");
    printf("\t- 2. Zakladny test - Chaining hash table - with resizing \n");
    printf("\t- 3. Zakladny test - Linear probing hash table \n");
    printf("\t- 4. Zakladny test - vsetky 4 algoritmy porovnanie\n");
    printf("\t- 5. Test s diverzitnymi hodnotami - Red Black tree\n");
    printf("\t- 6. Test s diverzitnymi hodnotami - AVL tree\n");
    printf("\t- 7. Test s diverzitnymi hodnotami - Chaining hash table - with resizing\n");
    printf("\t- 8. Test s diverzitnymi hodnotami - Linear probing hash table\n");
    printf("\t- 9. Test s diverzitnymi hodnotami - vsetky 4 algoritmy porovnanie\n");
    printf("\t- 10. Nechcem uz testovat\n");

    dataset = prepare_dataset_basic_test(TEST_BASIC_SIZE);
    dataset2 = prepare_dataset_with_collisions_test(TEST_BIG_NUMBERS);
    scanf("%d", &choice);

    switch (choice) {
        case 0:
            printf("======= Zakladny test Red Black tree =======\n");
            test_basic_red_black_tree(dataset, TEST_BASIC_SIZE);
            break;
        case 1:
            printf("======= Zakladny test AVL tree =======\n");
            test_basic_avl_tree(dataset, TEST_BASIC_SIZE);
            break;
        case 2:
            printf("======= Zakladny test Chaining hash table - with resizing =======\n");
            test_basic_chaining_hashing(dataset, TEST_BASIC_SIZE);
            break;
        case 3:
            printf("======= Zakladny test Linear probing hash table =======\n");
            test_basic_linear_probing(dataset, TEST_BASIC_SIZE);
            break;
        case 4:
            printf("======= Zakladny test - vsetky 4 algoritmy porovnanie =======\n");
            test_basic_red_black_tree(dataset, TEST_BASIC_SIZE);
            test_basic_avl_tree(dataset, TEST_BASIC_SIZE);
            test_basic_chaining_hashing(dataset, TEST_BASIC_SIZE);
            test_basic_linear_probing(dataset, TEST_BASIC_SIZE);
            break;
        case 5:
            printf("======= Test s diverzitnymi hodnotami - Red Black tree =======\n");
            test_basic_red_black_tree(dataset2, TEST_BIG_NUMBERS);
            break;
        case 6:
            printf("======= Test s diverzitnymi hodnotami - AVL tree =======\n");
            test_basic_avl_tree(dataset2, TEST_BIG_NUMBERS);
            break;
        case 7:
            printf("======= Test s diverzitnymi hodnotami - Chaining hash table - with resizing =======\n");
            test_basic_chaining_hashing(dataset2, TEST_BIG_NUMBERS);
            break;
        case 8:
            printf("======= Test s diverzitnymi hodnotami - Linear probing hash table =======\n");
            test_basic_linear_probing(dataset2, TEST_BIG_NUMBERS);
            break;
        case 9:
            printf("======= Test s diverzitnymi hodnotami - vsetky 4 algoritmy porovnanie =======\n");
            test_basic_red_black_tree(dataset2, TEST_BIG_NUMBERS);
            test_basic_avl_tree(dataset2, TEST_BIG_NUMBERS);
            test_basic_chaining_hashing(dataset2, TEST_BIG_NUMBERS);
            test_basic_linear_probing(dataset2, TEST_BIG_NUMBERS);
            break;
        default:
            break;
    }
}


int main() { 
    testing_enviroment();
  
  return 0; 
} 