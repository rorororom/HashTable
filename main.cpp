#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "./hash/hash_table.h"
#include "./hash/hash_func.h"
#include "./list/list.h"
#include "./list/log.h"
#include "./text_tools/read_file_in_buffer.h"

void writeToFileResult(const char* filename, struct HashTable* ht) {
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

void dispersion(struct HashTable* ht) {
    int sum_elememt = 0;
    for (size_t i = 0; i < ht->length; i++) {
        sum_elememt += ht->array[i].length;
    }

    printf("sum = %d\n", sum_elememt);
    printf("len = %d\n", ht->length);
    float average = sum_elememt / (float)ht->length;
    printf("average = %f\n", average);

    float average_disp = 0;
    for (size_t i = 0; i < ht->length; i++) {
        average_disp += pow(((float)ht->array[i].length - average), 2);
        if (i == 1) {
            printf("%d\n", average_disp);
        }
    }

    printf("dispersion = %f\n", average_disp / (float)ht->length);
}

int main()
{
    OpenLogFile("LOGE", "w");
    List list = {};
    CtorList(&list);

    struct BufferForFile source = {"./text_tools/ans.txt",
                                    NULL,
                                    NULL,
                                    0,
                                    0};
    MainFuncReadFile(&source);

    struct HashTable* ht = HT_Create(reinterpret_cast<key_type (*)(value_type)>(hash_func4_2));

    for (size_t i = 0; i < source.words; i++) {
        add(source.textArray[i], ht);
    }

    writeToFileResult("./result/output4(2).txt", ht);
    dispersion(ht);

    int sum = 0;
    for (size_t i = 0; i < ht->length; i++) {
        sum += ht->array[i].length;
    }

    printf("load = %f\n", sum / (float)ht->length);

    return 0;
}
