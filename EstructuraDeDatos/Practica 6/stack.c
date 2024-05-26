#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

Pila* pila_nueva(size_t capacidad) {
    Pila* pila = (Pila*)calloc(1, sizeof(Pila));
    pila->deberia_liberar_direccion_datos_nodo = true;
    pila->capacidad = capacidad;
    return pila;
}

NodoPila* nodo_pila_nuevo(void* datos) {
    NodoPila* nodo = (NodoPila*)calloc(1, sizeof(NodoPila));
    nodo->datos = datos;
    nodo->siguiente = NULL;
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
