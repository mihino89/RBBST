#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define size 11

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

float load_factor(int max, int akt){
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
        hash_table[hash].chain_root = new_hash_item;
    } else {
        current = hash_table[hash].chain_root;
        while(current->next != NULL){
            if(current->val == value) 
                return;
            current = current->next;
        }
        current->next = new_hash_item;
    }
}


void arr_init(){
    hash_table = (HASH_TABLE *)malloc(ARRAY_SIZE * sizeof(HASH_TABLE));

    for(int i = 0; i < ARRAY_SIZE; i++){
        hash_table[i].chain_root = NULL;
    }
}



int main_chaining_hashing(int n, int arr[]){
    int old_size;
    HASH_TABLE* new_bigger_arr;

    ARRAY_SIZE = eratosten(n);
    arr_init();

    // TODO - osetrit nech array_size je vacsi ako n, nie mensi
    for(int i = 1; i < ARRAY_SIZE; i ++){
        // printf("main iteration: %d\n", i);
        insert_chaining_hash(arr[i]);
        
        
        // // resizing
        // if(load_factor(n, i)){
        //     old_size = ARRAY_SIZE;
        //     ARRAY_SIZE = eratosten(3*n);
        //     printf("new size: %d\n", ARRAY_SIZE);
        //     new_bigger_arr = arr_init();
        //     struct_arr = re_indexing_sizing(struct_arr, new_bigger_arr, old_size);
        // }
    }
}


// NODE2 *re_indexing_sizing(NODE2 *arr, NODE2 *new_node_arr, int old_arr_size){
//     NODE2 *current, *current2;
//     int new_hash;
//     printf("old size: %d\n", old_arr_size);

//     for(int i = 0; i < old_arr_size; i++){
//         // printf("iteration: %d\n", i );
//         if((arr + i) != NULL && arr[i].next != NULL){
//             current = (arr+i);

//             while(current->next != NULL){
//                 new_hash = generate_hash(current->val, ARRAY_SIZE);
//                 current2 = (new_node_arr+new_hash);

//                 if(current2 == NULL){
//                     current2 = current;
//                 }
//                 else{
//                     while(current2->next != NULL){
//                         current2 = current2->next;
//                     }
//                     current2->next = current;
//                 }

//                 current = current->next;
//             }            
//         }
//         else if((arr+i) != NULL && (arr+i)->next == NULL){

//             /* pre indexing - skontrul aj kyblik */
//             new_hash = generate_hash((arr+i)->val, ARRAY_SIZE);
//             current = (new_node_arr+new_hash);

//             if(current == NULL){
//                 current = (arr+i);
//             }
//             else{
//                 while(current->next != NULL){
//                     current = current->next;
//                 }
//                 current->next = (arr+i);
//             }
//         }
//     }

//     free(struct_arr);
//     struct_arr = new_node_arr;

//     // TODO - aktualizuj nodik ako new node arr
// }