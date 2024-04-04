#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash_table.h"

List* LST_Create() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->fixedElement = NULL;
    list->length = 0;
    list->capacity = START_CAPACITY;

    return list;
}

HashTable* HT_Create(key_type (*hash_function)(value_type value)) {
    HashTable* ht         = (HashTable*)calloc(1, sizeof(HashTable));
    ht->length            = HT_TABLE_SIZE;
    ht->hash_function     = hash_function;
    ht->array = (List*)calloc(ht->length, sizeof(List));
    for (size_t i = 0; i < ht->length; ++i) {
        ht->array[i] = *LST_Create();
    }
    return ht;
}

void LST_Destroy(List* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->fixedElement;
    while (current != NULL) {
        Node* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    free(list);
}


void HT_Destroy(HashTable* table) {
    for (size_t i = 0; i < table->length; i++) {
        List* current = &table->array[i];

        while (current != NULL) {
            LST_Destroy(current);
        }

    }
    free(table->array);
    free(table);
}

bool is_element_present(char* key, struct HashTable* ht) {
    key_type hash = ht->hash_function(key) % ht->length;
    struct List* list = &ht->array[hash];
    Node* current = list->fixedElement;
    while (current != NULL) {
        if (strcmp(current->value, key) == 0) {
            return true;                            // Элемент уже присутствует в списке
        }
        current = current->next;
    }
    return false;                                   // Элемент не найден
}

void LST_add(struct List* list, value_type value) {
    assert(list);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    if (list->fixedElement == NULL) {
        list->fixedElement = new_node;
    } else {
        Node* current = list->fixedElement;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
    list->length++;
}

void add(char* key, struct HashTable* ht) {
    if (is_element_present(key, ht)) {                      // Проверка наличия элемента
        return;
    }

    key_type hash = ht->hash_function(key) % ht->length;
    LST_add(&ht->array[hash], key);
}
