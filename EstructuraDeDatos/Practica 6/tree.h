#ifndef __ARBOL_BINARIO__
#define __ARBOL_BINARIO__

typedef struct NodoArbol {
    void* datos;
    struct NodoArbol* izquierda;
    struct NodoArbol* derecha;
} NodoArbol;

typedef struct {
    NodoArbol* raiz;
    int (*comparar)(void*, void*);
} ArbolBinario;

NodoArbol* nodo_arbol_nuevo(void* datos);
void nodo_arbol_liberar(NodoArbol* nodo);
void arbol_insertar(ArbolBinario* arbol, void* datos);
void arbol_recorrer_inorden(NodoArbol* nodo, void (*visitar)(void*));
int comparar_genero(void* a, void* b);
int comparar_ano(void* a, void* b);

#endif
