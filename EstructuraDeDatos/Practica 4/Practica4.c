#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERDADERO 1
#define FALSO 0
#define MAX_CANCIONES 15

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
    int bucle_activado; // Nueva variable para controlar el bucle
} Cola;

// Prototipos de funciones
void inicializar_cola(Cola *cola_reproduccion);
void desplegar_reproduccion(Cola *cola_reproduccion);
void agregar_cancion(Cola *cola_reproduccion, Cancion *cancion);
void mostrar_lista_canciones(Cancion *canciones, int num_canciones);
void eliminar_cancion(Cola *cola_reproduccion, int posicion);
void reiniciar_reproduccion(Cola *cola_reproduccion);
void alternar_bucle(Cola *cola_reproduccion); // Nueva función para alternar el bucle

int main(void) {
    int option, corre_programa;

    corre_programa = VERDADERO;

    Cola cola_reproduccion;

    Cancion canciones[MAX_CANCIONES] = {
            {"Freak on a Leash", "Korn"},
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
            {"Coming Undone", "Korn"}
    };


    inicializar_cola(&cola_reproduccion);

    while (corre_programa) {
        system("cls"); //WINDOWS
        printf("\n\n");
        desplegar_reproduccion(&cola_reproduccion);
        printf("\n\n");
        printf("\n [0] BUCLE");
        printf("\n [1] ANTERIOR");
        printf("\n [2] SIGUIENTE");
        printf("\n [3] AGREGAR CANCION");
        printf("\n [4] MOSTRAR LISTA DE CANCIONES");
        printf("\n [5] QUITAR CANCION");
        printf("\n [6] REINICIAR REPRODUCCION");
        printf("\n [7] ALTERNAR BUCLE"); // Opción para alternar el bucle
        printf("\n [8] TERMINAR PROGRAMA");

        printf("\n\n Escoge opcion: ");
        scanf("%d", &option);
        switch (option) {
            case 0:
                if (cola_reproduccion.num_elementos > 0) {
                    if (cola_reproduccion.actual == NULL) {
                        cola_reproduccion.actual = cola_reproduccion.frente;
                    }
                    cola_reproduccion.actual->ant = cola_reproduccion.fin;
                    cola_reproduccion.actual->sig = cola_reproduccion.frente;
                }
                break;
            case 1:
                if (cola_reproduccion.actual != NULL && cola_reproduccion.actual->ant != NULL) {
                    cola_reproduccion.actual = cola_reproduccion.actual->ant;
                }
                break;
            case 2:
                if (cola_reproduccion.actual != NULL && cola_reproduccion.actual->sig != NULL) {
                    cola_reproduccion.actual = cola_reproduccion.actual->sig;
                } else {
                    printf("No hay más canciones después de la actual.\n");
                }
                break;
            case 3:
                mostrar_lista_canciones(canciones, MAX_CANCIONES);
                int seleccion;
                printf("Selecciona una canción para agregar: ");
                scanf("%d", &seleccion);
                if (seleccion >= 0 && seleccion < MAX_CANCIONES) {
                    agregar_cancion(&cola_reproduccion, &canciones[seleccion]);
                } else {
                    printf("Selección inválida.\n");
                }
                break;
            case 4:
                printf("Lista de reproducción actual:\n");
                Elemento *actual = cola_reproduccion.frente;
                int posicion = 0;
                while (actual != NULL) {
                    printf("[%d] %s - %s\n", posicion, actual->dato.nombre, actual->dato.autor);
                    actual = actual->sig;
                    posicion++;
                }
                cola_reproduccion.actual = cola_reproduccion.frente; // Volver al frente de la cola
                break;

            case 5:
                if (cola_reproduccion.num_elementos > 0) {
                    printf("Canciones en la lista de reproducción:\n");
                    desplegar_reproduccion(&cola_reproduccion);
                    printf("\n");

                    int posicion_eliminar;
                    printf("Selecciona una canción para eliminar: ");
                    scanf("%d", &posicion_eliminar);
                    if (posicion_eliminar >= 0 && posicion_eliminar < cola_reproduccion.num_elementos) {
                        eliminar_cancion(&cola_reproduccion, posicion_eliminar);
                    } else {
                        printf("Selección inválida.\n");
                    }
                } else {
                    printf("No hay canciones en la lista de reproducción.\n");
                }
                break;

            case 6:
                reiniciar_reproduccion(&cola_reproduccion);
                break;
            case 7:
                alternar_bucle(&cola_reproduccion); // Llamada a la función para alternar el bucle
                break;
            case 8:
                corre_programa = 0;
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }
    printf("\n\n");
    return 0;
}

void inicializar_cola(Cola *cola_reproduccion) {
    cola_reproduccion->frente = NULL;
    cola_reproduccion->fin = NULL;
    cola_reproduccion->actual = NULL;
    cola_reproduccion->posicion_actual = 0;
    cola_reproduccion->num_elementos = 0;
    cola_reproduccion->bucle_activado = FALSO; // Se inicializa el bucle desactivado
}

void desplegar_reproduccion(Cola *cola_reproduccion) {
    if (cola_reproduccion->actual != NULL) {
        if (cola_reproduccion->actual->ant != NULL) {
            printf("<<-- %s", cola_reproduccion->actual->ant->dato.nombre);
        } else {
            printf(" Ninguna <<--");
        }
        printf(" [%s] ", cola_reproduccion->actual->dato.nombre);
        if (cola_reproduccion->actual->sig != NULL) {
            printf("-->> %s", cola_reproduccion->actual->sig->dato.nombre);
        } else {
            printf("-->> Ninguna");
        }
        return;
    }
    printf(" Ninguna <<-- Ninguna -->> Ninguna");
}

void agregar_cancion(Cola *cola_reproduccion, Cancion *cancion) {
    Elemento *nuevo_elemento = (Elemento *)malloc(sizeof(Elemento));
    if (nuevo_elemento == NULL) {
        printf("Error: Memoria insuficiente.\n");
        return;
    }
    nuevo_elemento->dato = *cancion;
    nuevo_elemento->ant = NULL;
    nuevo_elemento->sig = NULL;

    printf("Ingresa la posición donde deseas agregar la canción (0-%d): ", cola_reproduccion->num_elementos);
    int posicion;
    scanf("%d", &posicion);
    while (posicion < 0 || posicion > cola_reproduccion->num_elementos) {
        printf("Posición inválida. Ingresa una posición válida (0-%d): ", cola_reproduccion->num_elementos);
        scanf("%d", &posicion);
    }

    if (cola_reproduccion->frente == NULL) {
        cola_reproduccion->frente = nuevo_elemento;
        cola_reproduccion->fin = nuevo_elemento;
        cola_reproduccion->actual = nuevo_elemento;
    } else {
        if (posicion == 0) {
            nuevo_elemento->sig = cola_reproduccion->frente;
            cola_reproduccion->frente->ant = nuevo_elemento;
            cola_reproduccion->frente = nuevo_elemento;
        } else if (posicion == cola_reproduccion->num_elementos) {
            cola_reproduccion->fin->sig = nuevo_elemento;
            nuevo_elemento->ant = cola_reproduccion->fin;
            cola_reproduccion->fin = nuevo_elemento;
        } else {
            Elemento *actual = cola_reproduccion->frente;
            for (int i = 0; i < posicion; i++) {
                actual = actual->sig;
            }
            nuevo_elemento->sig = actual;
            nuevo_elemento->ant = actual->ant;
            actual->ant->sig = nuevo_elemento;
            actual->ant = nuevo_elemento;
        }
    }
    cola_reproduccion->num_elementos++;
}

void mostrar_lista_canciones(Cancion *canciones, int num_canciones) {
    printf("\nLista de Canciones:\n");
    for (int i = 0; i < num_canciones; i++) {
        printf("[%d] %s\n", i, canciones[i].nombre);
    }
}

void reiniciar_reproduccion(Cola *cola_reproduccion) {
    cola_reproduccion->actual = cola_reproduccion->frente;
}

void eliminar_cancion(Cola *cola_reproduccion, int posicion) {
    if (posicion < 0 || posicion >= cola_reproduccion->num_elementos) {
        printf("Posición inválida.\n");
        return;
    }

    Elemento *actual = cola_reproduccion->frente;
    for (int i = 0; i < posicion; i++) {
        actual = actual->sig;
    }

    if (actual == cola_reproduccion->actual) {
        cola_reproduccion->actual = actual->sig; // Nueva canción actual será la siguiente
        if (cola_reproduccion->actual == NULL) { // Si no hay siguiente, se coloca la anterior
            cola_reproduccion->actual = actual->ant;
        }
    }

    if (actual->ant != NULL) {
        actual->ant->sig = actual->sig;
    } else {
        cola_reproduccion->frente = actual->sig;
    }

    if (actual->sig != NULL) {
        actual->sig->ant = actual->ant;
    } else {
        cola_reproduccion->fin = actual->ant;
    }

    free(actual);
    cola_reproduccion->num_elementos--;
}

void alternar_bucle(Cola *cola_reproduccion) {
    cola_reproduccion->bucle_activado = !cola_reproduccion->bucle_activado; // Invertir el estado del bucle
    if (cola_reproduccion->bucle_activado) {
        printf("Bucle activado.\n");
    } else {
        printf("Bucle desactivado.\n");
    }
}


