#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "libros.h"  // Incluir la definición de Libro

NodoArbol* nodo_arbol_nuevo(void* datos) {
    NodoArbol* nodo = (NodoArbol*)malloc(sizeof(NodoArbol));
    nodo->datos = datos;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

void nodo_arbol_liberar(NodoArbol* nodo) {
    if (nodo) {
        nodo_arbol_liberar(nodo->izquierda);
        nodo_arbol_liberar(nodo->derecha);
        free(nodo);
    }
}

void arbol_insertar(ArbolBinario* arbol, void* datos) {
    NodoArbol* nodo_nuevo = nodo_arbol_nuevo(datos);
    if (arbol->raiz == NULL) {
        arbol->raiz = nodo_nuevo;
        return;
    }

    NodoArbol* actual = arbol->raiz;
    NodoArbol* padre = NULL;
    while (actual != NULL) {
        padre = actual;
        if (arbol->comparar(datos, actual->datos) < 0) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }

    if (arbol->comparar(datos, padre->datos) < 0) {
        padre->izquierda = nodo_nuevo;
    } else {
        padre->derecha = nodo_nuevo;
    }
}

void arbol_recorrer_inorden(NodoArbol* nodo, void (*visitar)(void*)) {
    if (nodo != NULL) {
        arbol_recorrer_inorden(nodo->izquierda, visitar);
        visitar(nodo->datos);
        arbol_recorrer_inorden(nodo->derecha, visitar);
    }
}

int comparar_genero(void* a, void* b) {
    Libro* libroA = (Libro*)a;
    Libro* libroB = (Libro*)b;
    return strcmp(libroA->genre, libroB->genre);
}

int comparar_ano(void* a, void* b) {
    Libro* libroA = (Libro*)a;
    Libro* libroB = (Libro*)b;
    return (libroA->year - libroB->year);
}
