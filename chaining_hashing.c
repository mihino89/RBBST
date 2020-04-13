#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define size 11

typedef struct node2{ 
    int *val; 
    struct node2 *next;
} NODE2;

//pole 
NODE2* struct_arr;
int ARRAY_SIZE;

/* Pri int datasete je to jedno, staci ulozit na value index */
int generate_hash(int value, int size_of_arr){
    return (value % size_of_arr);
}

// NODE2 *createNode(int val){
//     NODE2 *node = (NODE2 *)malloc(sizeof(NODE2));

//     node->next = NULL;
//     node->val = val;

//     return node;
// }

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


void insert_chaining_hash(NODE2 *arr, int value){
    static int num_of_nodes_in_arr = 0;
    int hash, nearest_prime_num;
    NODE2 *previous_node;

    hash = generate_hash(value, ARRAY_SIZE);
    printf("tu to este funguje1: %d %d\n", hash, ARRAY_SIZE);

// ((arr+ hash)->val)
    if(arr[hash]->val == NULL){
        
        *((arr+hash)->val) = value;
         printf("je to nula a mozem to sem ulozit\n");
        (arr+hash)->next = NULL;
    } else {
        // printf("je to nula a mozem to sem ulozit\n");
        previous_node = (arr+hash);
        while(previous_node->next != NULL){
            previous_node = previous_node->next;
        }
        *(previous_node->next->val) = value;
        previous_node->next->next = NULL;
    }

    num_of_nodes_in_arr++;
}


void re_indexing_sizing(NODE2 *arr, NODE2 *new_node_arr){
    int old_arr_size = ARRAY_SIZE/3;
    NODE2 *current, *current2;
    int new_hash;

    for(int i = 0; i <= old_arr_size; i++){
        if((arr + i) != NULL && (arr + i)->next != NULL){
            current = (arr+i);

            while(current->next != NULL){
                new_hash = generate_hash(*(current->val), ARRAY_SIZE);
                current2 = (new_node_arr+new_hash);

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
        else if((arr+i) != NULL && (arr+i)->next == NULL){

            /* pre indexing - skontrul aj kyblik */
            new_hash = generate_hash(*((arr+i)->val), ARRAY_SIZE);
            current = (new_node_arr+new_hash);

            if(current == NULL){
                current = (arr+i);
            }
            else{
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = (arr+i);
            }
        }
    }

    free(struct_arr);
    struct_arr = new_node_arr;

    // TODO - aktualizuj nodik ako new node arr
}


NODE2 *arr_init(){
    NODE2* arr = malloc(ARRAY_SIZE * sizeof(NODE2));

    for(int i = 0; i < ARRAY_SIZE; i++){
        // struct_arr[i] = NULL;
        arr[i] = NULL;
    }

    return arr;
}



void arr_null_init(){
    for(int i = 0; i < ARRAY_SIZE; i++){
        // struct_arr[i] = NULL;
        (struct_arr + i) = NULL;
    }
}


int main_chaining_hashing(int n, int arr[]){
    NODE2* new_bigger_arr;
    ARRAY_SIZE = eratosten(n);
    struct_arr = arr_init();
    arr_null_init();

    printf("tu to este funguje: %d %d\n", ARRAY_SIZE, n);

    for(int i = 1; i < n; i ++){
        printf("main iteration: %d\n", i);
        insert_chaining_hash(struct_arr, arr[i]);
        if(i > ARRAY_SIZE/2){
            ARRAY_SIZE = eratosten(3*n);
            new_bigger_arr = arr_init();
            re_indexing_sizing(struct_arr, new_bigger_arr);
        }
    }
}