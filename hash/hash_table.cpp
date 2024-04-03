#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash_table.h"

List* LST_Create() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL; // Memory allocation failed
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
        free(current->value); // Assuming data is dynamically allocated
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
            // Элемент уже присутствует в списке
            return true;
        }
        current = current->next;
    }
    // Элемент не найден
    return false;
}

void LST_add(struct List* list, value_type value) {
    assert(list);
    // Створюємо новий вузол
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL; // Новий вузол стає останнім, тому наступний буде NULL

    if (list->fixedElement == NULL) {
        // Якщо список порожній, новий елемент стає першим
        list->fixedElement = new_node;
    } else {
        // Якщо список не порожній, додаємо новий елемент в кінець
        Node* current = list->fixedElement;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
    list->length++;
}

// Добавление элемента в хэш-таблицу
void add(char* key, struct HashTable* ht) {
    // Проверка наличия элемента
    if (is_element_present(key, ht)) {
        return;
    }

    // Вычисление хэша и добавление элемента в список
    key_type hash = ht->hash_function(key) % ht->length;
    LST_add(&ht->array[hash], key);
}
