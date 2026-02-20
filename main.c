/*
 * Esempio di Embedding Lookup in C
 *
 * Questo programma spiega passo-passo (con esempi semplici) come:
 * 1) caricare un vocabolario da file (una parola per riga),
 * 2) caricare una matrice di embedding da file binario,
 * 3) cercare una parola e stampare il suo vettore di embedding.
 *
 * File esterni utilizzati:
 * - vocab_loader.c/h : funzioni per caricare vocab e pesi
 * - tokenization.c/h  : (opzionale) funzioni di tokenizzazione
 * - embedding.c/h     : lookup dell'embedding
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenization.h"
#include "embedding.h"
#include "vocab_loader.h"

int main(void) {
    /*
     * 1) Caricamento del vocabolario
     *    Immagina: `vocab.txt` è una lista, una parola per riga,
     *    come una lista della spesa. Ogni parola avrà un indice (ID).
     */
    VocabEntry vocab[MAX_VOCAB];
    int vocab_size;
    float *W_E;
    char input[64];
    int id;
    int i;
    float vettore_risultato[DIM];

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
     * 3) Ricerca di una parola (esempio semplice)
     *    Qui usiamo "Regina" come parola di esempio.
     *    Spiegazione per un ragazzino:
     *      - Cerchiamo la parola nella lista (vocab). Se la troviamo, sappiamo
     *        qual è il suo numero (ID). Poi prendiamo i numeri corrispondenti
     *        dall'enorme lista `embedding.bin` e li stampiamo.
     */
    strcpy(input, "Regina");

    /* Cerca lineare nel vocabolario (semplice da capire) */
    id = -1;
    i = 0;
    while (i < vocab_size) {
        if (strcmp(vocab[i].parola, input) == 0) {
            id = i; /* trovato: l'ID è la posizione nella lista */
            break;
        }
        i++;
    }

    if (id != -1) {
        /* Se troviamo l'ID, usiamo il lookup per ottenere il vettore */
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
        printf("Parola sconosciuta.\n");
    }

    /* Pulisce la memoria */
    free(W_E);
    return 0;
}
