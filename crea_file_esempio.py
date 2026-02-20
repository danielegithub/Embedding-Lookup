import struct

# Vocabolario di esempio
vocab = ["Re", "Regina", "Uomo", "Donna", "Mela"]

# Vettori di embedding di esempio (DIM = 3, in base a embedding.h)
# Dimensioni immaginate: [Umanità, Regalità, Frutto]
embeddings = [
    [1.0, 1.0, 0.0],  # Re
    [1.0, 1.0, 0.0],  # Regina
    [1.0, 0.0, 0.0],  # Uomo
    [1.0, 0.0, 0.0],  # Donna
    [0.0, 0.0, 1.0],  # Mela
]

# 1. Crea il file vocab.txt
with open("vocab.txt", "w") as f:
    for word in vocab:
        f.write(f"{word}\n")

print("Creato vocab.txt con successo.")

# 2. Crea il file embedding.bin
with open("embedding.bin", "wb") as f:
    for vector in embeddings:
        for val in vector:
            # Scrive i float a 32-bit ('f') in little-endian ('<')
            f.write(struct.pack('<f', val))

print("Creato embedding.bin con successo.")
