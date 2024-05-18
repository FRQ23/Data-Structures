#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"
#include "hash.h"

void showMenu() {
    printf("[0] MOSTRAR HASH ID\n");
    printf("[1] MOSTRAR HASH NOMBRE\n");
    printf("[2] BUSCAR PELÍCULA ID\n");
    printf("[3] BUSCAR PELÍCULA NOMBRE\n");
    printf("[4] AGREGAR PELÍCULA\n");
    printf("[5] ELIMINAR PELÍCULA\n");
    printf("[6] TERMINAR PROGRAMA\n");
    printf("Seleccione una opción: ");
}

void freeHashTable(HashTable *hashTable) {
    if (hashTable) {
        free(hashTable->table);
        free(hashTable);
    }
}

int main(void) {
    int i, choice, id, year, rating;
    char name[100];
    HashTable *hashByID, *hashByName;
    Movie **movies = NULL;
    Movie *data = NULL;

    movies = create_movies();

    // Crear las tablas hash
    int maxID = SIZE_DATA;
    hashByID = createHashTable(maxID, NULL);
    hashByName = createHashTable(SIZE_DATA * 4, foldingFunction);

    // Insertar películas en las tablas hash
    for (i = 0; i < SIZE_DATA; i++) {
        data = getMovie(movies, i);
        if (data) {
            insertMovie(hashByID, data);
            insertMovie(hashByName, data);
        }
    }

    // Menú de opciones
    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printHashTable(hashByID);
                break;
            case 1:
                printHashTable(hashByName);
                break;
            case 2:
                printf("Ingrese el ID de la película: ");
                scanf("%d", &id);
                data = searchMovieByID(hashByID, id);
                if (data) {
                    printMovie(data);
                } else {
                    printf("Película no encontrada.\n");
                }
                break;
            case 3:
                printf("Ingrese el nombre de la película: ");
                scanf(" %[^\n]s", name);
                data = searchMovieByName(hashByName, name);
                if (data) {
                    printMovie(data);
                } else {
                    printf("Película no encontrada.\n");
                }
                break;
            case 4:
                printf("Ingrese el nombre de la película: ");
                scanf(" %[^\n]s", name);
                printf("Ingrese el año de la película: ");
                scanf("%d", &year);
                printf("Ingrese la calificación de la película: ");
                scanf("%d", &rating);
                data = (Movie *)malloc(sizeof(Movie));
                data->id = ++maxID;  // Generar un nuevo ID automáticamente
                data->name = strdup(name);
                data->release_date = year;
                data->rating = rating;
                insertMovie(hashByID, data);
                insertMovie(hashByName, data);
                break;
            case 5:
                printf("Eliminar por [0] ID o [1] Nombre: ");
                int delChoice;
                scanf("%d", &delChoice);
                if (delChoice == 0) {
                    printf("Ingrese el ID de la película: ");
                    scanf("%d", &id);
                    data = searchMovieByID(hashByID, id);
                    if (data) {
                        deleteMovieByID(hashByID, id);
                        deleteMovieByName(hashByName, data->name);
                    } else {
                        printf("Película no encontrada.\n");
                    }
                } else if (delChoice == 1) {
                    printf("Ingrese el nombre de la película: ");
                    scanf(" %[^\n]s", name);
                    data = searchMovieByName(hashByName, name);
                    if (data) {
                        deleteMovieByName(hashByName, name);
                        deleteMovieByID(hashByID, data->id);
                    } else {
                        printf("Película no encontrada.\n");
                    }
                }
                break;
            case 6:
                printf("Terminando programa...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (choice != 6);

    // Liberar memoria
    for (i = 0; i < SIZE_DATA; i++) {
        data = getMovie(movies, i);
        if (data) {
            free(data->name);
            free(data);
            movies[i] = NULL;
        }
    }
    free(movies);

    freeHashTable(hashByID);
    freeHashTable(hashByName);

    return 0;
}
