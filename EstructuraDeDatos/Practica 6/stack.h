#ifndef __PILA__
#define __PILA__

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

Pila* pila_nueva(size_t capacidad);
NodoPila* nodo_pila_nuevo(void* datos);
void* pila_push(Pila* pila, void* datos);
void* pila_pop(Pila* pila);
void nodo_pila_liberar(NodoPila* nodo);
void pila_liberar(Pila* pila);
void pila_imprimir_horizontal(Pila* pila, void imprimir_datos(void*));
void pila_imprimir_vertical(Pila* pila, void imprimir_datos(void*));

#endif
