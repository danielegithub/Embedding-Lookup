# Embedding Lookup

Questo progetto mostra un esempio semplice di tokenizzazione e lookup di embedding in C.

## Struttura del progetto

- **main.c**: contiene solo la funzione `main`, che utilizza le librerie esterne per la tokenizzazione e l'embedding.
- **tokenization.h/c**: libreria per la gestione del vocabolario e la tokenizzazione (conversione parola → ID).
- **embedding.h/c**: libreria per il lookup dell'embedding (conversione ID → vettore di caratteristiche).

## Come funziona

1. **Tokenizzazione**: una parola viene convertita in un ID numerico tramite la funzione `get_id`.
2. **Embedding Lookup**: dato l'ID, la funzione `lookup_embedding` restituisce il vettore di caratteristiche associato.

## Compilazione

Per compilare il progetto, usa il seguente comando nel terminale:

```
gcc main.c tokenization.c embedding.c -o embedding_lookup
```

Questo produrrà un eseguibile chiamato `embedding_lookup`.

## Esecuzione

Esegui il programma con:

```
./embedding_lookup
```

## Esempio di output

```
La parola 'Regina' (ID: 1) ha queste caratteristiche:
[Umano: 0.90, Regale: 0.95, Frutto: 0.00]
```

## Note
- Puoi modificare il vocabolario e la matrice di embedding direttamente in `main.c`.
- Le librerie sono modulari e riutilizzabili in altri progetti.
