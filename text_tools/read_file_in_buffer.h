#ifndef ONEGIN
#define ONEGIN
#include <stdlib.h>

#define LEN 256

const int MAXLEN = 256;

struct BufferForFile {
    char file[MAXLEN];
    char *buffer;
    char **textArray;
    int words;
    int size;
};

int MainFuncReadFile(struct BufferForFile *source);
void ReadFileInBuffer(FILE *fp, struct BufferForFile *source);
int GetFileSize(struct BufferForFile *source);
void word_count(struct BufferForFile *source);
void fill_text_and_count_word(struct BufferForFile *source);

#endif
