/*
 * Esempio di Embedding Lookup in C
 *
 * Questo programma spiega passo-passo (con esempi semplici) come:
 * 1) caricare un vocabolario da file (una parola per riga),
 * 2) caricare una matrice di embedding da file binario,
 * 3) cercare una parola e stampare il suo vettore di embedding.
 *
 * Uso:
 *   ./embedding_lookup            -> cerca la parola di default (Regina)
 *   ./embedding_lookup Mela       -> cerca la parola data come argomento
 *
 * File esterni utilizzati:
 * - vocab_loader.c/h : carica il vocabolario (vocab.txt) e i pesi (embedding.bin)
 * - tokenization.c/h : conversione parola -> ID (get_id)
 * - embedding.c/h    : conversione ID -> vettore (lookup_embedding)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenization.h"
#include "embedding.h"
#include "vocab_loader.h"

int main(int argc, char* argv[]) {
    /*
     * La parola da cercare: argv[1] se fornita, altrimenti la parola di esempio.
     */
    const char* input = (argc > 1) ? argv[1] : "Regina";

    VocabEntry vocab[MAX_VOCAB];
    int vocab_size;
    float* W_E;
    int i;
    int id;
    float vettore_risultato[DIM];

    /*
     * 1) Caricamento del vocabolario
     *    Immagina: `vocab.txt` è una lista, una parola per riga,
     *    come una lista della spesa. Ogni parola avrà un indice (ID).
     */
    vocab_size = carica_vocabolario(vocab, "vocab.txt");
    if (vocab_size == 0) {
        /* Se non riesce a leggere il file, informiamo l'utente */
        printf("Errore nel caricamento del vocabolario. Controlla vocab.txt\n");
        return 1;
    }

    /*
     * 2) Caricamento della matrice di embedding
     *    Immagina: `embedding.bin` contiene tanti numeri in fila.
     *    Ogni parola ha `DIM` numeri (il suo vettore).
     */
    W_E = carica_pesi("embedding.bin", vocab_size, DIM);
    if (!W_E) {
        printf("Errore nel caricamento della matrice di embedding. Controlla embedding.bin\n");
        return 1;
    }

    /*
     * 3) Tokenizzazione: parola -> ID
     *    Trasferisci le parole caricate dalla libreria di tokenizzazione
     *    e usa get_id() per trovare il numero che identifica la parola.
     *    L'ID corrisponde alla posizione della parola nel vocabolario:
     *    la prima parola di vocab.txt ha ID 0, la seconda ID 1, e così via.
     */
    Vocabolario* voc = (Vocabolario*)malloc((size_t)vocab_size * sizeof(Vocabolario));
    if (!voc) {
        free(W_E);
        printf("Errore di memoria.\n");
        return 1;
    }
    i = 0;
    while (i < vocab_size) {
        /* parola[19] in Vocabolario + terminatore: taglia i nomi troppo lunghi */
        strncpy(voc[i].parola, vocab[i].parola, sizeof(voc[i].parola) - 1);
        voc[i].parola[sizeof(voc[i].parola) - 1] = '\0';
        voc[i].id = i;
        i++;
    }

    id = get_id(voc, vocab_size, input);

    if (id != -1) {
        /* 4) Embedding lookup: ID -> vettore di caratteristiche */
        lookup_embedding(W_E, id, vettore_risultato);
        printf("La parola '%s' (ID: %d) ha queste caratteristiche:\n", input, id);
        printf("[");
        i = 0;
        while (i < DIM) {
            printf("%.2f", vettore_risultato[i]);
            if (i < DIM - 1) printf(", ");
            i++;
        }
        printf("]\n");
    } else {
        /* Parola non presente nel vocabolario */
        printf("Parola sconosciuta: '%s'. Prova uno di questi: ", input);
        i = 0;
        while (i < vocab_size) {
            if (i > 0) printf(", ");
            printf("%s", vocab[i].parola);
            i++;
        }
        printf("\n");
    }

    /* Pulisce la memoria */
    free(voc);
    free(W_E);
    return 0;
}
