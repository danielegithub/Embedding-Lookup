#ifndef VOCAB_LOADER_H
#define VOCAB_LOADER_H

#include <stdio.h>

#define MAX_VOCAB 50000

typedef struct {
    char parola[64];
} VocabEntry;

int carica_vocabolario(VocabEntry* vocab, const char* filename);
float* carica_pesi(const char* filename, int vocab_size, int dim);

#endif // VOCAB_LOADER_H
