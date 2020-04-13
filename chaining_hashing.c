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
    HASH_ITEM *chain_last;
} HASH_TABLE;


// globalne pole 
HASH_TABLE* hash_table;
int ARRAY_SIZE;


int eratosten(int size_of_array){
    int i, j;
    int arr[size_of_array+1];

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
    // printf("load factor %lf\n", akt/max);
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

    // printf("tu to este funguje1: %d %d\n", hash, new_hash_item->val);

    if(hash_table[hash].chain_root == NULL){
        hash_table[hash].chain_root = hash_table[hash].chain_last = new_hash_item;
        printf("INSERT -> root je NULL na indexe %d prvy node s hodnotou: %d posledny: %d\n", hash, hash_table[hash].chain_root->val, hash_table[hash].chain_last->val);
    } else {
        current = hash_table[hash].chain_root;
        while(current->next != NULL){
            if(current->val == value) 
                return;
            current = current->next;
        }
        current->next = new_hash_item;
        hash_table[hash].chain_last = new_hash_item;
        printf("INSERT -> root nie je NULL na indexe %d ulozeny node s hodnotou: %d, predchadzajuci %d a root v chaine: %d\n", hash, current->next->val, current->val, hash_table[hash].chain_root->val);
    }
}


HASH_TABLE *arr_init(int arr_init_size){
    HASH_TABLE *arr_init = (HASH_TABLE *)malloc(arr_init_size * sizeof(HASH_TABLE));

    for(int i = 0; i < ARRAY_SIZE; i++){
        arr_init[i].chain_root = arr_init[i].chain_last = NULL;
    }

    return arr_init;
}


HASH_TABLE *re_indexing_sizing(int old_arr_size){
    HASH_TABLE * new_hash_table;
    HASH_ITEM *current, *current2;
    int new_hash;

    new_hash_table = arr_init(ARRAY_SIZE);

    for(int i = 0; i < old_arr_size; i++){
        if(hash_table[i].chain_root != NULL && hash_table[i].chain_root->next != NULL){
            printf("chaining root: %d\n", hash_table[i].chain_root->val);
            current = hash_table[i].chain_root;

            while(current != NULL){
                new_hash = generate_hash(current->val, ARRAY_SIZE);
                // current2 = new_hash_table[new_hash].chain_root;

                if(new_hash_table[new_hash].chain_root == NULL){
                    new_hash_table[new_hash].chain_root = new_hash_table[new_hash].chain_last = current;
                    printf("case 1\n");
                    printf("RE-INDEXING -> povodny NON-ROOT, new index root je NULL na indexe %d ulozeny node s hodnotou: %d\n", new_hash, new_hash_table[new_hash].chain_root->val);
                }
                else{
                    // while(current2->next != NULL){
                    //     current2 = current2->next;
                    // }
                    // current2->next = current;
                    new_hash_table[new_hash].chain_last->next = current;
                    new_hash_table[new_hash].chain_last = current;
                    printf("case 2\n");
                    printf("RE-INDEXING -> povodny NON-ROOT, new index root nie je NULL na indexe %d root node: %d a posledny chain (ten co som vlozil): %d\n", new_hash, new_hash_table[new_hash].chain_root->val, new_hash_table[new_hash].chain_last->val);
                }

                current = current->next;
            }            
        }
        /* V LL je iba jeden node */
        else if(hash_table[i].chain_root  != NULL && hash_table[i].chain_root->next == NULL){
            printf("chaining root: %d\n", hash_table[i].chain_root->val);
            /* pre indexing - skontrul aj kyblik */
            new_hash = generate_hash(hash_table[i].chain_root->val, ARRAY_SIZE);

            if(new_hash_table[new_hash].chain_root == NULL){
                new_hash_table[new_hash].chain_root = new_hash_table[new_hash].chain_last = hash_table[i].chain_root;
                printf("case 3\n");
                printf("RE-INDEXING -> povodny ROOT, new index root je NULL na indexe %d ulozeny node s hodnotou: %d\n", new_hash, new_hash_table[new_hash].chain_root->val);
            }
            else{
                new_hash_table[new_hash].chain_last->next = hash_table[i].chain_root;
                new_hash_table[new_hash].chain_last = hash_table[i].chain_root;
                printf("case 4\n");
                printf("RE-INDEXING -> povodny ROOT, new index root nie je NULL na indexe %d root node: %d a posledny chain (ten co som vlozil): %d\n", new_hash, new_hash_table[new_hash].chain_root, new_hash_table[new_hash].chain_last->val);
            }
        }
    }

    free(hash_table);
    return new_hash_table;
}


int main_chaining_hashing(int n, int arr[]){
    int old_size;
    HASH_TABLE *new_bigger_arr;
    HASH_ITEM *current;

    ARRAY_SIZE = eratosten(n);
    hash_table = arr_init(ARRAY_SIZE);

    printf("ARR_SIZE: %d\n", ARRAY_SIZE);

    for(int i = 0; i < n; i ++){
        // printf("main iteration: %d\n", i);
        insert_chaining_hash(arr[i]);
        
        // // resizing
        if(load_factor(ARRAY_SIZE, i) > 0.66){
            printf("resizing and reindexing!\n");
            old_size = ARRAY_SIZE;
            ARRAY_SIZE = eratosten(3*ARRAY_SIZE);
            hash_table = re_indexing_sizing(old_size);
        }
    }

    printf("final array size: %d\n", ARRAY_SIZE);
    for(int i = 0; i < ARRAY_SIZE; i ++){
        if(hash_table[i].chain_root == NULL){
            printf("chain: %d is NULL\n", i);
        }
        else {
            current = hash_table[i].chain_root;
            printf("chain: %d is ", i);
            while(current->next != NULL){
                printf("%d ", current->val);
                current = current->next;
            }
            printf("%d \n", current->val);
        }
    }
}