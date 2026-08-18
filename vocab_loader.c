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
    float* matrix = malloc((size_t)vocab_size * dim * sizeof(float));
    if (!matrix) return NULL;
    FILE* f = fopen(filename, "rb");
    if (!f) {
        free(matrix);
        return NULL;
    }
    size_t attesi = (size_t)vocab_size * dim;
    size_t letti = fread(matrix, sizeof(float), attesi, f);
    fclose(f);
    if (letti != attesi) {
        /* File troncato o con dimensioni incoerenti: non usare dati parziali */
        free(matrix);
        return NULL;
    }
    return matrix;
}
