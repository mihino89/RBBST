// Zdroj: https://enthusiaststudent.blogspot.com/2017/03/hashing-using-linear-probing-c-program.html 
#include <stdio.h>
#include <stdlib.h>

/* to store a data (consisting of key and value) in hash table array */
typedef struct item{
    int key;
    int value;
}ITEM;

/* each hash table item has a flag (status) and data (consisting of key and value) */
typedef struct hashtable_item{
    int flag;
    /*
        * flag = 0 : data does not exist
        * flag = 1 : data exists
        * flag = 2 : data existed at least once
    */
    ITEM *data;
}HASH_TABLE_ITEM;

HASH_TABLE_ITEM *array;
int size = 0;
int max2 = 10;

/* initializing hash table array */
void init_array(){
    int i;

    for (i = 0; i < max2; i++){
        array[i].flag = 0;
        array[i].data = NULL;
    }
}

/* to every key, it will generate a corresponding index */
int hashcode(int key){
    return (key % max2);
}

/* to insert an element in the hash table */
void insert(int key){
    int index = hashcode(key);
    int i = index;

    /* creating new item to insert in the hash table array */
    ITEM *new_item = (ITEM *)malloc(sizeof(ITEM));
    new_item->key = key;

    /* probing through the array until we reach an empty space */
    while (array[i].flag == 1){

        if (array[i].data->key == key){
            return;
        }
        i = (i + 1) % max2;

        if (i == index){
            return;
        }
    }

    array[i].flag = 1;
    array[i].data = new_item;
    size++;
}

int size_of_hashtable(){
    return size;
}

void main_linear_probing(int n, int *arr){
    max2 = n;

    array = (HASH_TABLE_ITEM *)malloc(max2 * sizeof(HASH_TABLE_ITEM));
    init_array();

    for(int i = 0; i < max2; i ++){
        insert(arr[i]);
    }
}