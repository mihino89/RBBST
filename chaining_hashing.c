#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 11
#define ARRAY_BEGIN_SIZE 100

struct node2{ 
    int val; 
    struct node2 *next;
};
struct node2 *nodik[ARRAY_BEGIN_SIZE];
int ARRAY_SIZE = ARRAY_BEGIN_SIZE;


struct node2 *createNode(int val){
    struct node2  *node = (struct node2  *)malloc(sizeof(struct node2 ));

    node->next = NULL;
    node->val = val;

    return node;
}


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


void re_indexing_sizing(int new_arr_size, int akt_arr_size){
    struct node2 *new_node_arr[new_arr_size];
    int new_hash;

    for(int i = 0; i <= akt_arr_size; i++){
        if(nodik[i] != NULL){
            /* pre indexing */
            new_hash = generate_hash(nodik[i]->val, new_arr_size);
            new_node_arr[new_hash] = nodik[i];
        }
    }

    // TODO - aktualizuj nodik ako new node arr
}


void insert_chaining_hash(int value){
    static int num_of_nodes_in_arr = 0;
    int hash, nearest_prime_num;
    struct node2 *new_node, *previous_node;

    num_of_nodes_in_arr++;

    /* resing and implicated reindexing */
    if(num_of_nodes_in_arr > (ARRAY_SIZE / 2)){
        nearest_prime_num = eratosten(ARRAY_SIZE);
        re_indexing_sizing(nearest_prime_num, num_of_nodes_in_arr);
    }

    hash = generate_hash(value, ARRAY_SIZE);
    new_node = createNode(value);

    if(nodik[hash] != NULL){
        nodik[hash] = createNode(value);
    } else {
        previous_node = nodik[hash];
        while(previous_node->next != NULL){
            previous_node = previous_node->next;
        }
        previous_node->next = new_node;
    }
}