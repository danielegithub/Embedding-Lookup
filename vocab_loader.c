#include "vocab_loader.h"
#include <stdio.h>
#include <stdlib.h>

int carica_vocabolario(VocabEntry* vocab, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    int i = 0;
    while (fscanf(f, "%63s", vocab[i].parola) != EOF && i < MAX_VOCAB) {
        i++;
    }
    fclose(f);
    return i;
}

float* carica_pesi(const char* filename, int vocab_size, int dim) {
    float* matrix = malloc(vocab_size * dim * sizeof(float));
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;
    fread(matrix, sizeof(float), vocab_size * dim, f);
    fclose(f);
    return matrix;
}
