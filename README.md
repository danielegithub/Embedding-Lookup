# Embedding Lookup

Questo progetto mostra un esempio semplice e completo di **tokenizzazione** e **lookup di embedding** in C, con dati reali letti da file.

## Pipeline

```
vocab.txt  ──>  [parola, ID]          ──>  main.c
                       │
embedding.bin ──>  matrice (vocab_size x DIM)
                       │
              get_id(parola)  →  ID           (tokenization.c)
                       │
              lookup_embedding(ID)  →  vettore (embedding.c)
```

1. **Tokenizzazione**: una parola viene convertita in un ID numerico con `get_id()` (la sua posizione nel vocabolario).
2. **Embedding lookup**: dato l'ID, `lookup_embedding()` restituisce il vettore di `DIM` numeri associato alla parola.

## Struttura del progetto

- **main.c**: la `main`. Carica i dati, converte parola → ID, fa il lookup e stampa il vettore.
- **tokenization.h/c**: libreria con la struttura `Vocabolario {id, parola}` e `get_id()` (parola → ID).
- **embedding.h/c**: `lookup_embedding()` (ID → vettore) e la costante `DIM` (`DIM = 3`).
- **vocab_loader.h/c**: `carica_vocabolario()` legge `vocab.txt`, `carica_pesi()` legge `embedding.bin` (con verifica che il file contenga esattamente `vocab_size * DIM` float).
- **crea_file_esempio.py**: script Python che genera i file di esempio `vocab.txt` e `embedding.bin`.
- **vocab.txt** / **embedding.bin**: i dati (5 parole, vettori a 3 dimensioni: [Umanità, Regalità, Frutto]).

## Come rigenerare i dati di esempio (facoltativo)

```
python3 crea_file_esempio.py
```

Crea `vocab.txt` (una parola per riga) e `embedding.bin` (float32 little-endian, `vocab_size * DIM` valori).

## Compilazione

```
gcc main.c tokenization.c embedding.c vocab_loader.c -o embedding_lookup
```

> Suggerimento: usa `gcc -Wall -Wextra ... -o embedding_lookup` per vedere gli avvisi.

## Esecuzione

```
./embedding_lookup            # cerca la parola di default: 'Regina'
./embedding_lookup Mela       # cerca la parola data come argomento
```

## Esempio di output

```
$ ./embedding_lookup Regina
La parola 'Regina' (ID: 1) ha queste caratteristiche:
[1.00, 1.00, 0.00]

$ ./embedding_lookup NonEsistente
Parola sconosciuta: 'NonEsistente'. Prova uno di questi: Re, Regina, Uomo, Donna, Mela
```

## Note

- Le librerie (`tokenization`, `embedding`, `vocab_loader`) sono modulari e riutilizzabili in altri progetti.
- I vettori di esempio hanno senso solo come demo: in un modello reale `DIM` sarebbe 300+ e la matrice verrebbe appresa dai dati, non scritta a mano.
- `embedding.bin` è letto come float32 little-endian: funziona così come generato da `crea_file_esempio.py` su Mac/ARM e su x86 Linux.
