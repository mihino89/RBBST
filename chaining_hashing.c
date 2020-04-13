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
    int arr[size_of_array+1];

    // zaplni pole 1
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

    // printf("max: %d\n", max);

    return max;
}


/* Pri int datasete je to jedno, staci ulozit na value index */
int generate_hash(int value, int size_of_arr){
    return (value % size_of_arr);
}

float load_factor(float max, float akt){
    printf("load factor %lf\n", akt/max);
    return ((float) akt/max);
}


HASH_ITEM *createNewNode(int value){
    HASH_ITEM *new_hash_item = (HASH_ITEM *)malloc(sizeof(HASH_ITEM));

    new_hash_item->val = value;
    new_hash_item->next = NULL;

    return new_hash_item;
}


void insert_chaining_hash(int value){
    int hash;
    HASH_ITEM *new_hash_item, *current;


    new_hash_item = createNewNode(value);
    hash = generate_hash(value, ARRAY_SIZE);

    printf("tu to este funguje1: %d %d\n", hash, new_hash_item->val);

    if(hash_table[hash].chain_root == NULL){
        printf("root je NULL a novy root je s hodnotou: %d\n", value);
        hash_table[hash].chain_root = new_hash_item;
    } else {
        printf("root nieje NULL a val je s hodnotou: %d\n", value);
        current = hash_table[hash].chain_root;
        while(current->next != NULL){
            if(current->val == value) 
                return;
            current = current->next;
        }
        current->next = new_hash_item;
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
    HASH_TABLE * new_hash_table;
    HASH_ITEM *current, *current2;
    int new_hash;

    printf("old size: %d\n", old_arr_size);
    new_hash_table = arr_init(ARRAY_SIZE);

    for(int i = 0; i < old_arr_size; i++){
        if(hash_table[i].chain_root != NULL && hash_table[i].chain_root->next != NULL){
            current = hash_table[i].chain_root;

            while(current->next != NULL){
                new_hash = generate_hash(current->val, ARRAY_SIZE);
                current2 = new_hash_table[new_hash].chain_root;

                if(current2 == NULL){
                    current2 = current;
                }
                else{
                    while(current2->next != NULL){
                        current2 = current2->next;
                    }
                    current2->next = current;
                }

                current = current->next;
            }            
        }
        /* V LL je iba jeden node */
        else if(hash_table[i].chain_root  != NULL && hash_table[i].chain_root->next == NULL){

            /* pre indexing - skontrul aj kyblik */
            new_hash = generate_hash(hash_table[i].chain_root->val, ARRAY_SIZE);
            current = new_hash_table[new_hash].chain_root;

            if(current == NULL){
                current = hash_table[i].chain_root;
            }
            else{
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = hash_table[i].chain_root;
            }
        }
    }

    free(hash_table);
    return new_hash_table;
}


int main_chaining_hashing(int n, int arr[]){
    int old_size;
    HASH_TABLE* new_bigger_arr;

    ARRAY_SIZE = eratosten(n);
    hash_table = arr_init(ARRAY_SIZE);

    printf("ARR_SIZE: %d\n", ARRAY_SIZE);

    // TODO - osetrit nech array_size je vacsi ako n, nie mensi
    for(int i = 1; i < n; i ++){
        // printf("main iteration: %d\n", i);
        insert_chaining_hash(arr[i]);
        
        // // resizing
        if(load_factor(ARRAY_SIZE, i) > 0.66){
            printf("now!\n");
            old_size = ARRAY_SIZE;
            ARRAY_SIZE = eratosten(3*ARRAY_SIZE);
            printf("new size: %d\n", ARRAY_SIZE);
            hash_table = re_indexing_sizing(old_size);
        }
    }
}