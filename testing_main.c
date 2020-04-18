#include <stdio.h>
#include <time.h>   	
#include "AVL_tree.c"
#include "Red_Black_tree.c"
#include "chaining_hashing.c"
#include "linear_probing.c"

#define TEST_BASIC_SIZE 1000000
#define TEST_BIG_NUMBERS 200000

#define INSERT 0
#define SEARCH 1


int searching_choice(){
    int value;

    printf("Prosim zadajte hodnotu ktoru hladate v datasete: ");
    scanf("%d", &value);

    return value;
}

void test_basic_red_black_tree(int *arr, int arr_size, int additional_choice){
    int searching_number;
    NODE *head=NULL, *founded;
    double time_spent = 0.0;

    if(additional_choice == INSERT){
        clock_t begin = clock();
        for (int i = 0; i < arr_size; i++) {    
            head = insert_red_black_tree(head, arr[i]);
        }
        clock_t end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Cas potrebny pre vlozenie dataset algoritmu RED BLACK TREE is %f seconds\n", time_spent);
        return;
    }

    searching_number = searching_choice();
    for (int i = 0; i < arr_size; i++)    
        head = insert_red_black_tree(head, arr[i]);
        

    clock_t begin = clock();
    founded = search_red_black(head, searching_number);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    if(founded != NULL){
        printf("Hodnota %d bola uspesne najdena v datasete za cas %f sekund\n", founded->val, time_spent);
        return;
    }

    printf("Hodnota sa nenasla v datasete\n");
}


void test_basic_avl_tree(int *arr, int arr_size, int additional_choice){
    int searching_number;
    Node *head = NULL, *founded = NULL;
    double time_spent = 0.0;

    if(additional_choice == INSERT){
        clock_t begin = clock();
        for (int i = 0; i < arr_size; i++)   
            head = insert_avl(head, arr[i]);
        
        clock_t end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Cas potrebny pre vlozenie dataset algoritmu AVL TREE is %f seconds\n", time_spent);
        return;
    }

    searching_number = searching_choice();
    for (int i = 0; i < arr_size; i++)   
        head = insert_avl(head, arr[i]);

    clock_t begin = clock();
    founded = search_avl(head, searching_number);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    if(founded != NULL){
        printf("Hodnota %d bola uspesne najdena v datasete za cas %f sekund\n", founded->key, time_spent);
        return;
    }

    printf("Hodnota sa nenasla v datasete\n");  
}


void test_basic_chaining_hashing(int *input_data, int input_data_size, int additional_choice){
    int *hash_table_size = (int *)malloc(sizeof(int));
    int searching_number;
    double time_spent = 0.0;
    HASH_ITEM *founded;
    HASH_TABLE *hash_table;

    if(additional_choice == INSERT){
        clock_t begin = clock();
        hash_table = main_chaining_hashing(hash_table, hash_table_size, input_data, input_data_size);
        clock_t end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Cas potrebny pre vlozenie dataset algoritmu Chaining hash table is %f seconds\n", time_spent);
    } else {
        searching_number = searching_choice();
        hash_table = main_chaining_hashing(hash_table, hash_table_size, input_data, input_data_size);

        clock_t begin = clock();
        founded = search_chaining_hashing(hash_table, *hash_table_size, searching_number);
        clock_t end = clock();


        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        if(founded != NULL){
            printf("Hodnota %d bola uspesne najdena v datasete za cas %f sekund\n", founded->val, time_spent);
        } else{
            printf("Hodnota sa nenasla v datasete\n");  
        }
    }

    hash_table_free(hash_table, *hash_table_size);
    free(hash_table);
}


void test_basic_linear_probing(int *arr, int arr_size, int additional_choice){
    int searching_number;
    double time_spent = 0.0;
    ITEM *founded;
    
    if(additional_choice == INSERT){
        clock_t begin = clock();
        main_linear_probing(arr_size, arr);
        clock_t end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Cas potrebny pre vlozenie dataset algoritmu Linear probing hash table is %f seconds\n", time_spent);
        return;
    }

    searching_number = searching_choice();
    main_linear_probing(arr_size, arr);

    clock_t begin = clock();
    founded = search_linear_probing(searching_number);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    if(founded != NULL){
        printf("Hodnota %d bola uspesne najdena v datasete za cas %f sekund\n", founded->key, time_spent);
        return;
    }

    printf("Hodnota sa nenasla v datasete\n");  
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


int *prepare_dataset_user_input(int *dataset_size){
    int *arr, i=0;

    printf("Zadajte velkost pola, ktore chcete vlozit: ");
    scanf("%d", dataset_size);
    arr = (int *)malloc(*dataset_size * sizeof(int));
    
    printf("Zadajte prosim prvky datasetu ktore chcete vlozit (maximum is: %d)\n", *dataset_size);
    
    for(i = 0; i < *dataset_size; i++){
        scanf("%d", (arr + i));
    }

    for(i = 0; i < *dataset_size; i++){
        printf("%d ", *(arr + i));
    }
    printf("\n");

    return arr;
}


int additional_menu(){
    int choice;

    printf("\t\t- 0. Vlozenie datasetu do algoritmu\n");
    printf("\t\t- 1. Hladanie v datasete pomocou algoritmu \n");

    scanf("%d", &choice);

    if(choice == INSERT){
        return INSERT;
    }

    return SEARCH;
}


void testing_enviroment(){
    int choice, additional_choice;
    int *dataset, *dataset2, *dataset3, *dataset3_size;

    dataset3_size = (int *)malloc(sizeof(int));
    *dataset3_size = 0;

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
    printf("\t- 10. Vlastny test - Red Black tree\n");
    printf("\t- 11. Vlastny test - AVL tree\n");
    printf("\t- 12. Vlastny test - Chaining hash table - with resizing\n");
    printf("\t- 13. Vlastny test - Linear probing hash table\n");
    printf("\t- 14. Vlastny test - vsetky 4 algoritmy porovnanie\n");
    printf("\t- 15. Nechcem uz testovat\n");

    dataset = prepare_dataset_basic_test(TEST_BASIC_SIZE);
    dataset2 = prepare_dataset_with_collisions_test(TEST_BIG_NUMBERS);
    scanf("%d", &choice);

    switch (choice) {
        case 0:
            printf("======= Zakladny test Red Black tree =======\n");
            additional_choice = additional_menu();
            test_basic_red_black_tree(dataset, TEST_BASIC_SIZE, additional_choice);
            break;
        case 1:
            printf("======= Zakladny test AVL tree =======\n");
            additional_choice = additional_menu();
            test_basic_avl_tree(dataset, TEST_BASIC_SIZE, additional_choice);
            break;
        case 2:
            printf("======= Zakladny test Chaining hash table - with resizing =======\n");
            additional_choice = additional_menu();
            test_basic_chaining_hashing(dataset, TEST_BASIC_SIZE, additional_choice);
            break;
        case 3:
            printf("======= Zakladny test Linear probing hash table =======\n");
            additional_choice = additional_menu();
            test_basic_linear_probing(dataset, TEST_BASIC_SIZE, additional_choice);
            break;
        case 4:
            printf("======= Zakladny test - vsetky 4 algoritmy porovnanie =======\n");
            additional_choice = additional_menu();
            test_basic_red_black_tree(dataset, TEST_BASIC_SIZE, additional_choice);
            test_basic_avl_tree(dataset, TEST_BASIC_SIZE, additional_choice);
            test_basic_chaining_hashing(dataset, TEST_BASIC_SIZE, additional_choice);
            test_basic_linear_probing(dataset, TEST_BASIC_SIZE, additional_choice);
            break;
        case 5:
            printf("======= Test s diverzitnymi hodnotami - Red Black tree =======\n");
            additional_choice = additional_menu();
            test_basic_red_black_tree(dataset2, TEST_BIG_NUMBERS, additional_choice);
            break;
        case 6:
            printf("======= Test s diverzitnymi hodnotami - AVL tree =======\n");
            additional_choice = additional_menu();
            test_basic_avl_tree(dataset2, TEST_BIG_NUMBERS, additional_choice);
            break;
        case 7:
            printf("======= Test s diverzitnymi hodnotami - Chaining hash table - with resizing =======\n");
            additional_choice = additional_menu();
            test_basic_chaining_hashing(dataset2, TEST_BIG_NUMBERS, additional_choice);
            break;
        case 8:
            printf("======= Test s diverzitnymi hodnotami - Linear probing hash table =======\n");
            additional_choice = additional_menu();
            test_basic_linear_probing(dataset2, TEST_BIG_NUMBERS, additional_choice);
            break;
        case 9:
            printf("======= Test s diverzitnymi hodnotami - vsetky 4 algoritmy porovnanie =======\n");
            additional_choice = additional_menu();
            test_basic_red_black_tree(dataset2, TEST_BIG_NUMBERS, additional_choice);
            test_basic_avl_tree(dataset2, TEST_BIG_NUMBERS, additional_choice);
            test_basic_chaining_hashing(dataset2, TEST_BIG_NUMBERS, additional_choice);
            test_basic_linear_probing(dataset2, TEST_BIG_NUMBERS, additional_choice);
            break;
        case 10:
            printf("======= Vlastny test - Red Black tree =======\n");
            dataset3 = prepare_dataset_user_input(dataset3_size);
            additional_choice = additional_menu();
            test_basic_red_black_tree(dataset3, *dataset3_size, additional_choice);
            break;
        case 11:
            printf("======= Vlastny test - AVL tree =======\n");
            dataset3 = prepare_dataset_user_input(dataset3_size);
            additional_choice = additional_menu();
            test_basic_avl_tree(dataset3, *dataset3_size, additional_choice);
            break;
        case 12:
            printf("======= Vlastny test - Chaining hash table - with resizing =======\n");
            dataset3 = prepare_dataset_user_input(dataset3_size);
            // printf("*dataset3_size: %d\n", *dataset3_size);
            additional_choice = additional_menu();
            test_basic_chaining_hashing(dataset3, *dataset3_size, additional_choice);
            break;
        case 13:
            printf("======= Vlastny test - Linear probing hash table =======\n");
            dataset3 = prepare_dataset_user_input(dataset3_size);
            additional_choice = additional_menu();
            test_basic_linear_probing(dataset3, *dataset3_size, additional_choice);
            break;
        case 14:
            printf("======= Vlastny test - vsetky 4 algoritmy porovnanie =======\n");
            dataset3 = prepare_dataset_user_input(dataset3_size);
            additional_choice = additional_menu();
            test_basic_red_black_tree(dataset3, *dataset3_size, additional_choice);
            test_basic_avl_tree(dataset3, *dataset3_size, additional_choice);
            test_basic_chaining_hashing(dataset3, *dataset3_size, additional_choice);
            test_basic_linear_probing(dataset3, *dataset3_size, additional_choice);
            break;
        default:
            break;
    }
}


int main() { 
    testing_enviroment();
  
  return 0; 
} 