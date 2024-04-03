#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "./hash/hash_table.h"
#include "./hash/hash_func.h"
#include "list.h"
#include "log.h"
#include "./text_tools/read_file_in_buffer.h"

void writeToFile(const char* filename, struct HashTable* ht) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    int max = 0;
    int max_i = 0;
    for (size_t i = 0; i < ht->length; i++) {
        if (max < ht->array[i].length) {
            max = ht->array[i].length;
            max_i = i;
        }
        fprintf(file, "%zu %d\n", i, ht->array[i].length);
    }

    printf("%d %d\n", max, max_i);
    fclose(file);
}

int main()
{
    OpenLogFile("LOGE1111.html", "w");
    List list = {};
    CtorList(&list);

    struct BufferForFile source = {"./text_tools/ans.txt",
                                    NULL,
                                    NULL,
                                    0,
                                    0};
    MainFuncReadFile(&source);

    struct HashTable* ht = HT_Create(reinterpret_cast<key_type (*)(value_type)>(hash_func1));

    for (size_t i = 0; i < source.words; i++) {
        add(source.textArray[i], ht);
    }

    writeToFile("output1.txt", ht);

    return 0;
}
