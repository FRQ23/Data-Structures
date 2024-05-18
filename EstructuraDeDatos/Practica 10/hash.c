#include "hash.h"

// Función de plegado (folding) basada en el nombre
int foldingFunction(char *name) {
    int hash = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        hash += name[i];
    }
    return hash;
}

// Crear una nueva tabla hash
HashTable* createHashTable(int size, FunctionFolding folding) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->amount_data = 0;
    hashTable->table = (Movie **)calloc(size, sizeof(Movie *));
    hashTable->folding = folding;
    return hashTable;
}

// Función de rehashing
void rehash(HashTable *hashTable) {
    int oldSize = hashTable->size;
    Movie **oldTable = hashTable->table;

    // Duplicar el tamaño de la tabla
    hashTable->size *= 2;
    hashTable->table = (Movie **)calloc(hashTable->size, sizeof(Movie *));
    hashTable->amount_data = 0;

    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i] != NULL) {
            insertMovie(hashTable, oldTable[i]);
        }
    }
    free(oldTable);
}

// Insertar una película en la tabla hash
void insertMovie(HashTable *hashTable, Movie *movie) {
    // Verificar si es necesario rehashear
    if (hashTable->amount_data >= hashTable->size / 2) {
        rehash(hashTable);
    }

    int index;
    if (hashTable->folding != NULL) {
        index = hashTable->folding(movie->name) % hashTable->size;
    } else {
        index = movie->id % hashTable->size;
    }
    while (hashTable->table[index] != NULL) {
        index = (index + 1) % hashTable->size;
    }
    hashTable->table[index] = movie;
    hashTable->amount_data++;
}

// Eliminar una película por ID
void deleteMovieByID(HashTable *hashTable, int id) {
    int index = id % hashTable->size;
    while (hashTable->table[index] != NULL) {
        if (hashTable->table[index]->id == id) {
            hashTable->table[index] = NULL;
            hashTable->amount_data--;
            remapTable(hashTable);
            return;
        }
        index = (index + 1) % hashTable->size;
    }
}

// Eliminar una película por nombre
void deleteMovieByName(HashTable *hashTable, char *name) {
    int index = hashTable->folding(name) % hashTable->size;
    while (hashTable->table[index] != NULL) {
        if (strcmp(hashTable->table[index]->name, name) == 0) {
            hashTable->table[index] = NULL;
            hashTable->amount_data--;
            remapTable(hashTable);
            return;
        }
        index = (index + 1) % hashTable->size;
    }
}

// Buscar una película por ID
Movie* searchMovieByID(HashTable *hashTable, int id) {
    int index = id % hashTable->size;
    while (hashTable->table[index] != NULL) {
        if (hashTable->table[index]->id == id) {
            return hashTable->table[index];
        }
        index = (index + 1) % hashTable->size;
    }
    return NULL;
}

// Buscar una película por nombre
Movie* searchMovieByName(HashTable *hashTable, char *name) {
    int index = hashTable->folding(name) % hashTable->size;
    while (hashTable->table[index] != NULL) {
        if (strcmp(hashTable->table[index]->name, name) == 0) {
            return hashTable->table[index];
        }
        index = (index + 1) % hashTable->size;
    }
    return NULL;
}

// Imprimir la tabla hash con formato legible
void printHashTable(HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            printf("%-3d | %-50s | %4d | %2d\n",
                   hashTable->table[i]->id,
                   hashTable->table[i]->name,
                   hashTable->table[i]->release_date,
                   hashTable->table[i]->rating);
        }
    }
}

// Remapear la tabla después de eliminar un elemento
void remapTable(HashTable *hashTable) {
    Movie **oldTable = hashTable->table;
    int oldSize = hashTable->size;
    hashTable->table = (Movie **)calloc(hashTable->size, sizeof(Movie *));
    hashTable->amount_data = 0;
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i] != NULL) {
            insertMovie(hashTable, oldTable[i]);
        }
    }
    free(oldTable);
}
