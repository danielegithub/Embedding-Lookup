#ifndef TOKENIZATION_H
#define TOKENIZATION_H

typedef struct {
    int id;
    char parola[20];
} Vocabolario;

int get_id(Vocabolario voc[], int size, const char* parola);

#endif // TOKENIZATION_H
