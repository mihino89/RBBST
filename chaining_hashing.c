#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct hash_item{ 
    int val; 
    struct hash_item *next;
} HASH_ITEM;

typedef struct hash_table{
    HASH_ITEM *chain_root;
} HASH_TABLE;


// globalne pole 
HASH_TABLE* hash_table;
int ARRAY_SIZE;


int eratosten(int size_of_array){
    int i, j;
    int *arr = (int *)malloc(size_of_array * sizeof(int));

    for (i = 0; i <= size_of_array; i++)
        arr[i] = 1;


    for (i = 2; i*i <= size_of_array; i++){
        if(arr[i] == 1){
            for (j = i * i; j <= size_of_array; j+=i){
                arr[j] = 0;
            }
        }
    }

    int max;

    for (int i = 2; i <= size_of_array; i++){
        if(arr[i] == 1)
            max = i;
    }

    return max;
}


/* Pri int datasete je to jedno, staci ulozit na value index */
int generate_hash(int value, int size_of_arr){
    return (value % size_of_arr);
}

float load_factor(float max, float akt){
    return ((float) akt/max);
}


HASH_ITEM *createNewNode(int value){
    HASH_ITEM *new_hash_item = (HASH_ITEM *)malloc(sizeof(HASH_ITEM));

    new_hash_item->val = value;
    new_hash_item->next = NULL;

    return new_hash_item;
}


void insert_chaining_hash(HASH_TABLE *insert_hash_table, int value){
    int hash;
    HASH_ITEM *new_hash_item, *current;


    new_hash_item = createNewNode(value);
    hash = generate_hash(value, ARRAY_SIZE);

    if(insert_hash_table[hash].chain_root == NULL){
        insert_hash_table[hash].chain_root = new_hash_item;
        // printf("INSERT -> root je NULL na indexe %d prvy node s hodnotou: %d\n", hash, insert_hash_table[hash].chain_root->val);
    } else {
        current = insert_hash_table[hash].chain_root;
        while(current->next != NULL){
            if(current->val == value) 
                return;
            current = current->next;
        }
        current->next = new_hash_item;
        // printf("INSERT -> root nie je NULL na indexe %d ulozeny node s hodnotou: %d, predchadzajuci %d a root v chaine: %d\n", hash, current->next->val, current->val, insert_hash_table[hash].chain_root->val);
    }
}


HASH_TABLE *arr_init(int arr_init_size){
    HASH_TABLE *arr_init = (HASH_TABLE *)malloc(arr_init_size * sizeof(HASH_TABLE));

    for(int i = 0; i < ARRAY_SIZE; i++){
        arr_init[i].chain_root = NULL;
    }

    return arr_init;
}


HASH_TABLE *re_indexing_sizing(int old_arr_size){
    HASH_TABLE *new_hash_table;
    HASH_ITEM *current, *temp;
    int new_hash;

    new_hash_table = arr_init(ARRAY_SIZE);

    for(int i = 0; i < old_arr_size; i++){
        if(hash_table[i].chain_root != NULL){
            // printf("chaining root: %d\n", hash_table[i].chain_root->val);
            current = hash_table[i].chain_root;

            while(current != NULL){
                insert_chaining_hash(new_hash_table, current->val);
                temp = current;
                current = current->next;
                free(temp);
            }            
        }
    }

    free(hash_table);
    return new_hash_table;
}


HASH_ITEM *search_chaining_hashing(int value){

    // mozno to bude padat na size
    int hash;
    HASH_ITEM *current;

    hash = generate_hash(value, ARRAY_SIZE);
    current = hash_table[hash].chain_root;

    if(current == NULL){
        printf("Prvok sa nenachadza v hash tabulke! \n");
        return NULL;
    }

    while(current != NULL){
        if(current->val == value)
            return current;
        current = current->next;
    }

    return NULL;
}


HASH_TABLE *main_chaining_hashing(int n, int arr[]){
    int old_size;
    HASH_TABLE *new_bigger_arr;
    HASH_ITEM *current;

    ARRAY_SIZE = eratosten(n);
    hash_table = arr_init(ARRAY_SIZE);

    for(int i = 0; i < n; i ++){
        // printf("funguje %d\n", i);
        insert_chaining_hash(hash_table, arr[i]);
        
        // resizing
        if(load_factor(ARRAY_SIZE, i) > 0.66){
            // pintrintf("load factor %d\n", i);
            old_size = ARRAY_SIZE;
            ARRAY_SIZE = eratosten(3*ARRAY_SIZE);
            hash_table = re_indexing_sizing(old_size);
        }
    }

    return hash_table;

    // printf("final array size: %d\n", ARRAY_SIZE);
    // for(int i = 0; i < ARRAY_SIZE; i ++){
    //     if(hash_table[i].chain_root == NULL){
    //         printf("chain: %d is NULL\n", i);
    //     }
    //     else {
    //         current = hash_table[i].chain_root;
    //         printf("chain: %d is ", i);
    //         while(current->next != NULL){
    //             printf("%d ", current->val);
    //             current = current->next;
    //         }
    //         printf("%d \n", current->val);
    //     }
    // }
}