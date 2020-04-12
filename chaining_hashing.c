#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 11

typedef struct node2{ 
    int val; 
    struct node2 *next;
} NODE2;

//pole 
NODE2 *struct_arr;
int ARRAY_SIZE;

/* Pri int datasete je to jedno, staci ulozit na value index */
int generate_hash(int value, int size_of_arr){
    return (value % size_of_arr);
}


int find_the_nearest_left_prime_num(int arr[]){
    int arr_length = (int)( sizeof(arr) / sizeof(arr[0]));
    int max;

    for (int i = 2; i <= arr_length; i++){
        if(arr[i] == 1)
            max = arr[i];
    }

    return max;
}

int eratosten(int size_of_array){
    int i, j;
    int arr[size_of_array+1];

    // zaplni pole 1
    memset(arr, 1, size_of_array);
    for (i = 0; i <= size_of_array; i++)
        arr[i] = 1;

    i = 0;

    for (i = 2; i <= sqrt(size_of_array); i++){
        if(arr[i] == 1){
            for (j = i * i; j <= size_of_array; j++)
                arr[i] = 0;
        }
    }

    return find_the_nearest_left_prime_num(arr);
}


void insert_chaining_hash(NODE2 *arr[], int value){
    static int num_of_nodes_in_arr = 0;
    int hash, nearest_prime_num;
    NODE2 *previous_node;

    hash = generate_hash(value, ARRAY_SIZE);

    if(arr[hash]== NULL){
        arr[hash]->val = value;
        arr[hash]->next = NULL;
    } else {
        previous_node = arr[hash];
        while(previous_node->next != NULL){
            previous_node = previous_node->next;
        }
        previous_node->next->val = value;
        previous_node->next->next = NULL;
    }

    num_of_nodes_in_arr++;
}


NODE2 *arr_init(){
    return (NODE2 *)malloc(ARRAY_SIZE * sizeof (NODE2));
}


void re_indexing_sizing(NODE2 *arr[]){
    int old_arr_size = ARRAY_SIZE/3;
    NODE2 *new_node_arr = arr_init();
    NODE2 *current, *current2;
    int new_hash;

    for(int i = 0; i <= old_arr_size; i++){
        if(arr[i] != NULL && arr[i]->next != NULL){
            current = arr[i];

            while(current->next != NULL){
                new_hash = generate_hash(current->val, ARRAY_SIZE);
                current2 = new_node_arr[new_hash];

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
        else if(arr[i] != NULL && arr[i]->next == NULL){

            /* pre indexing - skontrul aj kyblik */
            new_hash = generate_hash(arr[i]->val, ARRAY_SIZE);
            current = new_node_arr[new_hash];

            if(current == NULL){
                current = arr[i];
            }
            else{
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = arr[i];
            }
        }
    }

    free(struct_arr);
    struct_arr = new_node_arr;

    // TODO - aktualizuj nodik ako new node arr
}


int main(int n, int arr[]){
    ARRAY_SIZE = eratosten(n);
    struct_arr = arr_init();

    for(int i = 0; i < n; i ++){
        insert_chaining_hash(struct_arr, arr[i]);
        if(i > ARRAY_SIZE/2){
            ARRAY_SIZE = eratosten(3*n);
            re_indexing_sizing(struct_arr);
        }
    }
}