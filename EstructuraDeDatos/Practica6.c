#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NodoPila {
    void* datos;
    struct NodoPila* siguiente;
} NodoPila;

typedef struct {
    struct NodoPila* tope;
    size_t longitud;
    size_t capacidad;

    bool deberia_liberar_direccion_datos_nodo;
} Pila;

typedef struct {
    char title[64];
    char genre[32];
    unsigned int year;
} Libro;

typedef struct NodoArbol {
    Pila* pila;
    struct NodoArbol* izquierdo;
    struct NodoArbol* derecho;
} NodoArbol;

Pila* pila_nueva(size_t capacidad);

NodoPila* nodo_pila_nuevo(void* datos);

void* pila_push(Pila* pila, void* datos);

void* pila_pop(Pila* pila);

void nodo_pila_liberar(NodoPila* nodo);

void pila_liberar(Pila* pila);

void pila_imprimir_horizontal(Pila* pila, void imprimir_datos(void*));

void pila_imprimir_vertical(Pila* pila, void imprimir_datos(void*));




Pila* pila_nueva(size_t capacidad) {
    Pila* pila = (Pila*)calloc(1, sizeof(Pila));

    pila->deberia_liberar_direccion_datos_nodo = true;
    pila->capacidad = capacidad;

    return pila;
}

NodoPila* nodo_pila_nuevo(void* datos) {
    NodoPila* nodo = (NodoPila*)calloc(1, sizeof(NodoPila));

    nodo->datos = datos;

    return nodo;
}

void nodo_pila_liberar(NodoPila* nodo) {
    free(nodo->datos);
    free(nodo);
}

void* pila_pop(Pila* pila);
void* pila_semi_pop(Pila* pila);
void pila_liberar(Pila* pila) {
    while (pila->tope) {
        if (pila->deberia_liberar_direccion_datos_nodo) {
            pila_pop(pila);
        } else {
            pila_semi_pop(pila);
        }
    }
    free(pila);
}

void* pila_push(Pila* pila, void* datos) {
    size_t siguiente_longitud = pila->longitud + 1;

    if (siguiente_longitud > pila->capacidad) {
        return NULL;
    }

    NodoPila* nodo = nodo_pila_nuevo(datos);

    nodo->siguiente = pila->tope;
    pila->tope = nodo;

    pila->longitud += 1;

    return pila->tope;
}

void* pila_pop(Pila* pila) {
    if (pila == NULL || pila->longitud < 1 || pila->tope == NULL) {
        return NULL;
    }

    NodoPila* anterior_tope = pila->tope;
    pila->tope = anterior_tope->siguiente;

    if (pila->deberia_liberar_direccion_datos_nodo) {
        nodo_pila_liberar(anterior_tope);
    } else {
        free(anterior_tope);
    }

    pila->longitud -= 1;

    if (pila->tope == NULL) {
        return NULL;
    }

    return pila->tope->datos;
}

/** Solo libera el nodo */
void* pila_semi_pop(Pila* pila) {
    NodoPila* anterior_tope = pila->tope;
    pila->tope = pila->tope->siguiente;

    free(anterior_tope);

    pila->longitud -= 1;

    if (pila->tope == NULL) {
        return NULL;
    }

    return pila->tope->datos;
}

void pila_imprimir_horizontal(Pila* pila, void imprimir_datos(void*)) {
    if (pila == NULL) {
        printf("NULL\n");
        return;
    }

    Pila* holder = pila_nueva(pila->capacidad);
    holder->deberia_liberar_direccion_datos_nodo = pila->deberia_liberar_direccion_datos_nodo;

    printf("[ ");

    while (pila->tope) {
        imprimir_datos(pila->tope->datos);

        pila_push(holder, pila->tope->datos);
        pila_semi_pop(pila);

        if (pila->tope) {
            printf(" | ");
        }
    }

    printf(" ]\n");

    while (holder->tope) {
        pila_push(pila, holder->tope->datos);
        pila_semi_pop(holder);
    }
    pila_liberar(holder);
}

void pila_imprimir_vertical(Pila* pila, void imprimir_datos(void*)) {
    if (pila == NULL) {
        printf("|\tNULL\t|\n");
        return;
    }

    if (pila->tope == NULL && pila->longitud == 0) {
        printf("[\t\t]\n");
    }

    Pila* holder = pila_nueva(pila->capacidad);
    holder->deberia_liberar_direccion_datos_nodo = pila->deberia_liberar_direccion_datos_nodo;

    while (pila->tope) {
        printf("[\t");

        imprimir_datos(pila->tope->datos);

        printf("\t]\n");

        pila_push(holder, pila->tope->datos);

        pila_semi_pop(pila);
    }

    while (holder->tope) {
        pila_push(pila, holder->tope->datos);
        pila_semi_pop(holder);
    }

    pila_liberar(holder);
}

NodoArbol* nodo_arbol_nuevo(Pila* pila) {
    NodoArbol* nodo = (NodoArbol*)calloc(1, sizeof(NodoArbol));
    nodo->pila = pila;
    return nodo;
}

void nodo_arbol_insertar(NodoArbol** raiz, Pila* pila, int (*comparar)(Pila*, Pila*)) {
    if (*raiz == NULL) {
        *raiz = nodo_arbol_nuevo(pila);
    } else if (comparar(pila, (*raiz)->pila) < 0) {
        nodo_arbol_insertar(&(*raiz)->izquierdo, pila, comparar);
    } else {
        nodo_arbol_insertar(&(*raiz)->derecho, pila, comparar);
    }
}

void nodo_arbol_a_pilas(NodoArbol* raiz, Pila*** pilas, size_t* longitud_pilas) {
    if (raiz == NULL) {
        return;
    }

    nodo_arbol_a_pilas(raiz->izquierdo, pilas, longitud_pilas);

    if (*pilas == NULL) {
        *pilas = calloc(1, sizeof(Pila*));
    } else {
        *pilas = realloc(*pilas, (*longitud_pilas + 1) * sizeof(Pila*));
    }
    // Crear una copia de la pila
    Pila* pila_copia = pila_nueva(raiz->pila->capacidad);
    pila_copia->deberia_liberar_direccion_datos_nodo = raiz->pila->deberia_liberar_direccion_datos_nodo;
    NodoPila* nodo = raiz->pila->tope;
    while (nodo) {
        pila_push(pila_copia, nodo->datos);
        nodo = nodo->siguiente;
    }
    (*pilas)[*longitud_pilas] = pila_copia;
    (*longitud_pilas)++;

    nodo_arbol_a_pilas(raiz->derecho, pilas, longitud_pilas);
}







Libro LIBROS[] = {
        {"Cell", "Horror", 2006},
        {"The Street Lawyer", "Thriller", 1998},
        {"Nineteen Minutes", "Thriller", 2007},
        {"Harry Potter y la piedra filosofal", "Fantasy", 1997},
        {"Armageddon", "Post-apocalyptic fiction", 2003},
        {"The Jester", "Historical fiction", 2003},
        {"Harry Potter y el prisionero de Azkaban", "Fantasy", 1999},
        {"Star Wars: Episode I The Phantom Menace", "Science fiction", 1999},
        {"Dreamcatcher", "Fantasy", 2001},
        {"Rainbow Six", "Thriller", 1998},
        {"Hannibal", "Horror", 1999},
        {"Twelve Sharp", "Crime", 2006},
        {"The Bear and the Dragon", "Thriller", 2000},
        {"The Testament", "Adventure Story", 1999},
        {"Red Rabbit", "Historical fiction", 2002},
        {"Anansi Boys", "Fantasy", 2005},
        {"Airframe", "Thriller", 1997},
        {"Harry Potter y la camara secreta", "Fantasy", 1998},
        {"The King of Torts", "Thriller", 2003},
        {"The Da Vinci Code", "Mystery", 2003},
        {"Harry Potter y la Orden del Fenix", "Fantasy", 2003},
        {"Mary, Mary", "Crime", 2005},
        {"The Summons", "Thriller", 2002},
        {"Bag of Bones", "Horror", 1998},
        {"The 5th Horseman", "Thriller", 2006},
        {"Step on a Crack", "Thriller", 2007},
        {"Winter's Heart", "Fantasy", 2000},
        {"Plum Island", "Fiction", 1997},
        {"Eleven on Top", "Crime", 2005},
        {"Harry Potter y el misterio del principe", "Fantasy", 2005},
        {"The Closers", "Crime", 2005},
        {"Glorious Appearing", "Post-apocalyptic fiction", 2004},
        {"Prey ", "Science fiction", 2002},
        {"The Last Juror", "Thriller", 2004},
        {"'S' Is for Silence", "Mystery", 2005},
        {"4th of July", "Mystery", 2005},
        {"Harry Potter y las reliquias de la Muerte", "Fantasy", 2007},
        {"The Shelters of Stone", "Historical fiction", 2002},
        {"Harry Potter y el caliz de fuego", "Fantasy", 2000},
        {"The Dark Tower VII: The Dark Tower", "Fantasy", 2004},
        {"Book of the Dead ", "Crime", 2007},
        {"The Dark Tower VI: Song of Susannah", "Fantasy", 2004},
        {"Cold Mountain", "Historical novel", 1997},
        {"A Feast for Crows", "Fantasy", 2005},
        //{"Prueba Profe", "Overwatch", 2016},
};
size_t LONGITUD_LIBROS = sizeof(LIBROS) / sizeof(Libro);

Pila* init_caja() {
    Pila* caja = pila_nueva(LONGITUD_LIBROS);

    caja->deberia_liberar_direccion_datos_nodo = false;

    for (int i = 0; i < LONGITUD_LIBROS; i++) {
        pila_push(caja, &LIBROS[i]);
    }

    return caja;
}

Libro* como_libro(void* addr) {
    return (Libro*)addr;
}

void encabezado() {
    printf("--- Caja de libros (%zu libros) ---\n\n", LONGITUD_LIBROS);
}

void imprimir_libro(void* addr) {
    const Libro* libro = como_libro(addr);

    printf(" (%d), (%s), (%s) ", libro->year, libro->genre, libro->title);
}

Pila** pilas_coinciden_una_o_crear(Pila** pilas, size_t* longitud_pilas, Libro* libro, char* estrategia) {
    if (libro == NULL) {
        return pilas;
    }

    bool es_coincidencia_genero = strcmp(estrategia, "genero") == 0;

    for (int i = 0; i < *longitud_pilas; i++) {
        Libro* libro_tope = como_libro(pilas[i]->tope->datos);

        if (!libro_tope) {
            continue;
        }

        if (
                (es_coincidencia_genero && strcmp(libro_tope->genre, libro->genre) == 0) ||
                (!es_coincidencia_genero && (libro_tope->year - libro->year == 0))) {
            pila_push(pilas[i], libro);
            return pilas;
        }
    }

    if (pilas == NULL) {
        pilas = calloc(1, sizeof(Pila));
    } else {
        pilas = realloc(pilas, ((*longitud_pilas) + 1) * sizeof(Pila));
    }

    /** Capacidad para la cantidad máxima de libros que la pila puede contener */
    pilas[*longitud_pilas] = pila_nueva(LONGITUD_LIBROS);
    /** Dado que los libros no están asignados dinámicamente */
    pilas[*longitud_pilas]->deberia_liberar_direccion_datos_nodo = false;

    pila_push(pilas[*longitud_pilas], libro);

    *longitud_pilas += 1;

    return pilas;
}

int comparar_genero(Pila* a, Pila* b) {
    Libro* libro_a = (Libro *) como_libro(a->tope->datos);
    Libro* libro_b = como_libro(b->tope->datos);
    return strcmp(libro_a->genre, libro_b->genre);
}

int comparar_ano(Pila* a, Pila* b) {
    Libro* libro_a = como_libro(a->tope->datos);
    Libro* libro_b = como_libro(b->tope->datos);
    return libro_a->year - libro_b->year;
}

Pila** menu_pila_por(Pila* caja, size_t* longitud_pilas_dir, char* estrategia) {
    NodoArbol* raiz = NULL;
    size_t longitud_pilas = *longitud_pilas_dir;

    const bool es_pilas_genero = strcmp(estrategia, "genero") == 0;

    // Initialize pilas here
    Pila** pilas = calloc(longitud_pilas, sizeof(Pila*));

    while (caja->tope) {
        Libro* libro = como_libro(caja->tope->datos);
        bool pila_existente = false;
        for (int i = 0; i < longitud_pilas; i++) {
            Libro* libro_tope = como_libro(pilas[i]->tope->datos);
            if ((es_pilas_genero && strcmp(libro_tope->genre, libro->genre) == 0) ||
                (!es_pilas_genero && libro_tope->year == libro->year)) {
                pila_push(pilas[i], libro);
                pila_existente = true;
                break;
            }
        }
        if (!pila_existente) {
            Pila* pila = pila_nueva(LONGITUD_LIBROS);
            pila->deberia_liberar_direccion_datos_nodo = false;
            pila_push(pila, libro);
            nodo_arbol_insertar(&raiz, pila, es_pilas_genero ? comparar_genero : comparar_ano);
            longitud_pilas++;
        }
        pila_pop(caja);
    }

    nodo_arbol_a_pilas(raiz, &pilas, longitud_pilas_dir);

    return pilas;
}


int main() {
    Pila* caja = init_caja();
    bool deberia_continuar = true;
    char res_char = '\0';

    while (deberia_continuar) {
        Pila** pilas = NULL;
        size_t longitud_pilas = 0;

        unsigned int opcion_seleccionada = 0;


        printf("MENÚ\n\n");

        printf("[0]: Mostrar contenido de la caja\n");
        printf("[1]: Pila por género\n");
        printf("[2]: Pila por año\n");
        printf("[3]: Salir\n\n");

        printf("Selección: ");
        scanf("%d", &opcion_seleccionada);

        /** De esta manera para mantener la legibilidad del código */
        if (opcion_seleccionada == 3) {
            break;
        }




        switch (opcion_seleccionada) {
            case 0:
                printf("\n[0] Mostrar contenido de la caja\n\n");

                pila_imprimir_vertical(caja, imprimir_libro);

                printf("\nPresione Enter para continuar: ");
                getchar();  // Espera a que el usuario presione Enter
                deberia_continuar = 1;  // Puedes establecer la condición de continuación como desees
                break;
            case 1:
                pilas = menu_pila_por(caja, &longitud_pilas, "genero");
                break;
            case 2:
                pilas = menu_pila_por(caja, &longitud_pilas, "año");
                break;
            default:
                break;
        }

        if (pilas == NULL) {
            continue;
        }

        for (int i = 0; i < longitud_pilas; i++) {
            while (pilas[i]->tope) {
                pila_push(caja, pilas[i]->tope->datos);
                pila_pop(pilas[i]);
            }

            pila_liberar(pilas[i]);
        }

        free(pilas);
    }

    pila_liberar(caja);


    printf("[¡El programa ha finalizado!");

    return 0;
}