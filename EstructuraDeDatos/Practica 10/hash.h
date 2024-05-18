#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

typedef int (*FunctionFolding)(char*);

typedef struct hashtable {
    int size;          // Capacidad de la tabla
    int amount_data;   // Número de elementos en la tabla
    Movie **table;     // Almacenamiento de las películas
    FunctionFolding folding; // Función de plegado para el hash basado en el nombre
} HashTable;

// Prototipos de funciones
HashTable* createHashTable(int size, FunctionFolding folding);
void insertMovie(HashTable *hashTable, Movie *movie);
void deleteMovieByID(HashTable *hashTable, int id);
void deleteMovieByName(HashTable *hashTable, char *name);
Movie* searchMovieByID(HashTable *hashTable, int id);
Movie* searchMovieByName(HashTable *hashTable, char *name);
void printHashTable(HashTable *hashTable);
int foldingFunction(char *name);
void remapTable(HashTable *hashTable);

#endif // HASH_H
