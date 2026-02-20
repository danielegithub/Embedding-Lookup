#include "tokenization.h"
#include <string.h>
#include "tokenization.h"
#include <string.h>

int get_id(Vocabolario voc[], int size, char* parola) {
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(voc[i].parola, parola) == 0) return voc[i].id;
    }
    return -1;
}
