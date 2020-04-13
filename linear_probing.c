// https://github.com/soasme/Practise/blob/68b07fd91cd3106dd19bbc43144a5c7d95f18d2e/Algorithms/3.4/linear_probing.c?fbclid=IwAR0oIGKmSnHIvDWvq3tod9jDDNjeTyyLxsOLyWFg-kEiuDa37ka8iEy3U38

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* string;

typedef struct {
    string* keys;
    int* values;
    int size;
} LinearProbing;

LinearProbing* linear_probing_init(int size);
LinearProbing* linear_probing_resize(LinearProbing* table, int size);
int linear_probing_hash(LinearProbing* table, string key);
void linear_probing_set(LinearProbing* table, string key, int value);
int linear_probing_get(LinearProbing* table, string key);
void linear_probing_print(LinearProbing* table);
void linear_probing_free(LinearProbing* table);

int
main(int argv, char** args){
    int hello;
    int size = 30;

    LinearProbing* table = linear_probing_init(size);

    hello = linear_probing_get(table, "hello");
    printf("first get: %d\n", hello);

    linear_probing_set(table, "hello", 1);

    hello = linear_probing_get(table, "hello");
    printf("get after set: %d\n", hello);

    hello = linear_probing_get(table, "hello");
    printf("get after delete: %d\n", hello);

    // collision
    int i;
    for (i = 0; i < 11; i++) {
        string key = (string) malloc (20);
        sprintf(key, "/key/%d", i);

        linear_probing_set(table, key, i);
        int value = linear_probing_get(table, key);
        printf("get %s: %d\n", key, value);
        free(key);
    }

    linear_probing_print(table);
    linear_probing_free(table);
    return 0;
}

LinearProbing*
linear_probing_init(int size){
    LinearProbing* table = (LinearProbing*) malloc (sizeof(LinearProbing));
    table->size = size;
    table->keys = (string*) malloc(sizeof(char) * 20 * size);
    table->values = (int*) malloc(sizeof(string) * size);
    return table;
}

void
linear_probing_free(LinearProbing* table) {
    free(table->keys);
    free(table->values);
    free(table);
}

LinearProbing*
linear_probing_resize(LinearProbing* table, int size){
    LinearProbing* new_table = linear_probing_init(size);
    int i;
    for (i = 0; i < table->size; i++) {
        if (table->keys[i]) {
            int new_index = linear_probing_hash(new_table, table->keys[i]);
            new_table->keys[new_index] = table->keys[i];
            new_table->values[new_index] = table->values[i];
        }
    }
    linear_probing_free(table);
    return new_table;
}

int
linear_probing_hash(LinearProbing* table, string key){
    // ref: https://gist.github.com/soasme/6109366
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;
    for(i = 0; i < table->size; key++, i++) {
        hash = (hash << 4) + (*key);
        if((x = hash & 0xF0000000L) != 0)
        {
        hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

void
linear_probing_set(LinearProbing* table, string key, int value){
    int start = linear_probing_hash(table, key) % table->size;
    int index = start;
    while (1) {
        if (!table->keys[index]) {
            table->keys[index] = key;
            table->values[index] = value;
            return;
        }

        if (strcmp(table->keys[index], key) == 0) {
            table->values[index] = value;
            return;
        }

        index = (index + 1) % table->size;
        if (index == start) {
            break;
        }
    }
}

int
linear_probing_get(LinearProbing* table, string key){
    int start = linear_probing_hash(table, key) % table->size;
    int index = start;
    while (1) {
        if (!table->keys[index]) {
            return 0;
        }

        if (strcmp(key, table->keys[index]) == 0) {
            return table->values[index];
        }

        index = (index + 1) % table->size;
        if (index == start) {
            break;
        }
    }
    return 0;
}


void
linear_probing_print(LinearProbing* table) {
    int i;
    printf("[table begin]\n");
    for (i = 0; i < table->size; i++) {
        if (table->keys[i] && table->values[i]) {
            printf("[table] [index %d] %s: %d\n", i, table->keys[i], table->values[i]);
        }
    }
    printf("[table end]\n");
}