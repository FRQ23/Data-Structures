
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
    struct Elemento* anterior;

} Elemento;

typedef struct
{
    Elemento* inicio;
    Elemento* final;
    Elemento* actual;

    int maxTam;
    int cantidadElementos;
    bool estaEnBucle;
    bool estaEnPrimIter;

} Cola;

typedef struct ColaAxuiliar
{
    Elemento* inicio;
    Elemento* final;
    Elemento* actual;

    int maxTam;
    int cantidadElementos;

} ColaAuxiliar;

void desplegarReproduccion(Cola* colaReproduccion);
void dequeue(Cola *cola, int posicion);
void enqueue(Cola* cola, Cancion* cancion, int posicion);
void inicializarCola(Cola* cola);
Elemento* alojarElemento(Cancion* cancion);
void mostrarColaReproduccion(Cola* cola);
int mostrarPlaylist(void);
void toggleBucle(Cola* cola, int activar);
bool estaEnModoCircular(Cola* cola);

static Cancion playlistOriginal[15] =
        {
                {"Blind", "Korn", 1994},
                {"Down with the Sickness", "Disturbed", 2000},
                {"Last Resort", "Papa Roach", 2000},
                {"Freak On A Leash", "Korn", 1998},
                {"Numb", "Linkin Park", 2003},
                {"Chop Suey!", "System of a Down", 2001},
                {"Wait and Bleed", "Slipknot", 1999},
                {"Break Stuff", "Limp Bizkit", 1999},
                {"Crawling", "Linkin Park", 2000},
                {"Got the Life", "Korn", 1998},
                {"Bodies", "Drowning Pool", 2001},
                {"Falling Away from Me", "Korn", 1999},
                {"Click Click Boom", "Saliva", 2001},
                {"Dig", "Mudvayne", 2000},
                {"Before I Forget", "Slipknot", 2004}
        };

void desplegarReproduccion(Cola* colaReproduccion)
{
    if (colaReproduccion->actual == null)
    {
        printf("Ninguna <<-- Ninguna -->> Ninguna\n");
        return;
    }

    if (colaReproduccion->actual->anterior != null)
    {
        printf("%s - %s <<-- ", colaReproduccion->actual->anterior->cancion->nombre, colaReproduccion->actual->anterior->cancion->autor);

    }else{

        printf("Ninguna <<-- ");
    }

    printf("%s - %s -->> ", colaReproduccion->actual->cancion->nombre, colaReproduccion->actual->cancion->autor);

    if (colaReproduccion->actual->siguiente != null)
    {
        printf("%s - %s\n", colaReproduccion->actual->siguiente->cancion->nombre, colaReproduccion->actual->siguiente->cancion->autor);

    }else{

        printf("Ninguna\n");
    }

    return;
}

void dequeue(Cola *cola, int posicion)
{
    if (cola->cantidadElementos == 0)
    {
        printf("ERROR: underflow\n");
        return;
    }

    if (posicion < 0 || posicion >= cola->cantidadElementos)
    {
        printf("\nERROR: unvalidPOS\n");
        return;
    }

    Elemento* elementoEliminado = null;
    Cancion* cancionOut = null;

    if (posicion == 0)
    {
        elementoEliminado = cola->inicio;
        cancionOut = elementoEliminado->cancion;

        if (cola->cantidadElementos == 1)
        {
            cola->inicio = null;
            cola->final = null;
        }
        else
        {
            cola->inicio = cola->inicio->siguiente;
            cola->inicio->anterior = cola->final;
            cola->final->siguiente = cola->inicio;
        }
    }
    else if (posicion == cola->cantidadElementos - 1)
    {
        elementoEliminado = cola->final;
        cancionOut = elementoEliminado->cancion;

        cola->final = cola->final->anterior;
        cola->final->siguiente = cola->inicio;
        cola->inicio->anterior = cola->final;
    }
    else
    {
        Elemento* actual = cola->inicio;
        for (int i = 0; i < posicion; i++)
        {
            actual = actual->siguiente;
        }

        elementoEliminado = actual;
        cancionOut = elementoEliminado->cancion;

        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }

    cola->cantidadElementos--;

    if (cola->cantidadElementos == 0)
    {
        cola->actual = null;
    }
    else if (cola->actual == elementoEliminado && cola->cantidadElementos != 0)
    {
        if (cola->actual->siguiente != null)
        {
            //cola->actual = cola->actual->anterior;
            cola->actual = cola->actual->siguiente;

        }else{
            // cola->actual = cola->actual->siguiente; OPCION B: tiene mismo efecto
            cola->actual = cola->inicio;
        }
    }
    else{
        //representativo, cola->actual se queda igual.
        //cola->actual = cola->actual;
    }

    free(elementoEliminado);
    printf("\nCancion eliminada: %s\n", cancionOut->nombre);
    /*
    if (cola->actual == elementoEliminado && cola->cantidadElementos != 0)
    {
        cola->actual = cola->actual->anterior;

        free(elementoEliminado);
        cola->cantidadElementos--;
        //printf("\nCancion eliminada: %s\n", cancionOut->nombre);
        return;
    }




    if (cola->cantidadElementos == 0)
    {
        cola->actual = null;
    }
    else
    {
        cola->actual = cola->actual;
    }
    */

    //printf("Llega a return statement\n");
    return;
}

void enqueue(Cola* cola, Cancion* cancion, int posicion)
{
    if (cola->maxTam > 0 && cola->cantidadElementos == cola->maxTam)
    {
        printf("\nERROR:overflow\n");
        return;
    }

    if (posicion < 0 || posicion > cola->cantidadElementos)
    {
        printf("\nERROR:unvalidPOS\n");
        return;
    }

    Elemento* nuevoElemento = alojarElemento(cancion);

    if (cola->cantidadElementos == 0)
    {
        cola->inicio = nuevoElemento;
        cola->final = nuevoElemento;
        nuevoElemento->siguiente = nuevoElemento;
        nuevoElemento->anterior = nuevoElemento;
    }
    else
    {
        if (posicion == 0)
        {
            nuevoElemento->siguiente = cola->inicio;
            nuevoElemento->anterior = cola->final;
            cola->inicio->anterior = nuevoElemento;
            cola->final->siguiente = nuevoElemento;
            cola->inicio = nuevoElemento;
        }
        else if (posicion == cola->cantidadElementos)
        {
            nuevoElemento->siguiente = cola->inicio;
            nuevoElemento->anterior = cola->final;
            cola->final->siguiente = nuevoElemento;
            cola->inicio->anterior = nuevoElemento;
            cola->final = nuevoElemento;
        }
        else
        {
            Elemento* actual = cola->inicio;
            for (int i = 0 ; i < posicion - 1 ; i++) { actual = actual->siguiente; }

            nuevoElemento->siguiente = actual->siguiente;
            nuevoElemento->anterior = actual;
            actual->siguiente->anterior = nuevoElemento;
            actual->siguiente = nuevoElemento;
        }
    }

    cola->cantidadElementos++;

    if (cola->cantidadElementos == 1) { cola->actual = cola->inicio; }

    else{
        //representativo, {cola->actual} se queda igual.
        //cola->actual = cola->actual; 
    }

    return;
}

void inicializarCola(Cola* cola)
{
    cola->inicio = null;
    cola->final = null;
    cola->actual = null;
    cola->maxTam = 0;
    cola->cantidadElementos = 0;
    cola->estaEnBucle = true;
    cola->estaEnPrimIter = true;

    return;
}

Elemento* alojarElemento(Cancion* cancion)
{
    Elemento* nuevo = malloc(sizeof(Elemento));

    nuevo->cancion = cancion;
    nuevo->siguiente = null;
    nuevo->anterior = null;

    return nuevo;
}

void mostrarColaReproduccion(Cola* cola)
{
    if (cola->cantidadElementos == 0)
    {
        return;
    }

    Elemento* actual = cola->inicio;

    int n = 0;
    printf("\n");

    while (n < cola->cantidadElementos)
    {
        printf("%d)%s - %s\n", n, actual->cancion->nombre, actual->cancion->autor);
        n++;

        actual = actual->siguiente;
    }

    return;
}

int mostrarPlaylist(void)
{
    int seleccion;
    printf("\nCanciones disponibles: \n");
    for (int i = 0 ; i < 15 ; i++)
    {
        printf("%d) %s - %s\n", i, playlistOriginal[i].nombre, playlistOriginal[i].autor);
    }

    printf("Elige una cancion\n> ");
    scanf("\n%d", &seleccion);

    return seleccion;
}

void toggleBucle(Cola* cola, int activar)
{
    // si la cola esta vacia, salimos para evitar segmentation fault
    if (cola->cantidadElementos == 0) { return; }

    if (activar)
    {
        cola->inicio->anterior = cola->final;
        cola->final->siguiente = cola->inicio;
        cola->estaEnBucle = true;
        //printf("\nBUCLE ACTIVADO\n"); debug
    }
    else
    {
        cola->inicio->anterior = null;
        cola->final->siguiente = null;
        cola->estaEnBucle = false;
        //printf("\nBUCLE DESACTIVADO\n"); debug
    }
}

bool estaEnModoCircular(Cola* cola)
{
    bool output = cola->inicio->anterior == cola->final && cola->final->siguiente == cola->inicio;

    return (output && cola->cantidadElementos > 0);
}

int main(void)
{
    int i, option, correPrograma, indice;

    correPrograma = true;

    Cola colaReproduccion;
    inicializarCola(&colaReproduccion);

    while(correPrograma)
    {
        //system("clear"); 
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

                if (colaReproduccion.actual != null)
                {
                    colaReproduccion.actual = colaReproduccion.actual->anterior;

                }

                break;
            case 2:
                printf("\n[2] SIGUIENTE\n");

                if (colaReproduccion.actual != null)
                {
                    colaReproduccion.actual = colaReproduccion.actual->siguiente;
                }

                break;
            case 3:
                printf("\n[3] Agregar cancion\n");

                i = mostrarPlaylist();

                if (i < 0 || i > 15) { break; }

                printf("\nMostrando cola de reproduccion\n");
                mostrarColaReproduccion(&colaReproduccion);
                printf("\nEliga una posicion donde insertar la cancion\n> ");
                scanf("\n%d", &indice);

                enqueue(&colaReproduccion, &playlistOriginal[i], indice);

                if (colaReproduccion.estaEnPrimIter)
                {
                    /*
                    * esta validacion es para tener el bucle desactivado tras la primera iteracion
                    * esto ya que nos interesa que el el modo circular no este activado
                    * predeterminadamente
                    */
                    toggleBucle(&colaReproduccion, DESACTIVAR);
                    colaReproduccion.estaEnPrimIter = false;
                    break;
                }

                if (estaEnModoCircular(&colaReproduccion) && !colaReproduccion.estaEnBucle)
                {
                    toggleBucle(&colaReproduccion, DESACTIVAR);
                }

                //sleep(0.5);

                break;
            case 4:
                printf("\n[4] Mostrando cola de reproduccion\n");
                mostrarColaReproduccion(&colaReproduccion);

                //sleep(4);

                break;
            case 5:
                printf("\n[5] Quitar cancion de la cola.\n");

                printf("\nMostrando cola de reproduccion\n");
                mostrarColaReproduccion(&colaReproduccion);
                printf("\nEliga una posicion para eliminar la cancion\n> ");
                scanf("\n%d", &indice);

                dequeue(&colaReproduccion, indice);

                // validacion para evitar crash en caso de que se elimine el ultimo elemento de la cola
                if (colaReproduccion.cantidadElementos == 0) { break; }

                if (estaEnModoCircular(&colaReproduccion) && !colaReproduccion.estaEnBucle)
                {
                    toggleBucle(&colaReproduccion, DESACTIVAR);
                }

                //sleep(0.5);

                break;
            case 6:
                printf("\n[6] REINICIAR REPRODUCCION\n");

                if (colaReproduccion.inicio != null)
                {
                    colaReproduccion.actual = colaReproduccion.inicio;
                }

                printf("\nReproducción reiniciada.\n");

                //sleep(0.5);

                break;
            case 7:
                printf("Bye bye\n");
                correPrograma = false;
                break;
            default:
                break;
        }
    }

    while (colaReproduccion.cantidadElementos > 0)
    {
        dequeue(&colaReproduccion, 0);
    }

    printf("\n\n\r");
    return 0;
}