#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SMALLER_PRIME_NUM 2


typedef struct hash_item{ 
    int val; 
    struct hash_item *next;
} HASH_ITEM;

typedef struct hash_table{
    HASH_ITEM *chain_root;
} HASH_TABLE;


int eratosten(int size_of_array){
    int i, j, max;
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


void insert_chaining_hash(HASH_TABLE *insert_hash_table, int value, int hash_table_size){
    int hash;
    HASH_ITEM *new_hash_item, *current;


    new_hash_item = createNewNode(value);
    hash = generate_hash(value, hash_table_size);

    if(insert_hash_table[hash].chain_root == NULL){
        insert_hash_table[hash].chain_root = new_hash_item;
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
    printf("arr_init_size: %d\n", arr_init_size);
    HASH_TABLE *hash_table_init = malloc(arr_init_size * sizeof(HASH_TABLE));
    printf("arr_init_size2: %d\n", arr_init_size);

    for(int i = 0; i < arr_init_size; i++){
        hash_table_init[i].chain_root = NULL;
    }

    return hash_table_init;
}


void hash_table_free(HASH_TABLE *hash_table_to_free, int hash_table_size){
    HASH_ITEM *current, *temp;
    int i;

    for(i = 0; i < hash_table_size; i++){
        if(hash_table_to_free[i].chain_root != NULL){
            current = hash_table_to_free[i].chain_root;

            while(current != NULL){
                temp = current;
                current = current->next;
                free(temp);
            }
        }
    }
}


HASH_TABLE *re_indexing_sizing(HASH_TABLE *hash_table, int new_arr_size, int old_arr_size){
    HASH_TABLE *new_hash_table;
    HASH_ITEM *current, *temp;
    int new_hash;

    new_hash_table = arr_init(new_arr_size);

    for(int i = 0; i < old_arr_size; i++){
        if(hash_table[i].chain_root != NULL){
            // printf("chaining root: %d\n", hash_table[i].chain_root->val);
            current = hash_table[i].chain_root;

            while(current != NULL){
                insert_chaining_hash(new_hash_table, current->val, new_arr_size);
                temp = current;
                current = current->next;
                free(temp);
            }            
        }
    }

    free(hash_table);
    return new_hash_table;
}


HASH_ITEM *search_chaining_hashing(HASH_TABLE *hash_table, int hash_table_size, int value){
    int hash;
    HASH_ITEM *current;

    hash = generate_hash(value, hash_table_size);
    current = hash_table[hash].chain_root;

    if(current == NULL)
        return NULL;

    while(current != NULL){
        if(current->val == value)
            return current;
        current = current->next;
    }

    return NULL;
}


HASH_TABLE *main_chaining_hashing(HASH_TABLE *main_hash_table, int *hash_table_size, int arr[], int input_data_arr){
    int old_size;

    if(input_data_arr <= 0){
        return NULL;
    }
    if(input_data_arr == 1)
        *hash_table_size = SMALLER_PRIME_NUM;
    else
        *hash_table_size = eratosten(input_data_arr);

    main_hash_table = arr_init(*hash_table_size);

    for(int i = 0; i < input_data_arr; i ++){
        // resizing
        if(load_factor(*hash_table_size, i) >= 0.66){
            old_size = *hash_table_size;

            *hash_table_size = eratosten(2*(*hash_table_size));
            printf("resizing and reindexing %d %d\n", *hash_table_size, old_size);
            main_hash_table = re_indexing_sizing(main_hash_table, *hash_table_size, old_size);
        }
        // printf("iteration %d\n", i);
        insert_chaining_hash(main_hash_table, arr[i], *hash_table_size);
    }


    return main_hash_table;
}