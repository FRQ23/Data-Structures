#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "tree.h"
#include "libros.h"

// Prototipo de la función agregar_a_pilas
void agregar_a_pilas(void* datos);

// Declaración global para pilas y longitud_pilas para usarlos en agregar_a_pilas
Pila** pilas = NULL;
size_t longitud_pilas = 0;
char* estrategia_global;

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
        pilas = calloc(1, sizeof(Pila*));
    } else {
        pilas = realloc(pilas, ((*longitud_pilas) + 1) * sizeof(Pila*));
    }

    pilas[*longitud_pilas] = pila_nueva(LONGITUD_LIBROS);
    pilas[*longitud_pilas]->deberia_liberar_direccion_datos_nodo = false;

    pila_push(pilas[*longitud_pilas], libro);

    *longitud_pilas += 1;

    return pilas;
}

void agregar_a_pilas(void* datos) {
    pilas = pilas_coinciden_una_o_crear(pilas, &longitud_pilas, (Libro*)datos, estrategia_global);
}

Pila** menu_pila_por(Pila* caja, size_t* longitud_pilas_dir, char* estrategia) {
    ArbolBinario arbol;
    if (strcmp(estrategia, "genero") == 0) {
        arbol.comparar = comparar_genero;
    } else {
        arbol.comparar = comparar_ano;
    }
    arbol.raiz = NULL;

    while (caja->tope) {
        arbol_insertar(&arbol, caja->tope->datos);
        pila_pop(caja);
    }

    // Inicializar pilas y longitud_pilas
    pilas = NULL;
    longitud_pilas = 0;
    estrategia_global = estrategia;

    arbol_recorrer_inorden(arbol.raiz, agregar_a_pilas);

    nodo_arbol_liberar(arbol.raiz);

    *longitud_pilas_dir = longitud_pilas;
    return pilas;
}

void mostrar_opciones_genero(Pila** pilas, size_t longitud_pilas) {
    char* generos[longitud_pilas];
    for (int i = 0; i < longitud_pilas; i++) {
        generos[i] = como_libro(pilas[i]->tope->datos)->genre;
    }

    for (int i = 0; i < longitud_pilas - 1; i++) {
        for (int j = i + 1; j < longitud_pilas; j++) {
            if (strcmp(generos[i], generos[j]) > 0) {
                char* temp = generos[i];
                generos[i] = generos[j];
                generos[j] = temp;
            }
        }
    }

    for (int i = 0; i < longitud_pilas; i++) {
        printf("[%d]: %s\n", i, generos[i]);
    }
}

void mostrar_opciones_ano(Pila** pilas, size_t longitud_pilas) {
    unsigned int anos[longitud_pilas];
    for (int i = 0; i < longitud_pilas; i++) {
        anos[i] = como_libro(pilas[i]->tope->datos)->year;
    }

    for (int i = 0; i < longitud_pilas - 1; i++) {
        for (int j = i + 1; j < longitud_pilas; j++) {
            if (anos[i] > anos[j]) {
                unsigned int temp = anos[i];
                anos[i] = anos[j];
                anos[j] = temp;
            }
        }
    }

    for (int i = 0; i < longitud_pilas; i++) {
        printf("[%d]: %u\n", i, anos[i]);
    }
}

int main() {
    Pila* caja = init_caja();
    bool deberia_continuar = true;

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

        if (opcion_seleccionada == 3) {
            break;
        }

        switch (opcion_seleccionada) {
            case 0:
                printf("\n[0] Mostrar contenido de la caja\n\n");
                pila_imprimir_vertical(caja, imprimir_libro);
                printf("\nPresione Enter para continuar: ");
                getchar();
                deberia_continuar = 1;
                break;
            case 1:
                pilas = menu_pila_por(caja, &longitud_pilas, "genero");
                printf("\n[1] Pila por género\n\n");
                mostrar_opciones_genero(pilas, longitud_pilas);
                printf("Seleccione una opción: ");
                scanf("%d", &opcion_seleccionada);
                pila_imprimir_vertical(pilas[opcion_seleccionada], imprimir_libro);
                break;
            case 2:
                pilas = menu_pila_por(caja, &longitud_pilas, "año");
                printf("\n[2] Pila por año\n\n");
                mostrar_opciones_ano(pilas, longitud_pilas);
                printf("Seleccione una opción: ");
                scanf("%d", &opcion_seleccionada);
                pila_imprimir_vertical(pilas[opcion_seleccionada], imprimir_libro);
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
