#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define null NULL
#define ACTIVAR 1
#define DESACTIVAR 0

typedef struct
{
    char* nombre;
    char* autor;
    int fechaSalida;
} Cancion;

typedef struct Elemento
{
    Cancion* cancion;
    struct Elemento* siguiente;
} Elemento;

typedef struct
{
    Elemento* inicio;
    int cantidadElementos;
} Pila;

typedef struct
{
    Elemento* inicio;
    Elemento* final;
    Elemento* actual;
    int cantidadElementos;
    bool estaEnBucle;
    bool estaEnPrimIter;
} Cola;

Cola colaReproduccion;
Pila pilaAuxiliar;

void desplegarReproduccion(Cola* colaReproduccion);
void enqueue(Cola* cola, Cancion* cancion, int posicion);
void dequeue(Cola *cola, int posicion);
void inicializarCola(Cola* cola);
Elemento* alojarElemento(Cancion* cancion);
void mostrarColaReproduccion(Cola* cola);
int mostrarPlaylist(void);
void toggleBucle(Cola* cola, int activar);
bool estaEnModoCircular(Cola* cola);

static Cancion playlistOriginal[15] =
        {
                {"Like a Stone", "Audioslave", 2002},
                {"Decadence", "Disturbed", 2005},
                {"Something In The Way", "Nirvana", 1991},
                {"505", "Arctic Monkeys", 2007},
                {"Creep", "Radiohead", 1993},
                {"Freak On A Leash", "Korn", 1998},
                {"Twist", "Korn", 1996},
                {"Coming Undone", "Korn", 2005},
                {"The Less I Know The Better", "Tame Impala", 2015},
                {"Edge Of The Earth", "30 Seconds To Mars", 2002},
                {"Song 2", "Blur", 1997},
                {"The People That We Love", "Bush", 2001},
                {"Feel Good Inc", "Gorillaz", 2005},
                {"The Trooper", "Iron Maiden", 1983},
                {"Broken Promises", "Element Eighty", 2003}
        };

void desplegarReproduccion(Cola* colaReproduccion)
{
    if (colaReproduccion->actual == null)
    {
        printf("Ninguna <<-- Ninguna -->> Ninguna\n");
        return;
    }

    if (colaReproduccion->actual->siguiente != null)
    {
        printf("%s - %s <<-- ", colaReproduccion->actual->cancion->nombre, colaReproduccion->actual->cancion->autor);
    }
    else
    {
        printf("Ninguna <<-- ");
    }

    printf("%s - %s -->> ", colaReproduccion->actual->cancion->nombre, colaReproduccion->actual->cancion->autor);

    if (colaReproduccion->actual->siguiente != null)
    {
        printf("%s - %s\n", colaReproduccion->actual->siguiente->cancion->nombre, colaReproduccion->actual->siguiente->cancion->autor);
    }
    else
    {
        printf("Ninguna\n");
    }
}

void enqueue(Cola* cola, Cancion* cancion, int posicion)
{
    Elemento* nuevoElemento = alojarElemento(cancion);

    if (cola->cantidadElementos == 0)
    {
        // Si la cola está vacía, el nuevo elemento será tanto el inicio como el final de la cola
        cola->inicio = nuevoElemento;
        cola->final = nuevoElemento;
        cola->actual = nuevoElemento; // También será el elemento actual
        cola->cantidadElementos++;
        return;
    }

    if (posicion == 0)
    {
        // Si la posición es 0, el nuevo elemento se inserta al principio de la cola
        nuevoElemento->siguiente = cola->inicio;
        cola->inicio = nuevoElemento;
        cola->actual = nuevoElemento; // Actualiza el puntero actual
    }
    else
    {
        // Si la posición no es 0, se inserta en la posición especificada
        Elemento* actual = cola->inicio;
        for (int i = 0; i < posicion - 1; i++)
        {
            actual = actual->siguiente;
        }
        nuevoElemento->siguiente = actual->siguiente;
        actual->siguiente = nuevoElemento;
        // Verifica si el nuevo elemento se inserta al final de la cola
        if (actual == cola->final)
        {
            cola->final = nuevoElemento;
        }
        // Actualiza el puntero actual si es necesario
        if (cola->actual == actual)
        {
            cola->actual = nuevoElemento;
        }
    }

    cola->cantidadElementos++;
}


void dequeue(Cola *cola, int posicion)
{
    if (cola->cantidadElementos == 0)
    {
        printf("ERROR: underflow\n");
        return;
    }

    Elemento* elementoEliminado = null;

    if (posicion == 0)
    {
        elementoEliminado = cola->inicio;
        cola->inicio = cola->inicio->siguiente;
    }
    else
    {
        Elemento* actual = cola->inicio;
        for (int i = 0; i < posicion - 1; i++)
        {
            actual = actual->siguiente;
        }
        elementoEliminado = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
    }

    if (cola->cantidadElementos == 1)
    {
        cola->final = null;
    }

    cola->cantidadElementos--;
    free(elementoEliminado);
}

void inicializarCola(Cola* cola)
{
    cola->inicio = null;
    cola->final = null;
    cola->actual = null;
    cola->cantidadElementos = 0;
    cola->estaEnBucle = true;
    cola->estaEnPrimIter = true;
}

Elemento* alojarElemento(Cancion* cancion)
{
    Elemento* nuevo = malloc(sizeof(Elemento));
    nuevo->cancion = cancion;
    nuevo->siguiente = null;
    return nuevo;
}

void mostrarColaReproduccion(Cola* cola)
{
    if (cola->cantidadElementos == 0)
    {
        printf("Cola vacía\n");
        return;
    }

    Elemento* actual = cola->inicio;
    int n = 0;

    while (actual != null)
    {
        printf("%d) %s - %s\n", n, actual->cancion->nombre, actual->cancion->autor);
        actual = actual->siguiente;
        n++;
    }
}

int mostrarPlaylist(void)
{
    int seleccion;
    printf("\nCanciones disponibles: \n");
    for (int i = 0 ; i < 15 ; i++)
    {
        printf("%d) %s - %s\n", i, playlistOriginal[i].nombre, playlistOriginal[i].autor);
    }

    printf("Elige una canción\n> ");
    scanf("%d", &seleccion);

    return seleccion;
}

void toggleBucle(Cola* cola, int activar)
{
    if (activar == ACTIVAR)
    {
        cola->estaEnBucle = true;
    }
    else if (activar == DESACTIVAR)
    {
        cola->estaEnBucle = false;
    }
}

bool estaEnModoCircular(Cola* cola)
{
    return cola->estaEnBucle;
}

int main(void)
{
    int option, correPrograma, indice;

    correPrograma = true;

    inicializarCola(&colaReproduccion);

    while(correPrograma)
    {
        printf("\n\r");
        desplegarReproduccion(&colaReproduccion);
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
        scanf("%d",&option);
        switch(option)
        {
            case 0:
                printf("[0] BUCLE\n");

                if (colaReproduccion.estaEnBucle)
                {
                    toggleBucle(&colaReproduccion, DESACTIVAR);

                }else{
                    toggleBucle(&colaReproduccion, ACTIVAR);
                }

                break;
            case 1:
                printf("\n[1] ANTERIOR\n");

                if (colaReproduccion.actual != null && colaReproduccion.actual->siguiente != null)
                {
                    colaReproduccion.actual = colaReproduccion.actual->siguiente;
                }
                else
                {
                    printf("You are already at the first song, can't go to the previous.\n");
                }

                break;
            case 2:
                printf("\n[2] SIGUIENTE\n");

                if (colaReproduccion.actual != null && colaReproduccion.actual->siguiente != null)
                {
                    colaReproduccion.actual = colaReproduccion.actual->siguiente;
                }
                else
                {
                    printf("You are already at the last song, can't go to the next.\n");
                }

                break;
            case 3:
                printf("\n[3] Agregar canción\n");

                indice = mostrarPlaylist();

                if (indice < 0 || indice > 14) { break; }

                enqueue(&colaReproduccion, &playlistOriginal[indice], 0);

                if (colaReproduccion.estaEnPrimIter)
                {
                    toggleBucle(&colaReproduccion, DESACTIVAR);
                    colaReproduccion.estaEnPrimIter = false;
                    break;
                }

                if (estaEnModoCircular(&colaReproduccion) && !colaReproduccion.estaEnBucle)
                {
                    toggleBucle(&colaReproduccion, DESACTIVAR);
                }

                break;

            case 4:
                printf("\n[4] Mostrando cola de reproduccion\n");
                mostrarColaReproduccion(&colaReproduccion);
                break;
            case 5:
                printf("\n[5] Quitar cancion de la cola.\n");

                printf("\nMostrando cola de reproduccion\n");
                mostrarColaReproduccion(&colaReproduccion);
                printf("\nElige una posicion para eliminar la cancion\n> ");
                scanf("%d", &indice);

                dequeue(&colaReproduccion, indice);

                if (colaReproduccion.cantidadElementos == 0) { break; }

                if (estaEnModoCircular(&colaReproduccion) && !colaReproduccion.estaEnBucle)
                {
                    toggleBucle(&colaReproduccion, DESACTIVAR);
                }

                break;
            case 6:
                printf("\n[6] REINICIAR REPRODUCCION\n");

                if (colaReproduccion.inicio != null)
                {
                    colaReproduccion.actual = colaReproduccion.inicio;
                }

                printf("\nReproducción reiniciada.\n");
                break;
            case 7:
                printf("Bye bye\n");
                correPrograma = false;
                break;
            default:
                break;
        }
    }

    return 0;
}
