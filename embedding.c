#include "embedding.h"

void lookup_embedding(float* matrix, int token_id, float* output_vector) {
    int start_index = token_id * DIM;
    int j;
    for (j = 0; j < DIM; j++) {
        output_vector[j] = matrix[start_index + j];
    }
}
