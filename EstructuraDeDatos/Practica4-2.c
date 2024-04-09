//
// Created by Fertronic on 4/8/2024.
//


#include <stdio.h>
#include <stdlib.h>

#define VERDADERO 1
#define FALSO 0

typedef struct cancion {
    char nombre[50];
    char autor[50];
    short int release_date;
} Cancion;

typedef struct elemento {
    Cancion dato;
    struct elemento *ant;
    struct elemento *sig;
} Elemento;

typedef struct cola {
    Elemento *frente;
    Elemento *fin;
    Elemento *actual;
    int posicion_actual;
    int num_elementos;
    int bucle_activado; // Add this line
} Cola;


//definir funciones

void iniciarlizar_cola(Cola *cola_reproduccion);
void desplegar_reproduccion(Cola *cola_reproduccion);
void desactivar_bucle_reproduccion(Cola *cola_reproduccion);
void activar_bucle_reproduccion(Cola *cola_reproduccion);
void reproducir_anterior(Cola *cola_reproduccion);
void reproducir_siguiente(Cola *cola_reproduccion);
int es_cola_vacia(Cola *cola_reproduccion);
void mostrar_canciones_disponibles(Cancion canciones[], int num_canciones);
int seleccionar_cancion(Cancion canciones[], int num_canciones);
int seleccionar_posicion(Cola *cola_reproduccion);
void eliminar_cancion(Cola *cola_reproduccion, int posicion);
void mover_actual_al_inicio(Cola *cola_reproduccion);
void mostrar_canciones_cola(Cola *cola_reproduccion);
int es_posicion_valida(Cola *cola_reproduccion, int posicion);


int main(void) {
    // Arreglo de canciones (mínimo 15)
    static Cancion canciones[15] = {{"Freak on a Leash", "Korn"},
                                    {"Last Resort", "Papa Roach"},
                                    {"Bodies", "Drowning Pool"},
                                    {"One Step Closer", "Linkin Park"},
                                    {"Down With the Sickness", "Disturbed"},
                                    {"My Own Summer (Shove It)", "Deftones"},
                                    {"Blind", "Mudvayne"},
                                    {"Wait and Bleed", "Slipknot"},
                                    {"Numb", "Linkin Park"},
                                    {"Chop Suey!", "System of a Down"},
                                    {"Killing in the Name", "Rage Against the Machine"},
                                    {"B.Y.O.B.", "System of a Down"},
                                    {"Crawling", "Linkin Park"},
                                    {"Click Click Boom", "Saliva"},
                                    {"Coming Undone", "Korn"}};

    int i, option, corre_programa;

    corre_programa = VERDADERO;

    Cola cola_reproduccion;
    iniciarlizar_cola(&cola_reproduccion);

    while (corre_programa) {
        //system("cls"); // WINDOWS
        printf("\n\r");
        desplegar_reproduccion(&cola_reproduccion);
        printf("\n\r");
        printf("\n\r [0] BUCLE");
        printf("\n\r [1] ANTERIOR");
        printf("\n\r [2] SIGUIENTE");
        printf("\n\r [3] AGREGAR CANCION");
        printf("\n\r [4] MOSTRAR LISTA DE REPRODUCCION");
        printf("\n\r [5] QUITAR CANCION");
        printf("\n\r [6] REINICIAR REPRODUCCION");
        printf("\n\r [7] TERMINAR PROGRAMA");

        printf("\n\r Escoge opcion: ");
        scanf("%d", &option);
        switch (option) {
            case 0:
                printf("Ejecutando caso 0...\n");
                if (cola_reproduccion.bucle_activado) {
                    desactivar_bucle_reproduccion(&cola_reproduccion);
                    printf("\n\r Bucle de reproduccion desactivado");
                } else {
                    activar_bucle_reproduccion(&cola_reproduccion);
                    printf("\n\r Bucle de reproduccion activado");
                }
                break;
            case 1:
                printf("Ejecutando caso 1...\n");
                reproducir_anterior(&cola_reproduccion);
                break;
            case 2:\
                printf("Ejecutando caso 2...\n");
                reproducir_siguiente(&cola_reproduccion);
                break;
                break;
            case 3:
                printf("Ejecutando caso 3...\n");
                mostrar_canciones_disponibles(canciones, 15);
                int cancion_seleccionada = seleccionar_cancion(canciones, 15);
                int posicion_seleccionada = seleccionar_posicion(cola_reproduccion);

                Elemento *nuevo_elemento = (Elemento *)malloc(sizeof(Elemento));
                nuevo_elemento->dato = canciones[cancion_seleccionada];

                if (posicion_seleccionada == 0) {
                    nuevo_elemento->ant = NULL;
                    nuevo_elemento->sig = cola_reproduccion->frente;
                    if (cola_reproduccion->frente != NULL) {
                        cola_reproduccion->frente->ant = nuevo_elemento;
                    }
                    cola_reproduccion->frente = nuevo_elemento;
                    if (cola_reproduccion->fin == NULL) {
                        cola_reproduccion->fin = nuevo_elemento;
                    }
                } else {
                    Elemento *temporal = cola_reproduccion->frente;
                    int i;

                    for (i = 1; i < posicion_seleccionada && temporal != NULL; i++) {
                        temporal = temporal->sig;
                    }

                    if (temporal != NULL) {
                        nuevo_elemento->ant = temporal;
                        nuevo_elemento->sig = temporal->sig;
                        if (temporal->sig != NULL) {
                            temporal->sig->ant = nuevo_elemento;
                        } else {
                            cola_reproduccion->fin = nuevo_elemento;
                        }
                        temporal->sig = nuevo_elemento;
                    } else {
                        nuevo_elemento->ant = cola_reproduccion->fin;
                        nuevo_elemento->sig = NULL;
                        if (cola_reproduccion->fin != NULL) {
                            cola_reproduccion->fin->sig = nuevo_elemento;
                        }
                        cola_reproduccion->fin = nuevo_elemento;
                        if (cola_reproduccion->frente == NULL) {
                            cola_reproduccion->frente = nuevo_elemento;
                        }
                    }
                }
                cola_reproduccion->num_elementos++;
                break;
            case 4:
                printf("Ejecutando caso 4...\n");
                if (!es_cola_vacia(&cola_reproduccion)) {
                    mostrar_canciones_cola(&cola_reproduccion);
                } else {
                    printf("\n\r La lista de reproduccion esta vacia");
                }
                break;
            case 5:
                printf("Ejecutando caso 5...\n");
                if (!es_cola_vacia(&cola_reproduccion)) {
                    mostrar_canciones_cola(&cola_reproduccion);
                    int posicion_seleccionada = seleccionar_posicion(&cola_reproduccion);

                    eliminar_cancion(&cola_reproduccion, posicion_seleccionada);
                } else {
                    printf("\n\r La lista de reproduccion esta vacia");
                }
                break;
            case 6:
                printf("Ejecutando caso 6...\n");
                if (!es_cola_vacia(&cola_reproduccion)) {
                    mover_actual_al_inicio(&cola_reproduccion);
                }
                break;
            case 7:
                printf("Ejecutando caso 7...\n");
                corre_programa = 0;
                break;
            default:
                printf("Opción no reconocida.\n");
                break;
        }
    }

    printf("\n\n\r");
    return 0;
}

void activar_bucle_reproduccion(Cola *cola_reproduccion) {
    printf("Activando bucle de reproduccion...\n");
    if (cola_reproduccion->fin != NULL && cola_reproduccion->frente != NULL) {
        cola_reproduccion->fin->sig = cola_reproduccion->frente;
        cola_reproduccion->frente->ant = cola_reproduccion->fin;
        cola_reproduccion->bucle_activado = VERDADERO;  // Add this line
    } else {
        printf("No se puede activar el bucle de reproduccion porque la cola esta vacia.\n");
    }
}

void desactivar_bucle_reproduccion(Cola *cola_reproduccion) {
    printf("Desactivando bucle de reproduccion...\n");
    if (cola_reproduccion->fin != NULL && cola_reproduccion->frente != NULL) {
        cola_reproduccion->fin->sig = NULL;
        cola_reproduccion->frente->ant = NULL;
        cola_reproduccion->bucle_activado = FALSO;  // Add this line
    } else {
        printf("No se puede desactivar el bucle de reproduccion porque la cola esta vacia.\n");
    }
}

void reproducir_siguiente(Cola *cola_reproduccion) {
    if (cola_reproduccion->actual != NULL) {
        cola_reproduccion->actual = cola_reproduccion->actual->sig;
        if (cola_reproduccion->actual == NULL) {
            if (cola_reproduccion->bucle_activado) {
                cola_reproduccion->actual = cola_reproduccion->frente;
            }
        }
    }
}

void reproducir_anterior(Cola *cola_reproduccion) {
    if (cola_reproduccion->actual != NULL) {
        if (cola_reproduccion->actual->ant != NULL) {
            cola_reproduccion->actual = cola_reproduccion->actual->ant;
        } else {
            if (cola_reproduccion->bucle_activado) {
                cola_reproduccion->actual = cola_reproduccion->fin;
            }
        }
    }
}

void iniciarlizar_cola(Cola *cola_reproduccion) {
    cola_reproduccion->frente = NULL;
    cola_reproduccion->fin = NULL;
    cola_reproduccion->actual = NULL;
    cola_reproduccion->posicion_actual = 0;
    cola_reproduccion->num_elementos = 0;
    cola_reproduccion->bucle_activado = FALSO; // Bucle de reproducción desactivado al inicio
}

void desplegar_reproduccion(Cola *cola_reproduccion) {
    if (cola_reproduccion->actual != NULL) {
        if (cola_reproduccion->actual->ant != NULL) {
            printf(" <<-- ");
            printf("%s - %s (%d)", cola_reproduccion->actual->ant->dato.nombre,
                   cola_reproduccion->actual->ant->dato.autor,
                   cola_reproduccion->actual->ant->dato.release_date);
        } else {
            printf(" Ninguna <<--");
        }
        printf(" **%s - %s (%d)** ", cola_reproduccion->actual->dato.nombre,
               cola_reproduccion->actual->dato.autor,
               cola_reproduccion->actual->dato.release_date);

        if (cola_reproduccion->actual->sig != NULL) {
            printf("-->> ");
            printf("%s - %s (%d)", cola_reproduccion->actual->sig->dato.nombre,
                   cola_reproduccion->actual->sig->dato.autor,
                   cola_reproduccion->actual->sig->dato.release_date);
        } else {
            printf("-->> Ninguna");
        }
        return;
    }
    printf(" Ninguna <<-- Ninguna -->> Ninguna");
}

void agregar_cancion(Cola *cola_reproduccion, Cancion cancion) {
    Elemento *nuevo_elemento = (Elemento *)malloc(sizeof(Elemento));
    nuevo_elemento->dato = cancion;
    nuevo_elemento->ant = NULL;
    nuevo_elemento->sig = NULL;

    if (es_cola_vacia(cola_reproduccion)) {
        cola_reproduccion->frente = nuevo_elemento;
        cola_reproduccion->fin = nuevo_elemento;
        cola_reproduccion->actual = nuevo_elemento;
    } else {
        cola_reproduccion->fin->sig = nuevo_elemento;
        nuevo_elemento->ant = cola_reproduccion->fin;
        cola_reproduccion->fin = nuevo_elemento;
    }
    cola_reproduccion->num_elementos++;
}

int seleccionar_posicion(Cola *cola_reproduccion) {
    int opcion;

    do {
        printf("\n\r Selecciona una posicion (0-%d): ",
               cola_reproduccion->num_elementos);
        scanf("%d", &opcion);
    } while (opcion < 0 || (opcion > cola_reproduccion->num_elementos && cola_reproduccion->num_elementos != 0));

    return opcion;
}

void eliminar_cancion(Cola *cola_reproduccion, int posicion) {
    if (es_posicion_valida(cola_reproduccion, posicion)) {
        Elemento *temporal = cola_reproduccion->frente;
        int i;

        if (posicion == 1) {
            cola_reproduccion->frente = cola_reproduccion->frente->sig;
            if (cola_reproduccion->frente != NULL) {
                cola_reproduccion->frente->ant = NULL;
            } else {
                cola_reproduccion->fin = NULL;
            }
        } else {
            for (i = 1; i < posicion; i++) {
                temporal = temporal->sig;
            }

            if (temporal == cola_reproduccion->actual) {
                cola_reproduccion->actual = cola_reproduccion->actual->sig;
            }

            if (temporal->ant != NULL) {
                temporal->ant->sig = temporal->sig;
            } else {
                cola_reproduccion->frente = temporal->sig;
            }

            if (temporal->sig != NULL) {
                temporal->sig->ant = temporal->ant;
            } else {
                cola_reproduccion->fin = temporal->ant;
            }
        }
        free(temporal);
        cola_reproduccion->num_elementos--;

        if (cola_reproduccion->actual == NULL) {
            cola_reproduccion->posicion_actual = 0;
        }
    }
}

void mover_actual_al_inicio(Cola *cola_reproduccion) {
    if (cola_reproduccion->actual != cola_reproduccion->frente) {
        Elemento *temporal = cola_reproduccion->actual;

        if (temporal->ant != NULL) {
            temporal->ant->sig = temporal->sig;
        } else {
            cola_reproduccion->frente = temporal->sig;
        }

        if (temporal->sig != NULL) {
            temporal->sig->ant = temporal->ant;
        } else {
            cola_reproduccion->fin = temporal->ant;
        }

        temporal->ant = NULL;
        temporal->sig = cola_reproduccion->frente;
        cola_reproduccion->frente->ant = temporal;
        cola_reproduccion->frente = temporal;
        cola_reproduccion->posicion_actual = 1;
    }
}

int es_cola_vacia(Cola *cola_reproduccion) {
    return (cola_reproduccion->frente == NULL);
}

int es_posicion_valida(Cola *cola_reproduccion, int posicion) {
    if (cola_reproduccion == NULL) {
        return 0;
    }
    return (posicion > 0 && posicion <= cola_reproduccion->num_elementos);
}

void mostrar_canciones_disponibles(Cancion canciones[], int num_canciones) {
    printf("Inside mostrar_canciones_disponibles function\n");
    int i;

    for (i = 0; i < num_canciones; i++) {
        printf("\n\r [%d] %s - %s (%d)", i + 1, canciones[i].nombre,
               canciones[i].autor, canciones[i].release_date);
        printf("Inside loop, i = %d\n", i);
    }
}

void mostrar_canciones_cola(Cola *cola_reproduccion) {
    Elemento *temporal = cola_reproduccion->frente;
    int i = 1;

    while (temporal != NULL) {
        if (temporal == cola_reproduccion->actual) {
            printf("\n\r [%d] **%s - %s (%d)**", i, temporal->dato.nombre,
                   temporal->dato.autor, temporal->dato.release_date);
        } else {
            printf("\n\r [%d] %s - %s (%d)", i, temporal->dato.nombre,
                   temporal->dato.autor, temporal->dato.release_date);
        }
        temporal = temporal->sig;
        i++;
    }
}

int seleccionar_cancion(Cancion canciones[], int num_canciones) {
    int opcion;

    do {
        printf("\n\r Selecciona una cancion (1-%d): ", num_canciones);
        scanf("%d", &opcion);
    } while (!es_posicion_valida(NULL, opcion));

    return opcion - 1;
}

