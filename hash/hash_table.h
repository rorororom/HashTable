#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdlib.h>
#include "../list/list.h"

const size_t HT_TABLE_SIZE        = 4001;
const size_t HT_TABLE_SIZE_SMALL  = 503;
const int    START_CAPACITY       = 100;
typedef size_t key_type;
typedef char* value_type;

struct HashTable {
    size_t   length;
    List*    array;
    key_type (*hash_function)    (value_type value);
};

List* LST_Create();
struct HashTable* HT_Create(key_type (*hash_function)(value_type value));
void increase_capacity(List* list);
void LST_add(struct List* list, value_type value);
void add(char* key, struct HashTable* ht);

#endif
